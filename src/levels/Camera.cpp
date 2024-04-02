#include "Camera.h"
Camera::Camera() : screenWidth_(SCREEN_WIDTH), screenHeight_(SCREEN_HEIGHT), mapWidth_(1000), mapHeight_(1000), xOffset_(0), yOffset_(0) {}
Camera::Camera(int screenWidth, int screenHeight, int mapWidth, int mapHeight)
	: screenWidth_(screenWidth), screenHeight_(screenHeight), mapWidth_(mapWidth), mapHeight_(mapHeight), xOffset_(0), yOffset_(0) {}

Camera::~Camera() {}

void Camera::setPosition(int x, int y) {
	xOffset_ = x;
	yOffset_ = y;
}

void Camera::move(int dx, int dy) {
	xOffset_ += dx;
	yOffset_ += dy;
}

void Camera::centerOn(int x, int y) {
	xOffset_ = x - screenWidth_ / 2;
	yOffset_ = y - screenHeight_ / 2;
}

SDL_Rect Camera::getViewport() const {
	SDL_Rect viewport;
	viewport.x = xOffset_;
	viewport.y = yOffset_;
	viewport.w = screenWidth_ / TILE_SIZE;
	viewport.h = screenHeight_ / TILE_SIZE;
	return viewport;
}
