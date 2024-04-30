#ifndef VECTOR2D_H_
#define VECTOR2D_H_
#include "../core/Constants.h"
class Vector2D {
public:
	float x;
	float y;

	Vector2D();
	Vector2D(float _x, float _y);

	Vector2D operator+(const Vector2D& other) const;
	Vector2D operator-(const Vector2D& other) const;
	Vector2D operator*(float scalar) const;
	Vector2D operator/(float scalar) const;
	Vector2D& operator+=(const Vector2D& other);
	Vector2D& operator-=(const Vector2D& other);
	Vector2D& operator*=(float scalar);
	Vector2D& operator/=(float scalar);

	float length() const;

	Vector2D& normalize();

	float dot(const Vector2D& other) const;
	static float distance(const Vector2D& v1, const Vector2D& v2);
};

#endif // VECTOR2D_H_
