#include "Managers.hpp"

namespace Physics
{
namespace Managers
{
    TransformationManager::TransformationManager()
    {
        view = sf::View(sf::FloatRect(0.f, 0.f, 1080.f, 720.f));
        view.setCenter(0.f, 0.f); 
    }

    // Updates the manager
	void TransformationManager::Update(const float& scrollValue)
	{

        // Update Scaling factor based on scroll value
        float scaleFactor = scrollValue < 0 ? 1.1f : scrollValue > 0 ? 0.91f : 1.0f;
        scale *= scaleFactor;

        // Scale the view
        view.zoom(scaleFactor);

        // Drag with left mouse button moves the view
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
        {
            newTranslation = sf::Mouse::getPosition() - currentMousePosition;
            view.setCenter(-translation.x - newTranslation.x, -translation.y - newTranslation.y);
        }
        else
        {
            currentMousePosition = sf::Mouse::getPosition();

            view.setCenter(-translation.x, -translation.y);
            translation += newTranslation;
            newTranslation = sf::Vector2i(0, 0);
        }
	}

    sf::View& TransformationManager::GetView() { return view; }

    // Splits a string with a given character and returns a vector of strings. This method ignores spaces
    std::vector<std::string> SplitStringIgnoreSpace(const std::string& string, const char& character)
    {
        // The parts of the strings
        std::vector<std::string> splitStrings;
        splitStrings.push_back("");

        // Index of the current part
        size_t splitStringIndex = 0;

        for (size_t i = 0; i < string.size(); i++)
        {
            // Skip space
            if (string[i] == ' ')
                continue;

            // If the split character is reached, begin adding a new string to the vector and continue
            if (string[i] == character)
            {
                splitStringIndex++;
                splitStrings.push_back("");
                continue;
            }

            // Add the current character to the current string in the vector
            splitStrings[splitStringIndex] += string[i];
        }

        return splitStrings;
    }
}
}