#include <Managers.hpp>
#include <Physics.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window/WindowStyle.hpp>
#include <iostream>

int main(const int argc, const char *argv[]) {
    if (argc < 2) {
        return 1;
    }
    Physics::Universe universe = Physics::Universe(argv[1]);

    // Graphical settings
    sf::ContextSettings settings;
    settings.antialiasingLevel = 4;

    // Window object
    sf::RenderWindow window(sf::VideoMode(1080, 720), "Planets", sf::Style::Default, settings);

    // Clock used for elapsed time
    sf::Clock clock;

    // Mouse wheel scroll value, calculated in delta from 0
    float scrollValue = 0;

    // Transformation manager
    Physics::Managers::TransformationManager manager;

    window.setFramerateLimit(30);

    while (window.isOpen()) {
        scrollValue = 0;
        window.setView(manager.GetView());
        // Handle Events
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseWheelScrolled)
                scrollValue = event.mouseWheelScroll.delta;
        }

        // Get Elapsed Time
        float elapsedTime = clock.getElapsedTime().asSeconds();
        clock.restart();

        // Update Transformation Manager
        manager.Update(scrollValue);

        // Clear Window
        window.clear();

        // Update and draw content
        universe.Update(elapsedTime);
        universe.Draw(window);

        // Display the window
        window.display();
    }

    return 0;
}