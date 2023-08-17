#include <Managers.hpp>
#include <Physics.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window/WindowStyle.hpp>
#include <iostream>
#include <lua.hpp>

int main(const int argc, const char *argv[]) {
    if (argc < 2) {
        std::cout << "No Lua files given." << std::endl;
        return 1;
    }

    // Set up Lua
    lua_State *L = luaL_newstate();
    luaL_openlibs(L);
    if (luaL_dofile(L, argv[1]) != LUA_OK) {
        std::cout << lua_tostring(L, -1) << std::endl;
        return 1;
    }

    // Read from Lua
    Physics::Universe universe;
    Physics::Configuration configuration;
    if (!configuration.FromLua(L) || !universe.FromLua(L)) {
        return 1;
    }
    lua_close(L);

    // Setup window and graphics settings
    Physics::ViewManager viewManager(configuration.width, configuration.height);
    sf::ContextSettings settings;
    settings.antialiasingLevel = configuration.AALevel;
    sf::RenderWindow window(sf::VideoMode(configuration.width, configuration.height),
                            "Planets",
                            sf::Style::Default,
                            settings);
    window.setFramerateLimit(configuration.fpsLimit);

    // Clock used for elapsed time
    sf::Clock clock;

    // Update loop
    while (window.isOpen()) {
        window.setView(viewManager.GetView());

        // Event handling
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::MouseWheelMoved) {
                viewManager.MouseScrolled(event.mouseWheel.delta);
            }
            if (event.type == sf::Event::Resized) {
                viewManager.WindowResized(event.size.width, event.size.height);
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
        }

        float elapsedTime = clock.getElapsedTime().asSeconds();
        clock.restart();

        // Update routines
        viewManager.Update(elapsedTime);
        if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            universe.Update(elapsedTime);
        }

        // Draw routines
        window.clear();
        universe.Draw(window);
        window.display();
    }

    return 0;
}