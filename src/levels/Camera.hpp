#ifndef CAMERA_H_
#define CAMERA_H_

#include "../comp/Vector2D.hpp"
/**
 * @class Camera
 * @brief Represents a camera used for viewing a game level.
 */
class Camera {
public:
	/**
	 * @brief Default constructor for the Camera class.
	 */
	Camera();

	/**
	 * @brief Destructor for the Camera class.
	 */
	~Camera();

	/**
	 * @brief Sets the position of the camera to the specified coordinates.
	 *
	 * @param x The x-coordinate of the new position.
	 * @param y The y-coordinate of the new position.
	 */
	void setPosition(const float& x, const float& y);

	/**
	 * @brief Moves the camera by the specified distance.
	 *
	 * @param d The distance to move the camera by, specified as a Vector2D.
	 */
	void move(Vector2D d);

	/**
	 * @brief Centers the camera on the specified position within the given width and height.
	 *
	 * @param pos The position to center the camera on, specified as a Vector2D.
	 * @param w The width of the camera's viewport.
	 * @param h The height of the camera's viewport.
	 * @param levelWidth The width of the level.
	 * @param levelHeight The height of the level.
	 */
	void centerOn(const Vector2D& pos, const int& w, const int& h, const int& levelWidth, const int& levelHeight);

	/**
	 * @brief Retrieves the viewport of the camera.
	 *
	 * @return The SDL_Rect representing the viewport of the camera.
	 */
	SDL_Rect getViewport() const;

	/**
	 * @brief Gets the position of the camera.
	 *
	 * @return The position of the camera as a Vector2D.
	 */
	Vector2D getPos() const;

private:
	int screenWidth_; /**< The width of the screen.> */
	int screenHeight_; /**< The height of the screen.> */
	int xOffset_; /**< The x-offset of the camera.> */
	int yOffset_; /**< The y-offset of the camera.> */
	Vector2D pos_; /**< The position of the camera.> */
	float damping_factor_; /**< The damping factor for camera movement.> */
};

#endif 