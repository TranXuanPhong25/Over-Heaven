#ifndef BASE_OBJECT_H_
#define BASE_OBJECT_H_
#include "Constants.h"
class BaseObject {
public:
	BaseObject();
	~BaseObject();
	void render(SDL_Renderer* ren, SDL_Rect* clip = NULL, SDL_Rect* stretch = NULL);
	void free();
	bool loadTexture(SDL_Renderer* ren, const std::string& path);
	SDL_Texture* getTexture();
	void setRect(const int& x, const int& y);
	SDL_Rect getRect() const;
protected:

	SDL_Rect rect_;
	SDL_Texture* texture_;
};
#endif // !BASE_OBJECT_H_