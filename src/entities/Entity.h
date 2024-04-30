#ifndef BASE_OBJECT_H_
#define BASE_OBJECT_H_
#include "../levels/Camera.h"
class Entity {
public:
	Entity();
	~Entity();
	void render(SDL_Renderer* ren, SDL_Rect* clip = NULL, SDL_FRect* stretch = NULL);
	void free();
	bool loadTexture(SDL_Renderer* ren, const std::string& path);
	SDL_Texture* getTexture();
	Vector2D getPos() const;
	void setRect(const float& x, const float& y, Camera& cam);
	SDL_FRect getRect() const;
	void updateRect(Camera& cam);
protected:
	SDL_FRect rect_;
	SDL_Texture* texture_;
	Vector2D pos_;
};
#endif // !BASE_OBJECT_H_