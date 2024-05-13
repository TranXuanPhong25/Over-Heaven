#include "Camera.hpp"
Camera::Camera() : screenWidth_(SCREEN_WIDTH / TILE_SIZE), screenHeight_(SCREEN_HEIGHT / TILE_SIZE), xOffset_(0), yOffset_(0), damping_factor_(0.05f) {
}

Camera::~Camera() {}

void Camera::setPosition(const float& x, const float& y) {
	xOffset_ = static_cast<int>(x / TILE_SIZE);
	yOffset_ = static_cast<int>(y / TILE_SIZE);
	pos_.x = x;
	pos_.y = y;
}

void Camera::move(Vector2D d) {
	d *= damping_factor_;
	pos_ += d;
}

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

SDL_Rect Camera::getViewport() const {
	SDL_Rect viewport{};
	viewport.x = xOffset_;
	viewport.y = yOffset_;
	viewport.w = screenWidth_;
	viewport.h = screenHeight_;
	return viewport;
}

Vector2D Camera::getPos() const
{
	return pos_;
}
