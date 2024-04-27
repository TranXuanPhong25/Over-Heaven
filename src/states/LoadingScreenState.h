#ifndef LOADING_SCREEN_STATE_H
#define LOADING_SCREEN_STATE_H

#include "../core/StateMachine.h"
#include "../comp/Transition.h"
static int loadingResources(void* data);

class PlayState;
class LoadingScreenState : public GameState
{
public:
	static LoadingScreenState* get();
	bool enter(SDL_Renderer* ren);
	bool exit();
	void handleEvent(SDL_Event& e);
	void update(const float& dT);
	void render(SDL_Renderer* ren);
private:
	static LoadingScreenState s_loading_screen_state_;
	LoadingScreenState();
	SDL_Thread* loadingThread_;
	Uint8 alpha_;
	std::atomic<float> progress_;
	std::atomic<bool> loading_finished_;
	std::atomic<Uint64> end_loaded_time_;
	SDL_FRect progress_bar_rect_;
	// another stuff
};

#endif // LOADING_SCREEN_STATE_H