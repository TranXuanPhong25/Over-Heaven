#ifndef BASE_OBJECT_H_
#define BASE_OBJECT_H_
#include "../levels/Camera.h"
class Entity {
public:
	Entity();
	~Entity();
	void render(SDL_Renderer* ren, SDL_Rect* clip = NULL, SDL_Rect* stretch = NULL);
	void free();
	bool loadTexture(SDL_Renderer* ren, const std::string& path);
	SDL_Texture* getTexture();
	void setRect(const int& x, const int& y, Camera& cam);
	SDL_Rect getRect() const;
	SDL_Rect getHurtBox() const;
	void updateRect(Camera& cam);
	Vector2D getPos() const;
protected:
	SDL_Rect hurtbox_;
	SDL_Rect rect_;
	SDL_Texture* texture_;
	Vector2D pos_;
};
#endif // !BASE_OBJECT_H_