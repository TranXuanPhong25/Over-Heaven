#include "LoadingState.h"
#include "PlayState.h"
struct ThreadData
{
	PlayState* playState;
	SDL_Renderer* ren;
	std::atomic<float>* progress;
	std::atomic<bool>* loadingFinished;
	std::atomic<Uint64>* endLoadedTime;
};

LoadingState LoadingState::s_loading_state_;

int loadingResources(void* data)
{
	ThreadData* threadData = reinterpret_cast<ThreadData*>(data);
	PlayState* playState = threadData->playState;
	SDL_Renderer* ren = threadData->ren;
	std::atomic<float>* progress = threadData->progress;
	std::atomic<bool>* loadingFinished = threadData->loadingFinished;
	std::atomic<Uint64>* endLoadedTime = threadData->endLoadedTime;

	playState->loadResources(ren, progress);
	*endLoadedTime = SDL_GetTicks64();
	*loadingFinished = true;
	delete threadData;

	return 1;
}

LoadingState::LoadingState()
{
	p_loading_thread_ = NULL;
	end_loaded_time_ = 0;
	alpha_ = 0;
	progress_ = 0.0f;
	progress_bar_rect_ = { 0, SCREEN_HEIGHT / 2 - 20, 0, 40 };
	end_loaded_time_ = 0;
	loading_finished_ = false;
}

LoadingState* LoadingState::get()
{
	return &s_loading_state_;
}

bool LoadingState::enter(SDL_Renderer* ren)
{
	startGetInEffect();
	bool success = true;
	progress_ = 0.0f;
	// Start the loading thread
	ThreadData* threadData = new ThreadData();
	threadData->playState = PlayState::get();
	threadData->ren = ren;
	threadData->progress = &progress_;
	threadData->loadingFinished = &loading_finished_;
	threadData->endLoadedTime = &end_loaded_time_;
	p_loading_thread_ = SDL_CreateThread(loadingResources, "LoadingThread", threadData);

	return success;
}

bool LoadingState::exit()
{
	bool success = true;
	progress_ = 0.0f;
	end_loaded_time_ = 0;
	loading_finished_ = false;
	p_loading_thread_ = NULL;
	alpha_ = 0;
	progress_bar_rect_ = { 0, SCREEN_HEIGHT / 2 - 20, 0,40 };

	return success;
}

void LoadingState::handleEvent(SDL_Event& e)
{
}

void LoadingState::update(const float& dT)
{
	progress_bar_rect_.w = easeInOut(progress_bar_rect_.w, static_cast<float>(SCREEN_WIDTH) / 2 * progress_, 0.1f);
	progress_bar_rect_.x = static_cast<float>(SCREEN_WIDTH) / 2 - progress_bar_rect_.w / 2;

	if (loading_finished_)
	{
		alpha_ = static_cast<Uint8>((SDL_GetTicks64() - end_loaded_time_) / 1000 * 255);
	}

	if (alpha_ >= 255)
	{
		startGetOutEffect();
		loading_finished_=false; // stop the loading bar, ensure this block run once
		alpha_=	0;
	}
	handleTransition(dT);
}
void LoadingState::render(SDL_Renderer* ren)
{
	SDL_SetRenderDrawColor(ren, 0xff, 0xff, 0xff, 255);
	SDL_RenderFillRectF(ren, &progress_bar_rect_);
	SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
	renderTransitionFx(ren);
}

void LoadingState::finishGetOut()
{
	StateMachine::get()->setNextState(PlayState::get());
}
