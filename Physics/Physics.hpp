#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

namespace Physics
{
	extern sf::VertexArray Trace;

	struct Vector2
	{
		// Values
		float x = 0.0f, y = 0.0f;

		// Constructors
		Vector2(const float& x, const float& y);
		Vector2();

		// Methods
		float Magnitude();
		Vector2 Normalised();
		float DistanceTo(const Vector2& vector);

		// Operator Overloads
		Vector2 operator + (const Vector2& other) const;
		Vector2 operator - (const Vector2& other) const;
		Vector2 operator * (const float& other) const;
		Vector2 operator / (const float& other) const;
		Vector2& operator += (const Vector2& other);
		Vector2& operator -= (const Vector2& other);
		Vector2& operator *= (const float& other);
		Vector2& operator /= (const float& other);
		Vector2& operator = (const float& other);
	};

	class Body
	{
	public:
		// Constructors
		Body();
		Body(const float& mass, const Vector2& position0, const Vector2& velocity0 = { 0,0 }, const sf::Color& color = sf::Color::Green);

		// Update/Draw Methods
		void Update(const float& elapsedTime, std::vector<Body>& bodies);
		void Draw(sf::RenderWindow& window);
		void NewMass(float newMass);
		float GetRadius();
		Vector2 GetPosition();

		// Values
		bool ToBeRemoved = false;

		// Operator Overloads
		bool operator == (const Body& other);

	private:

		// Values
		Vector2 position, velocity, acceleration;
		float mass = 1.0f;
		float radius;
		sf::CircleShape shape;
		

		// Trail data
		unsigned int trailIndex = 0;
		std::vector<sf::Vector2f> trailPosition;

		// Methods
		Vector2 calculateAccelerationTo(const Body& body);
	};

	class Universe
	{
	public:
		// Default constructor
		Universe();
		
		// Construct a universe through a .planets file
		Universe(const std::string& file);

		// Add a new body through an existing one
		void NewBody(Body body);

		// Add a new body through data
		void NewBody(float mass, Vector2 position0, Vector2 velocity0, sf::Color color = sf::Color::Green);

		// Update the universe
		void Update(const float& elapsedTime);

		// Draw the content of the universe
		void Draw(sf::RenderWindow& window);

		// Getters
		const std::vector<Body>& GetBodies();

		// Constants
		static const unsigned int TRAIL_LENGTH = 100;

	private:
		// Bodies in the universe
		std::vector<Body> bodies;
	};
}