#include "Vector2D.h"
Vector2D::Vector2D() : x(0), y(0) {}
Vector2D::Vector2D(float _x, float _y) : x(_x), y(_y) {}


Vector2D Vector2D::operator+(const Vector2D& other) const {
	return Vector2D(x + other.x, y + other.y);
}

Vector2D Vector2D::operator-(const Vector2D& other) const {
	return Vector2D(x - other.x, y - other.y);
}

Vector2D Vector2D::operator*(float scalar) const {
	return Vector2D(x * scalar, y * scalar);
}

Vector2D Vector2D::operator/(float scalar) const {
	if (scalar != 0) {
		return Vector2D(x / scalar, y / scalar);
	}
	else std::cout << "try to / 0\n";

	return *this;
}

Vector2D& Vector2D::operator+=(const Vector2D& other) {
	x += other.x;
	y += other.y;
	return *this;
}

Vector2D& Vector2D::operator-=(const Vector2D& other) {
	x -= other.x;
	y -= other.y;
	return *this;
}

Vector2D& Vector2D::operator*=(float scalar) {
	x *= scalar;
	y *= scalar;
	return *this;
}

Vector2D& Vector2D::operator/=(float scalar) {
	if (scalar != 0) {
		x /= scalar;
		y /= scalar;
	}
	else std::cout << "try to / 0\n";
	return *this;
}

float Vector2D::length() const {
	return sqrt(x * x + y * y);
}

Vector2D& Vector2D::normalize() {
	float len = length();
	if (len > 0) {
		*this /= len;
	}
	return *this;
}

float Vector2D::dot(const Vector2D& other) const {
	return x * other.x + y * other.y;
}

float Vector2D::distance(const Vector2D& v1, const Vector2D& v2) {
	float dx = v2.x - v1.x;
	float dy = v2.y - v1.y;
	return sqrt(dx * dx + dy * dy);
}