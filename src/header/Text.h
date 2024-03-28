#pragma once

#include "BaseObject.h"
class Text : public BaseObject {
public:
	Text();


	void setTextColor(SDL_Color type);
	std::string getTextContent();
	bool setTextContent(SDL_Renderer* ren, const std::string& content, TTF_Font* font);
private:
	std::string content_;
	SDL_Color color_;
};