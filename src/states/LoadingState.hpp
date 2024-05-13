#ifndef LOADING_SCREEN_STATE_H
#define LOADING_SCREEN_STATE_H

#include "../core/StateMachine.hpp"
#include "../comp/Transition.hpp"
static int loadingResources(void* data);

class PlayState;
class LoadingState : public GameState, public Transition
{
public:
	static LoadingState* get();
	bool enter(SDL_Renderer* ren);
	bool exit();
	void handleEvent(SDL_Event& e);
	void update(const float& dT);
	void render(SDL_Renderer* ren);
	void finishGetOut() override;
private:
	static LoadingState s_loading_state_;
	LoadingState();

	SDL_Thread* p_loading_thread_;
	Uint8 alpha_;
	std::atomic<float> progress_;
	std::atomic<bool> loading_finished_;
	std::atomic<Uint64> end_loaded_time_;
	SDL_FRect progress_bar_rect_;
	// another stuff
};

#endif // LOADING_SCREEN_STATE_H