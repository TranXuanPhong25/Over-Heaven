#include "header/Text.h"
Text::Text() {
	rect_.x = 0;
	rect_.y = 0;
	rect_.w = 0;
	rect_.h = 0;
	texture_ = NULL;
	content_ = "";
	color_ = { 0,0,0 };

}


void Text::setTextColor(SDL_Color type) {
	color_ = type;

}

std::string Text::getTextContent() {

	return content_;
}
bool Text::setTextContent(SDL_Renderer* ren, const std::string& content, TTF_Font* font) {
	SDL_Surface* textSurface = TTF_RenderText_Solid(font, content.c_str(), color_);

	if (textSurface == NULL)
	{
		std::cout << SDL_GetError() << std::endl;

	}
	else
	{
		//Create texture from surface pixels
		texture_ = SDL_CreateTextureFromSurface(ren, textSurface);
		if (texture_ == NULL)
		{
			std::cout << SDL_GetError() << std::endl;

		}
		else {
			rect_.w = textSurface->w;
			rect_.h = textSurface->h;
		}

		SDL_FreeSurface(textSurface);
	}

	return texture_ != NULL;
}