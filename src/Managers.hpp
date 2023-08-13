#pragma once
#include <Physics.hpp>
#include <SFML/Graphics.hpp>

namespace Physics {
namespace Managers {
// Manages transformations of the items in the window. Size and translation
class TransformationManager {
public:
    TransformationManager();

    // Updates the manager
    void Update(const float& scrollValue);

    // Return the view object
    const sf::View& GetView();

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

std::vector<std::string> SplitStringIgnoreSpace(const std::string& string, const char& character);
}  // namespace Managers
}  // namespace Physics