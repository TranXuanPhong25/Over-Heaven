#ifndef VECTOR2D_H_
#define VECTOR2D_H_

#include "../core/Constants.hpp"

/**
 * @brief Represents a 2D vector.
 */
class Vector2D {
public:
	float x; /**< The x-coordinate of the vector. */
	float y; /**< The y-coordinate of the vector. */

	/**
	 * @brief Default constructor.
	 */
	Vector2D();

	/**
	 * @brief Constructor that initializes the vector with given x and y values.
	 * @param _x The x-coordinate value.
	 * @param _y The y-coordinate value.
	 */
	Vector2D(float _x, float _y);
	/**
	 * @brief Overloaded addition operator.
	 * @param other The vector to be added.
	 * @return The resulting vector after addition.
	 */
	Vector2D operator+(const Vector2D& other) const;

	/**
	 * @brief Overloaded subtraction operator.
	 * @param other The vector to be subtracted.
	 * @return The resulting vector after subtraction.
	 */
	Vector2D operator-(const Vector2D& other) const;

	/**
	 * @brief Overloaded multiplication operator.
	 * @param scalar The scalar value to multiply the vector by.
	 * @return The resulting vector after multiplication.
	 */
	Vector2D operator*(float scalar) const;

	/**
	 * @brief Overloaded division operator.
	 * @param scalar The scalar value to divide the vector by.
	 * @return The resulting vector after division.
	 */
	Vector2D operator/(float scalar) const;

	/**
	 * @brief Overloaded addition assignment operator.
	 * @param other The vector to be added.
	 * @return Reference to the resulting vector after addition.
	 */
	Vector2D& operator+=(const Vector2D& other);

	/**
	 * @brief Overloaded subtraction assignment operator.
	 * @param other The vector to be subtracted.
	 * @return Reference to the resulting vector after subtraction.
	 */
	Vector2D& operator-=(const Vector2D& other);

	/**
	 * @brief Overloaded multiplication assignment operator.
	 * @param scalar The scalar value to multiply the vector by.
	 * @return Reference to the resulting vector after multiplication.
	 */
	Vector2D& operator*=(float scalar);

	/**
	 * @brief Overloaded division assignment operator.
	 * @param scalar The scalar value to divide the vector by.
	 * @return Reference to the resulting vector after division.
	 */
	Vector2D& operator/=(float scalar);

	/**
	 * @brief Calculates the length (magnitude) of the vector.
	 * @return The length of the vector.
	 */
	float length() const;

	/**
	 * @brief Normalizes the vector to have a length of 1.
	 * @return Reference to the normalized vector.
	 */
	Vector2D& normalize();

	/**
	 * @brief Calculates the dot product between this vector and another vector.
	 * @param other The other vector.
	 * @return The dot product of the two vectors.
	 */
	float dot(const Vector2D& other) const;

	/**
	 * @brief Calculates the distance between two vectors.
	 * @param v1 The first vector.
	 * @param v2 The second vector.
	 * @return The distance between the two vectors.
	 */
	static float distance(const Vector2D& v1, const Vector2D& v2);
};

#endif // VECTOR2D_H_
