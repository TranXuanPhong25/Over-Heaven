#ifndef CREDITSTATE_H_
#define CREDITSTATE_H_
#include "../core/StateMachine.hpp"
#include "../comp/Transition.hpp"
class IntroState;
class CreditState : public GameState, public Transition {
public:
	static CreditState* get();
	bool enter(SDL_Renderer* ren);
	bool exit();
	void handleEvent(SDL_Event& e);
	void update(const float& dT);
	void render(SDL_Renderer* ren);
	void finishGetOut() override;
private:
	static CreditState s_exit_state_;
	CreditState();
	SDL_Texture* credit_;
	SDL_Rect credit_rect_;
	SDL_Rect dest_rect_;
	int credit_texture_height_;
	bool esc_pressed_;
	Mix_Music* background_music_;
};

#endif // !CREDITSTATE_H_