#include <SFML/Graphics.hpp>
#include <iostream>
#include "Physics/Physics.hpp"
#include "Physics/Managers.hpp"

int main(const int argc, const char* argv[])
{
#ifdef NDEBUG
    // NOT DEBUGGING: Compile in release to run any file by running the .exe file and passing the file name as the executable argument
    if (argc < 2) { return 1; }
    Physics::Universe universe = Physics::Universe(argv[1]);
#else
    // DEBUGGING: This is run in the debugging mode in an IDE such as Visual Studio
    Physics::Universe universe = Physics::Universe("Examples/SolarSystem.planets"); // Change the file name to use a file in the directory
#endif

    // Graphical settings
    sf::ContextSettings settings;
    settings.antialiasingLevel = 5;

    // Window object
    sf::RenderWindow window(sf::VideoMode(1080, 720), "Planets", 7U, settings);

    // Clock used for elapsed time
    sf::Clock clock;

    // Mouse wheel scroll value, calculated in delta from 0
    float scrollValue = 0;

    // Transformation manager
    Physics::Managers::TransformationManager manager;

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