#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <vector>

namespace Physics {

extern sf::VertexArray Trace;

sf::Vector2f Zero();
float Distance(const sf::Vector2f &v1, const sf::Vector2f &v2);
sf::Vector2f Scale(const sf::Vector2f& v, const float& c);
sf::Vector2f Normalise(const sf::Vector2f &v);

class Body {
public:
    // Constructors
    Body();
    Body(const float &mass,
         const sf::Vector2f &position0,
         const sf::Vector2f &velocity0 = {0.f, 0.f},
         const sf::Color &color = sf::Color::Green);

    // Update/Draw Methods
    void Update(const float &elapsedTime, std::vector<Body> &bodies);
    void Draw(sf::RenderWindow &window);
    void NewMass(float newMass);
    float GetRadius();
    sf::Vector2f GetPosition();

    // Values
    bool ToBeRemoved = false;

    // Operator Overloads
    bool operator==(const Body &other);

private:
    // Values
    sf::Vector2f position, velocity, acceleration;
    float mass = 1.0f;
    float radius;
    sf::CircleShape shape;

    // Trail data
    unsigned int trailIndex = 0;
    std::vector<sf::Vector2f> trailPosition;

    // Methods
    sf::Vector2f calculateAccelerationTo(const Body &body);
};

class Universe {
public:
    // Default constructor
    Universe();

    // Construct a universe through a .planets file
    Universe(const std::string &file);

    // Add a new body through an existing one
    void NewBody(Body body);

    // Add a new body through data
    void NewBody(float mass, sf::Vector2f position0, sf::Vector2f velocity0, sf::Color color = sf::Color::Green);

    // Update the universe
    void Update(const float &elapsedTime);

    // Draw the content of the universe
    void Draw(sf::RenderWindow &window);

    // Getters
    const std::vector<Body> &GetBodies();

    // Constants
    static const unsigned int TRAIL_LENGTH = 100;

private:
    // Bodies in the universe
    std::vector<Body> bodies;
};
}