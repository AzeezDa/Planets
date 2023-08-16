#include <Managers.hpp>
#include <lua.hpp>

#define MOUSE_SCALE_FACTOR 0.1f
#define KEYBOARD_SCALE_FACTOR 0.2f
#define KEYBOARD_MOVEMENT_SPEED 50.f
constexpr float upScaleFactor(const float& factor) { return (1.f + factor); }
constexpr float downScaleFactor(const float& factor) { return 1.f / upScaleFactor(factor); }

namespace Physics {

ViewManager::ViewManager(const unsigned int& width, const unsigned int& height) {
    view = sf::View(sf::FloatRect(0.f, 0.f, (float)width, (float)height));
    view.setCenter(0.f, 0.f);
}

void ViewManager::Update(const float& elapsedTime) {
    // I & O for Zoom In and Out
    float zoom_factor = 1.0;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::I)) {
        zoom_factor *= downScaleFactor(KEYBOARD_SCALE_FACTOR * elapsedTime);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::O)) {
        zoom_factor *= upScaleFactor(KEYBOARD_SCALE_FACTOR * elapsedTime);
    }
    view.zoom(zoom_factor);
    scale *= zoom_factor;

    // Drag with the left mouse button moves the view
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
        newTranslation = static_cast<sf::Vector2f>(sf::Mouse::getPosition()) - currentMousePosition;
        view.setCenter(-translation.x - newTranslation.x * scale, -translation.y - newTranslation.y * scale);
        return;  // Avoid up messing with keyboard
    } else {
        currentMousePosition = static_cast<sf::Vector2f>(sf::Mouse::getPosition());
        translation += newTranslation * scale;
        view.setCenter(-translation.x, -translation.y);
        newTranslation = sf::Vector2f(0.f, 0.f);
    }

    // WASD to the camera around
    sf::Vector2f keyboardTranslation = Zero();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        keyboardTranslation.y += 1.0f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        keyboardTranslation.x += 1.0f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        keyboardTranslation.y -= 1.0f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        keyboardTranslation.x -= 1.0f;
    }
    if (keyboardTranslation != Zero()) {
        translation += Scale(Normalise(keyboardTranslation), elapsedTime * KEYBOARD_MOVEMENT_SPEED * scale);
        view.setCenter(-translation.x, -translation.y);
    }
}

void ViewManager::WindowResized(const unsigned int& width, const unsigned int& height) {
    view.setSize(width, height);
}

void ViewManager::MouseScrolled(const float& delta) {
    float factor = 1.0f;
    if (delta > 0) {
        factor *= downScaleFactor(MOUSE_SCALE_FACTOR);
    } else if (delta < 0) {
        factor *= upScaleFactor(MOUSE_SCALE_FACTOR);
    }
    view.zoom(factor);
    scale *= factor;
}

const sf::View& ViewManager::GetView() { return view; }

}  // namespace Physics