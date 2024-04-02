#include "Camera.h"
Camera::Camera() : screenWidth_(SCREEN_WIDTH / TILE_SIZE), screenHeight_(SCREEN_HEIGHT / TILE_SIZE), xOffset_(0), yOffset_(0) {
}

Camera::~Camera() {}

void Camera::setPosition(int x, int y) {
	xOffset_ = x;
	yOffset_ = y;
	pos_.x = TILE_SIZE * x;
	pos_.y = TILE_SIZE * y;
}

void Camera::move(const Vector2D& d) {
	pos_ += d;
	xOffset_ = pos_.x / TILE_SIZE;
	yOffset_ = pos_.y / TILE_SIZE;

	//printf("%f %f \n", d.x, d.y);
	//float cameraSpeed = 0.1f;

	//// Calculate the target position with an offset
	//Vector2D targetPos = pos_ + d;

	//// Calculate the difference between current position and target position
	//Vector2D diff = targetPos - pos_;

	//// Update the position with interpolation
	//pos_ += diff * cameraSpeed;

	//// Update the offset in tiles
	//xOffset_ = pos_.x / TILE_SIZE;
	//yOffset_ = pos_.y / TILE_SIZE;
}

void Camera::centerOn(const Vector2D& pos, const int& w, const int& h, const int& levelWidth, const int& levelHeight) {
	pos_ = pos - Vector2D(SCREEN_WIDTH / 2 - w, SCREEN_HEIGHT / 2 - h);
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
	xOffset_ = pos_.x / TILE_SIZE;
	yOffset_ = pos_.y / TILE_SIZE;
	//float cameraSpeed = 0.1f;
	//// Calculate the target position with an offset
	//Vector2D targetPos = pos - Vector2D(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);

	//// Calculate the difference between current position and target position
	//Vector2D diff = targetPos - pos_;

	//// Update the position with interpolation
	//pos_ += diff * cameraSpeed;

	//// Clamp the position to ensure it stays within the level boundaries
	//pos_.x = max(0.0f, min((float)(levelWidth - SCREEN_WIDTH), pos_.x));
	//pos_.y = max(0.0f, min((float)(levelHeight - SCREEN_HEIGHT), pos_.y));

	//// Calculate the offset in tiles
	//xOffset_ = pos_.x / TILE_SIZE;
	//yOffset_ = pos_.y / TILE_SIZE;
}

SDL_Rect Camera::getViewport() const {
	SDL_Rect viewport{};
	viewport.x = xOffset_;
	viewport.y = yOffset_;
	viewport.w = screenWidth_;
	viewport.h = screenHeight_;
	return viewport;
}

Vector2D Camera::getPos()
{
	return pos_;
}
