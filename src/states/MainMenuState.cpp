#include "MainMenuState.h"

MainMenuState MainMenuState::s_main_menu_state_;
MainMenuState::MainMenuState()
{
	buttons_[0].setType(MenuButton::NEWGAME);
	buttons_[1].setType(MenuButton::CONTINUE);
	buttons_[2].setType(MenuButton::QUIT);
	current_button_ = MenuButton::NEWGAME;
	bg_ = NULL;
}
MainMenuState::~MainMenuState()
{
	if (bg_ != NULL) {
		SDL_DestroyTexture(bg_);
		bg_ = NULL;
	}
}
MainMenuState* MainMenuState::get() {
	return &s_main_menu_state_;
}
bool MainMenuState::enter(SDL_Renderer* ren) {
	for (int i = 0; i < NUMS_OF_BUTTONS; i++) {
		buttons_[i].loadTexture(ren, MENU_BUTTON_TEXTURE_PATHS[i]);
		buttons_[i].setRectY(SCREEN_HEIGHT / 2 + i * 100);
	}
	bg_ = IMG_LoadTexture(ren, MENU_BACKGROUND_TEXTURE_PATH.c_str());

	return true;
}
bool MainMenuState::exit() {
	SDL_DestroyTexture(bg_);
	return true;
}
void MainMenuState::handleFocusUp() {
	if (current_button_ == MenuButton::NEWGAME) {
		current_button_ = MenuButton::QUIT;
	}
	else {
		current_button_ = static_cast<MenuButton::ButtonType>(current_button_ - 1);
	}
}
void MainMenuState::handleFocusDown() {
	if (current_button_ == MenuButton::QUIT) {
		current_button_ = MenuButton::NEWGAME;
	}
	else {
		current_button_ = static_cast<MenuButton::ButtonType>(current_button_ + 1);
	}
}
void MainMenuState::handleEnter() {
	if (current_button_ == MenuButton::QUIT) {
		StateMachine::get()->setNextState(ExitState::get());
	}
	else {
		if (current_button_ == MenuButton::NEWGAME) {
			PlayState::get()->deleteSave();
		}
		StateMachine::get()->setNextState(LoadingScreenState::get());
	}
}
void MainMenuState::handleEvent(SDL_Event& e) {
	if (e.type == SDL_KEYDOWN) {
		if (e.key.keysym.sym == SDLK_UP || e.key.keysym.sym == SDLK_w) {
			handleFocusUp();
		}
		else if (e.key.keysym.sym == SDLK_DOWN || e.key.keysym.sym == SDLK_s) {
			handleFocusDown();
		}
		else if (e.key.keysym.sym == SDLK_RETURN) {
			handleEnter();
		}
	}
}
void MainMenuState::update(const float& dT) {
}
void MainMenuState::render(SDL_Renderer* ren) {
	SDL_RenderCopy(ren, bg_, NULL, NULL);
	for (int i = 0; i < NUMS_OF_BUTTONS; i++) {
		if (buttons_[i].getType() == current_button_) {
			buttons_[i].render(ren, FOCUSING);
		}
		else buttons_[i].render(ren);

	}

}

MenuButton::~MenuButton()
{
	SDL_DestroyTexture(texture_);
	texture_ = NULL;
}

void MenuButton::render(SDL_Renderer* ren, const int& alphaFactor)
{
	SDL_SetTextureAlphaMod(texture_, alphaFactor);
	SDL_RenderCopy(ren, texture_, NULL, &rect_);
}


void MenuButton::loadTexture(SDL_Renderer* ren, const std::string& path)
{
	texture_ = IMG_LoadTexture(ren, path.c_str());
	SDL_QueryTexture(texture_, NULL, NULL, &rect_.w, &rect_.h);
	rect_.x = (SCREEN_WIDTH - rect_.w) / 2;
}
void MenuButton::setRectY(const int& y)
{
	rect_.y = y;
}

void MenuButton::setType(ButtonType type)
{
	type_ = type;
}

MenuButton::ButtonType MenuButton::getType()
{
	return type_;
}
