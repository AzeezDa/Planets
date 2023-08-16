#include <Managers.hpp>
#include <Physics.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window/WindowStyle.hpp>
#include <iostream>

#define FPS_LIMIT 60

int main(const int argc, const char *argv[]) {
    if (argc < 2) {
        return 1;
    }

    // Create the universe from the given file
    Physics::Universe universe = Physics::Universe(argv[1]);

    // Setup window and graphics settings
    sf::ContextSettings settings;
    settings.antialiasingLevel = 4;
    sf::RenderWindow window(sf::VideoMode(1080, 720), "Planets", sf::Style::Default, settings);

    // Clock used for elapsed time
    sf::Clock clock;

    // Mouse wheel scroll value, calculated in delta from 0
    float scrollValue = 0;

    // Transformation manager
    Physics::ViewManager manager;

    window.setFramerateLimit(FPS_LIMIT);

    // Update loop
    while (window.isOpen()) {
        window.setView(manager.GetView());

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::MouseWheelMoved) {
                manager.MouseScrolled(event.mouseWheel.delta);
            }
            if (event.type == sf::Event::Resized) {
                manager.WindowResized(event.size.width, event.size.height);
            }
        }

        float elapsedTime = clock.getElapsedTime().asSeconds();
        clock.restart();
        manager.Update(elapsedTime);

        window.clear();
        universe.Update(elapsedTime);
        universe.Draw(window);

        window.display();
    }

    return 0;
}