#include "Camera.h"
Camera::Camera() : screenWidth_(SCREEN_WIDTH / TILE_SIZE), screenHeight_(SCREEN_HEIGHT / TILE_SIZE), xOffset_(0), yOffset_(0), damping_factor_(0.05f) {
}

Camera::~Camera() {}

/**
 * Sets the position of the camera.
 *
 * @param x The x-coordinate of the camera position.
 * @param y The y-coordinate of the camera position.
 */
void Camera::setPosition(const float& x, const float& y) {
	xOffset_ = static_cast<int>(x / TILE_SIZE);
	yOffset_ = static_cast<int>(y / TILE_SIZE);
	pos_.x = x;
	pos_.y = y;
}

/**
 * Moves the camera by a given displacement vector.
 * The movement is dampened by the damping factor.
 *
 * @param d The displacement vector to move the camera by.
 */
void Camera::move(Vector2D d) {
	d *= damping_factor_;
	pos_ += d;
}

/**
 * Centers the camera on a given position with specified target width and height.
 * 
 * @param pos The position to center the camera on.
 * @param targetWidth The target width .
 * @param targetHeight The target height .
 * @param levelWidth The width of the level.
 * @param levelHeight The height of the level.
 */
void Camera::centerOn(const Vector2D& pos, const int& targetWidth, const int& targetHeight, const int& levelWidth, const int& levelHeight) {
	Vector2D targetPos = pos - Vector2D(SCREEN_WIDTH / 2 - targetWidth, 2 * SCREEN_HEIGHT / 3 - targetHeight);

	// Apply linear interpolation (lerp) to smooth camera movement with damping
	Vector2D delta = targetPos - pos_;
	pos_ += delta * damping_factor_;

	// Ensure camera doesn't go beyond level boundaries
	if (pos_.x < 0) {
		pos_.x = 0;
	}
	else if (pos_.x > levelWidth - SCREEN_WIDTH) {
		pos_.x = levelWidth - SCREEN_WIDTH;
	}

	if (pos_.y < 0) {
		pos_.y = 0;
	}
	else if (pos_.y > levelHeight - SCREEN_HEIGHT) {
		pos_.y = levelHeight - SCREEN_HEIGHT;
	}

	// Calculate tile offsets for rendering
	xOffset_ = pos_.x / TILE_SIZE;
	yOffset_ = pos_.y / TILE_SIZE;
}


/**
 * @brief Get the viewport of the camera.
 *
 * This function returns an SDL_Rect representing the viewport of the camera.
 * The viewport contains the x and y offsets, as well as the width and height
 * of the screen.
 *
 * @return SDL_Rect The viewport of the camera.
 */
SDL_Rect Camera::getViewport() const {
	SDL_Rect viewport{};
	viewport.x = xOffset_;
	viewport.y = yOffset_;
	viewport.w = screenWidth_;
	viewport.h = screenHeight_;
	return viewport;
}

/**
 * @brief Get the position of the camera.
 * 
 * @return Vector2D The position of the camera.
 */
Vector2D Camera::getPos()
{
	return pos_;
}
