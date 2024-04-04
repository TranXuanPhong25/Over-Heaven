#ifndef CAMERA_H_
#define CAMERA_H_

#include "Tile.h"
#include "../comp/Vector2D.h"
class Camera {
public:
	Camera();

	~Camera();

	void setPosition(int x, int y);
	void move(Vector2D d);
	void centerOn(const Vector2D& pos, const int& w, const int& h, const int& levelWidth, const int& levelHeight);

	SDL_Rect getViewport() const;
	Vector2D getPos();
private:
	int screenWidth_;
	int screenHeight_;
	int xOffset_;
	int yOffset_;
	Vector2D pos_;
	float damping_factor_;
};

#endif 