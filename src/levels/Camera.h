#ifndef CAMERA_H_
#define CAMERA_H_

#include "Tile.h"
class Camera {
public:
	Camera();
	Camera(int screenWidth, int screenHeight, int mapWidth, int mapHeight);
	~Camera();

	void setPosition(int x, int y);
	void move(int dx, int dy);
	void centerOn(int x, int y);

	SDL_Rect getViewport() const;

private:
	int screenWidth_;
	int screenHeight_;
	int mapWidth_;
	int mapHeight_;
	int xOffset_;
	int yOffset_;
};

#endif 