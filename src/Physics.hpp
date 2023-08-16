#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <lua.hpp>
#include <vector>

namespace Physics {

// The zero vector: (0.f, 0.f)
const sf::Vector2f Zero();

// Calculate the euclidean distance between two Vector2s
float Distance(const sf::Vector2f &v1, const sf::Vector2f &v2);

// Takes a Vector2 and a float and scale the vector by the float
sf::Vector2f Scale(const sf::Vector2f &v, const float &c);

// Take a Vector2 and return a Vector2 of the same direction but with unit length
sf::Vector2f Normalise(const sf::Vector2f &v);

class Body {
public:
    // Construct a new body given its values
    Body(const float &mass,
         const sf::Vector2f &position0,
         const sf::Vector2f &velocity0,
         const sf::Color &color);

    void Update(const float &elapsedTime, std::vector<Body> &bodies);
    void Draw(sf::RenderWindow &window);

    // Flag the body to be removed during the current update iteration
    bool ToBeRemoved = false;

private:
    sf::Vector2f position, velocity, acceleration;
    float mass;
    float radius;
    sf::CircleShape shape;

    // A vector that stores the bodies previous positions in order to draw a line strip of them for a trail
    std::vector<sf::Vector2f> trail;
    // Index of the ring buffer used for the trail
    size_t trailIndex;

    // Change the mass of the body
    void newMass(const float &newMass);
    sf::Vector2f calculateAccelerationTo(const Body &body);
};

class Universe {
public:
    // Read the Universe table from the lua file
    bool FromLua(lua_State *L);

    void Update(const float &elapsedTime);
    void Draw(sf::RenderWindow &window);

private:
    std::vector<Body> bodies;
};

}  // namespace Physics