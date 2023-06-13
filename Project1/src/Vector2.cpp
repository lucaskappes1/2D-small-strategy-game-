#include "Vector2.h"
#include <cmath>

Vector2::Vector2() : x(0), y(0)
{

}

Vector2::Vector2(float _x, float _y) : x(_x), y(_y)
{
}

Vector2 Vector2::operator+(const Vector2& other) const
{
	return Vector2(x + other.x, y + other.y);
}

Vector2 Vector2::operator-(const Vector2& other) const
{
	return Vector2(x - other.x, y - other.y);
}

Vector2& Vector2::operator+=(const Vector2& other)
{
	x += other.x;
	y += other.y;
	return *this;
}

Vector2& Vector2::operator-=(const Vector2& other)
{
	x -= other.x;
	y -= other.y;
	return *this;
}

Vector2 Vector2::operator*(float scalar) const
{
	return Vector2(x * scalar, y * scalar);
}

Vector2& Vector2::operator*=(float scalar)
{
	x *= scalar;
	y *= scalar;
	return *this;
}

float Vector2::dot(const Vector2& other) const
{
	return x * other.x + y * other.y;
}

float Vector2::magnitude() const
{
	return std::sqrt(x * x + y * y);
}

Vector2 Vector2::normalize() const
{
	float mag = magnitude();
	return Vector2(x / mag, y / mag);
}
