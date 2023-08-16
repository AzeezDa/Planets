#include <math.h>
#include <Physics.hpp>

#define RADIUS_TO_MASS_POWER 0.33f
#define GRAVITIONAL_CONSTANT 1000.f
#define TRAIL_LENGTH 100

namespace Physics {

Body::Body(const float& mass, const sf::Vector2f& position0, const sf::Vector2f& velocity0, const sf::Color& color)
    : mass(mass), position(position0), velocity(velocity0), trailIndex(0U) {
    radius = pow(mass, RADIUS_TO_MASS_POWER);

    // Shape of the bodies is a circle
    shape = sf::CircleShape(radius);
    shape.setOrigin(radius, radius);
    shape.setFillColor(color);

    // Set up the trail
    trail.resize(TRAIL_LENGTH);
    for (int i = 0; i < TRAIL_LENGTH; i++) {
        trail[i] = sf::Vector2f(position.x, position.y);
    }
}

void Body::Update(const float& elapsedTime, std::vector<Body>& bodies) {
    // This update uses the verlet velocity to calculate the kinematic equation

    sf::Vector2f halfStepVelocity = velocity + acceleration * 0.5f * elapsedTime;
    position += halfStepVelocity * elapsedTime;

    acceleration = Zero();

    // Go through each body and calculate the force to each body
    for (auto& body : bodies) {
        // Skip calculating force to itself
        if (&body == this || body.ToBeRemoved) {
            continue;
        }

        acceleration += calculateAccelerationTo(body);

        // If the body collides with another body, merge them into one
        if (Distance(position, body.position) <= radius + body.radius) {
            // Conservation of momentum
            halfStepVelocity = (velocity * mass + body.velocity * body.mass) / (body.mass + mass);
            newMass(body.mass + mass);
            body.ToBeRemoved = true;
            acceleration = Zero();
            break;
        }
    }

    velocity = halfStepVelocity + acceleration * 0.5f * elapsedTime;

    shape.setPosition(position.x, position.y);

    // Shift the for loop index for the trail to avoid memory reallocation
    trail[trailIndex] = sf::Vector2f(position.x, position.y);
    trailIndex = (trailIndex + 1) % trail.size();
}

void Body::Draw(sf::RenderWindow& window) {
    sf::VertexArray trailVertexArray = sf::VertexArray(sf::LinesStrip, TRAIL_LENGTH);
    for (size_t i = 0; i < trail.size(); i++) {
        // The alpha value is doing the fading effect
        sf::Color color = sf::Color(255, 255, 255, static_cast<sf::Uint8>(i * 255 / TRAIL_LENGTH));

        trailVertexArray[i] = trail[(i + trailIndex) % TRAIL_LENGTH];
        trailVertexArray[i].color = color;
    }

    window.draw(trailVertexArray);
    window.draw(shape);
}

sf::Vector2f Body::calculateAccelerationTo(const Body& body) {
    // Apply Newton's Law of Gravity
    sf::Vector2f diff = position - body.position;
    float distance = Distance(position, body.position);
    return Scale(Normalise(diff), -GRAVITIONAL_CONSTANT * body.mass / distance / distance);
}

void Body::newMass(const float& newMass) {
    mass = newMass;
    radius = pow(mass, RADIUS_TO_MASS_POWER);
    shape.setRadius(radius);
    shape.setOrigin(radius, radius);
}

}  // namespace Physics