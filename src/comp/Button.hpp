#ifndef BUTTON_H_
#define BUTTON_H_

#include "Transition.hpp"

class Button {
public:
	enum Type {
		CONTINUE,
		NEWGAME,
		OPTIONS,
		EXIT,
		VOLUME_SLIDER,
		SLIDER,
		BACK,
		NUM_BUTTONS
	};
    Button();
	~Button();
	void render(SDL_Renderer* ren);
	void loadTexture(SDL_Renderer* ren, const std::string& path);
    SDL_Texture* getTexture();
	void setRectY(const int& y);
	void setRectXCenterOn(const int& x);
    SDL_Rect getRect() const;
	void setType(Type type);
	void reduceAlpha();
	void enhanceAlpha();
	Type getType() const;
	void verticalCenter(Button destination);
private:
	Type type_;
	SDL_Texture* texture_;
	SDL_Rect rect_;
	bool is_focused_;
	Uint8 alpha_;
};
#endif // !BUTTON_H_