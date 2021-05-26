#include <SFML/Graphics.hpp>
#include <iostream>
#include "Physics/Physics.hpp"
#include "Physics/Managers.hpp"

int main(const int argc, const char* argv[])
{
    if (argc == 1)
        return 1;
    // Graphical settings
    sf::ContextSettings settings;
    settings.antialiasingLevel = 5;

    // Window object
    sf::RenderWindow window(sf::VideoMode(1080, 720), "Planets", 7U, settings);

    // Clock used for elapsed t ime
    sf::Clock clock;

    // Mouse wheel scroll value, calculated in delta from 0
    float scrollValue = 0;

    // Transformation manager
    Physics::Managers::TransformationManager manager;

    // Universe, all content and calculations happen here
    Physics::Universe universe = Physics::Universe(argv[1]);

    window.setFramerateLimit(60);

    while (window.isOpen())
    {
        scrollValue = 0;
        window.setView(manager.GetView());
        // Handle Events
        sf::Event event;
        while (window.pollEvent(event))
        {
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