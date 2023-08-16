#pragma once
#include <Physics.hpp>
#include <SFML/Graphics.hpp>

namespace Physics {
// Manages transformations of the items in the window. Size and translation
class ViewManager {
public:
    ViewManager();

    // Updates the manager
    void Update(const float& elapsedTime);

    // Return the view object
    const sf::View& GetView();

    // Window resized
    void WindowResized(const unsigned int& width, const unsigned int& height);

    // Mouse scrolled
    void MouseScrolled(const float& delta);

private:
    // The Transformation matrix
    sf::View view;

    // Translation from the origin
    sf::Vector2f translation;

    // Position of the mouse, used to determine how much the mouse was dragged across the screen
    sf::Vector2f currentMousePosition;

    // Stores the currently added translation, is added later to the original translation
    sf::Vector2f newTranslation;

    // The scale of the items
    float scale = 1.0f;
};

}  // namespace Physics