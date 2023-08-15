#include <Managers.hpp>
#include <Physics.hpp>
#include <algorithm>
#include <cctype>
#include <iostream>
#include <lua.hpp>

void universeError(const std::string &key, const int &bodyIndex) {
    std::cout << key << " for the body at index " << bodyIndex + 1 << " is malformed." << std::endl;
}

bool luaOk(lua_State *L, int r) {
    if (r != LUA_OK) {
        std::string error = lua_tostring(L, -1);
        std::cout << error << std::endl;
        return false;
    }
    return true;
}

bool parseColor(std::string &colorStr, sf::Color &color) {
    std::transform(colorStr.begin(), colorStr.end(), colorStr.begin(), [](char c) { return std::tolower(c); });
    if (colorStr.length() == 7 && colorStr[0] == '#') {
        for (auto i = colorStr.begin() + 1; i != colorStr.end(); i++) {
            if (!std::isxdigit(*i)) {
                return {};
            }
        }
        std::string s = {colorStr[1], colorStr[2]};
        sf::Uint8 r = std::stoi(s, nullptr, 16);
        s = {colorStr[3], colorStr[4]};
        sf::Uint8 g = std::stoi(s, nullptr, 16);
        s = {colorStr[5], colorStr[6]};
        sf::Uint8 b = std::stoi(s, nullptr, 16);

        color = sf::Color(r, g, b);
        return true;
    }
    if (colorStr == "red") {
        color = sf::Color::Red;
        return true;
    }
    if (colorStr == "green") {
        color = sf::Color::Green;
        return true;
    }
    if (colorStr == "blue") {
        color = sf::Color::Blue;
        return true;
    }
    if (colorStr == "yellow") {
        color = sf::Color::Yellow;
        return true;
    }
    if (colorStr == "magenta") {
        color = sf::Color::Magenta;
        return true;
    }
    if (colorStr == "cyan") {
        color = sf::Color::Cyan;
        return true;
    }
    if (colorStr == "white") {
        color = sf::Color::White;
        return true;
    }
    if (colorStr == "grey") {
        color = sf::Color(100, 100, 100);
        return true;
    }
    if (colorStr == "orange") {
        color = sf::Color(255, 165, 0);
        return true;
    }
    return false;
}

bool bodyFromLuaTable(lua_State *L, std::vector<Physics::Body> &bodies) {
    // Get mass
    lua_pushstring(L, "mass");
    if (lua_gettable(L, -2) != LUA_TNUMBER) {
        universeError("Mass", bodies.size());
        return false;
    }
    float mass = (float)lua_tonumber(L, -1);
    lua_pop(L, 1);

    // Get position
    lua_pushstring(L, "position");
    if (lua_gettable(L, -2) != LUA_TTABLE) {
        universeError("Position vector", bodies.size());
        return false;
    }
    lua_pushnumber(L, 1);
    if (lua_gettable(L, -2) != LUA_TNUMBER) {
        universeError("X-coordinate for the position", bodies.size());
        return false;
    }
    lua_pushnumber(L, 2);
    if (lua_gettable(L, -3) != LUA_TNUMBER) {
        universeError("Y-coordinate for the position", bodies.size());
        return false;
    }
    float x = (float)lua_tonumber(L, -2);
    float y = (float)lua_tonumber(L, -1);
    lua_pop(L, 3);

    // Get velocity
    lua_pushstring(L, "velocity");
    if (lua_gettable(L, -2) != LUA_TTABLE) {
        universeError("Velocity vector", bodies.size());
        return false;
    }
    lua_pushnumber(L, 1);
    if (lua_gettable(L, -2) != LUA_TNUMBER) {
        universeError("X-coordinate for the position", bodies.size());
        return false;
    }
    lua_pushnumber(L, 2);
    if (lua_gettable(L, -3) != LUA_TNUMBER) {
        universeError("Y-coordinate for the position", bodies.size());
        return false;
    }
    float vx = (float)lua_tonumber(L, -2);
    float vy = (float)lua_tonumber(L, -1);
    lua_pop(L, 3);

    // Get color (optional)
    sf::Color color = sf::Color::Green;
    lua_pushstring(L, "color");
    int colorQueryResult = lua_gettable(L, -2);
    if (colorQueryResult != LUA_TNIL) {
        if (colorQueryResult != LUA_TSTRING) {
            universeError("Color", bodies.size());
            return false;
        }
        std::string colorStr = lua_tostring(L, -1);
        if (!parseColor(colorStr, color)) {
            universeError("Color", bodies.size());
            return false;
        }
    }
    lua_pop(L, 1);

    bodies.emplace_back(mass, sf::Vector2f(x, y), sf::Vector2f(vx, vy), color);

    return true;
}
namespace Physics {

Universe::Universe(const std::string &path) {
    lua_State *L = luaL_newstate();
    luaL_openlibs(L);
    if (!luaOk(L, luaL_dofile(L, path.c_str()))) {
        return;
    }
    lua_getglobal(L, "Universe");  // lstack = [table]
    if (!lua_istable(L, -1)) {
        return;
    }

    lua_pushnil(L);  // lstack = [table] [nil]

    while (lua_next(L, -2)) {
        if (!bodyFromLuaTable(L, bodies)) {
            break;
        }
        lua_pop(L, 1);
    }

    lua_close(L);
}

void Universe::Update(const float &elapsedTime) {
    for (auto &b : bodies) {
        if (!b.ToBeRemoved) {
            b.Update(elapsedTime, bodies);
        }
    }

    // Remove the collided bodies
    bodies.erase(std::remove_if(bodies.begin(), bodies.end(), [](Body b) { return b.ToBeRemoved; }), bodies.end());
}

void Universe::Draw(sf::RenderWindow &window) {
    for (auto &body : bodies) {
        body.Draw(window);
    }
}

}  // namespace Physics