#include <Managers.hpp>
#include <iostream>
#include <lua.hpp>

void configurationError(const std::string& key) {
    std::cout << "Configuration " << key << " is malformed." << std::endl;
}

namespace Physics {

bool Configuration::FromLua(lua_State* L) {
    lua_getglobal(L, "Config");
    if (lua_isnil(L, -1)) {
        return true;
    }
    if (!lua_istable(L, -1)) {
        return false;
    }

    // Get Window Size
    lua_pushstring(L, "windowSize");
    if (lua_gettable(L, -2) != LUA_TNIL) {
        if (!lua_istable(L, -1) || lua_rawlen(L, -1) > 2) {
            configurationError("windowSize");
            return false;
        }
        lua_pushnumber(L, 1);
        if (lua_gettable(L, -2) != LUA_TNUMBER) {
            configurationError("windowSize's width");
            return false;
        }
        lua_pushnumber(L, 2);
        if (lua_gettable(L, -3) != LUA_TNUMBER) {
            configurationError("windowSize's height");
            return false;
        }

        int width = (int)lua_tonumber(L, -2);
        int height = (int)lua_tonumber(L, -1);

        if (width <= 0 || height <= 0) {
            configurationError("windowSize");
            return false;
        }
        // Update struct values
        this->width = (unsigned int)width;
        this->height = (unsigned int)height;

        lua_pop(L, 2);
    }
    lua_pop(L, 1);

    // Get AALevel
    lua_pushstring(L, "AALevel");
    if (lua_gettable(L, -2) != LUA_TNIL) {
        if (!lua_isnumber(L, -1)) {
            configurationError("AALevel");
            return false;
        }

        int AALevel = (int)lua_tonumber(L, -1);
        if (AALevel < 0) {
            configurationError("AALevel");
            return false;
        }

        // Update struct values
        this->AALevel = (unsigned int)AALevel;
    }
    lua_pop(L, 1);

    // Get fpsLimit
    lua_pushstring(L, "fpsLimit");
    if (lua_gettable(L, -2) != LUA_TNIL) {
        if (!lua_isnumber(L, -1)) {
            configurationError("fpsLimit");
            return false;
        }

        int fpsLimit = (int)lua_tonumber(L, -1);
        if (fpsLimit <= 0) {
            configurationError("fpsLimit");
            return false;
        }

        // Update struct values
        this->fpsLimit = (unsigned int)fpsLimit;
    }
    lua_pop(L, 1);

    return true;
}

}  // namespace Physics