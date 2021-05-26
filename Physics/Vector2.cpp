#include "Physics.hpp"

namespace Physics
{
	// Vector Constructors
	Vector2::Vector2() : x(0.0f), y(0.0f) {}
	Vector2::Vector2(const float& x, const float& y) : x(x), y(y) {}

	// Mathematical methods
	float Vector2::Magnitude() { return sqrt(x * x + y * y); }
	float Vector2::DistanceTo(const Vector2& vector) { return sqrt(pow(x - vector.x, 2.0f) + pow(y - vector.y, 2.0f)); }

	Vector2 Vector2::Normalised()
	{ 
		float squareInv = 1 / Magnitude(); 
		return Vector2(x * squareInv, y * squareInv); 
	}

	// Operator overloads
	Vector2 Vector2::operator + (const Vector2& other) const { return Vector2(this->x + other.x, this->y + other.y); }
	Vector2 Vector2::operator - (const Vector2& other) const { return Vector2(this->x - other.x, this->y - other.y); }
	Vector2 Vector2::operator * (const float& value) const { return Vector2(this->x * value, this->y * value); }
	Vector2 Vector2::operator / (const float& value) const { return Vector2(this->x / value, this->y / value); }

	Vector2& Vector2::operator += (const Vector2& other)
	{
		this->x += other.x;
		this->y += other.y;
		return *this;
	}

	Vector2& Vector2::operator -= (const Vector2& other)
	{
		this->x -= other.x;
		this->y -= other.y;
		return *this;
	}

	Vector2& Vector2::operator *= (const float& other)
	{
		this->x *= other;
		this->y *= other;
		return *this;
	}

	Vector2& Vector2::operator /= (const float& other)
	{
		this->x /= other;
		this->y /= other;
		return *this;
	}

	Vector2& Vector2::operator = (const float& other)
	{
		this->x = other;
		this->y = other;
		return *this;
	}
}