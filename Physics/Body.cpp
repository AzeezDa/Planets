#include "Physics.hpp"

namespace Physics
{
    

    // Constructors
    Body::Body() : Body(1.f, { 0.f,0.f }, { 0.f,0.f }) {}

    Body::Body(const float& mass, const Vector2& position0, const Vector2& velocity0, const sf::Color& color)
        : mass(mass), position(position0), velocity(velocity0)
    {
        // Radius is proportional to the cube root of the mass
        radius = pow(mass, 0.33f);

        // Shape of the bodies is a circle
        shape = sf::CircleShape(radius);
        shape.setOrigin(radius, radius);
        shape.setFillColor(color);

        // Set up the trail
        trailPosition.resize(Universe::TRAIL_LENGTH);
        for (auto& vector : trailPosition)
            vector = sf::Vector2f(position.x, position.y);
    }

    // Update / Draw
    void Body::Update(const float& elapsedTime, std::vector<Body>& bodies)
    {
        // This update uses the verlet velocity to calculate the kinematic equation

        Vector2 halfStepVelocity = velocity + acceleration * 0.5f * elapsedTime;
        position += halfStepVelocity * elapsedTime;

        acceleration = 0.0f;

        // Go through each body and calculate the force to each body
        for (std::vector<Body>::iterator body = bodies.begin(); body != bodies.end();)
        {
            // Skip calculating force to itself
            if (*body == *this || body->ToBeRemoved) {
                ++body;
                continue;
            }
            acceleration += calculateAccelerationTo(*body);

            // If the body collides with another body, merge them into one
            if (position.DistanceTo(body->position) <= radius + body->radius)
            {
                // Conservation of momentum
                halfStepVelocity = (velocity * mass + body->velocity * body->mass) / (body->mass + mass);
                NewMass(body->mass + mass);
                body->ToBeRemoved = true;
                acceleration = 0.0f;
                break;
            }

            ++body;
        }

        velocity = halfStepVelocity + acceleration * 0.5f * elapsedTime;

        shape.setPosition(position.x, position.y);
        
        // Shift the for loop index for the trail to avoid memory reallocation
        trailPosition[trailIndex] = sf::Vector2f(position.x, position.y);
        trailIndex = (trailIndex + 1) % Universe::TRAIL_LENGTH;
    }

    void Body::Draw(sf::RenderWindow& window)
    {
        // Draw the trail by going through the trace vector that contains the previous positions of the body. This is a shifting for loop to avoid memory reallocation
        for (size_t i = 0; i < Universe::TRAIL_LENGTH - 1; i++)
        {
            // Color fading effect
            sf::Color color = sf::Color(255, 255, 255, 
                0 + static_cast<sf::Uint8>(i * 255 / Universe::TRAIL_LENGTH));

            // Set the position of the trail dot.
            Trace[0].position = trailPosition[(i + trailIndex) % Universe::TRAIL_LENGTH];
            Trace[1].position = trailPosition[(i + trailIndex + 1) % Universe::TRAIL_LENGTH];

            // Set colours
            Trace[0].color = color;
            Trace[1].color = color;

            window.draw(Trace);
        }

        window.draw(shape);
    }

    Vector2 Body::calculateAccelerationTo(const Body& body)
    {
        // Calculate acceleration using Newton's Law of Gravitation

        // Vectorial difference between the bodies
        Vector2 diff = position - body.position;

        // Length of the vectorial difference
        float distance = position.DistanceTo(body.position);

        // Law of Gravitation
        return diff.Normalised() * body.mass / distance / distance * -1000;
    }

    // Change mass of the body
    void Body::NewMass(float newMass)
    {
        mass = newMass;
        radius = pow(mass, 0.33f);
        shape.setRadius(radius);
    }

    // Return the Radius of the body
    float Body::GetRadius() { return shape.getRadius(); }

    // Return the position of the body
    Vector2 Body::GetPosition() { return position; }

    // Operator Overload of ==
    bool Body::operator == (const Body& other) { return this == &other; }
}