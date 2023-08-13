#include <math.h>
#include <Physics.hpp>

namespace Physics {
// Constructors
Body::Body() : Body(1.f, {0.f, 0.f}, {0.f, 0.f}) {}

Body::Body(const float& mass, const sf::Vector2f& position0, const sf::Vector2f& velocity0, const sf::Color& color)
    : mass(mass), position(position0), velocity(velocity0), trailIndex(0) {
    // Radius is proportional to the cube root of the mass
    radius = pow(mass, 0.33f);

    // Shape of the bodies is a circle
    shape = sf::CircleShape(radius);
    shape.setOrigin(radius, radius);
    shape.setFillColor(color);

    // Set up the trail
    trail.resize(Universe::TRAIL_LENGTH);
    for (int i = 0; i < Universe::TRAIL_LENGTH; i++)
        trail[i] = sf::Vector2f(position.x, position.y);
}

// Update / Draw
void Body::Update(const float& elapsedTime, std::vector<Body>& bodies) {
    // This update uses the verlet velocity to calculate the kinematic equation

    sf::Vector2f halfStepVelocity = velocity + acceleration * 0.5f * elapsedTime;
    position += halfStepVelocity * elapsedTime;

    acceleration = Zero();

    // Go through each body and calculate the force to each body
    for (auto& body : bodies) {
        // Skip calculating force to itself
        if (body == *this || body.ToBeRemoved) {
            continue;
        }
        acceleration += calculateAccelerationTo(body);

        // If the body collides with another body, merge them into one
        if (Distance(position, body.position) <= radius + body.radius) {
            // Conservation of momentum
            halfStepVelocity = (velocity * mass + body.velocity * body.mass) / (body.mass + mass);
            NewMass(body.mass + mass);
            body.ToBeRemoved = true;
            acceleration = Zero();
            break;
        }
    }

    velocity = halfStepVelocity + acceleration * 0.5f * elapsedTime;

    shape.setPosition(position.x, position.y);

    // Shift the for loop index for the trail to avoid memory reallocation
    trail[trailIndex] = sf::Vector2f(position.x, position.y);
    trailIndex = (trailIndex + 1) % Universe::TRAIL_LENGTH;
}

void Body::Draw(sf::RenderWindow& window) {
    // Draw the trail by going through the trace vector that contains the previous positions of the body. This is a shifting for loop to avoid memory reallocation
    sf::VertexArray va = sf::VertexArray(sf::LinesStrip, Universe::TRAIL_LENGTH);
    for (size_t i = 0; i < Universe::TRAIL_LENGTH; i++) {
        // Color fading effect
        sf::Color color = sf::Color(255, 255, 255, 0 + static_cast<sf::Uint8>(i * 255 / Universe::TRAIL_LENGTH));
        va[i] = trail[(i + trailIndex) % Universe::TRAIL_LENGTH];
        va[i].color = color;
    }
    window.draw(va);

    window.draw(shape);
}

// Calculate acceleration using Newton's Law of Gravitation
sf::Vector2f Body::calculateAccelerationTo(const Body& body) {
    // Vectorial difference between the bodies
    sf::Vector2f diff = position - body.position;

    // Length of the vectorial difference
    float distance = Distance(position, body.position);

    // Law of Gravitation
    return Scale(Normalise(diff), body.mass / distance / distance * -1000.0);
}

// Change mass of the body
void Body::NewMass(float newMass) {
    mass = newMass;
    radius = pow(mass, 0.33f);
    shape.setRadius(radius);
}

// Return the Radius of the body
float Body::GetRadius() { return shape.getRadius(); }

// Return the position of the body
sf::Vector2f Body::GetPosition() { return position; }

// Operator Overload of ==
bool Body::operator==(const Body& other) { return this == &other; }
}  // namespace Physics