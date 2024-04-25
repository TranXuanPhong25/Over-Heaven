#include "LoadingScreenState.h"
#include "PlayState.h"
struct ThreadData
{
    PlayState *playState;
    SDL_Renderer *ren;
};

LoadingScreenState LoadingScreenState::s_loading_screen_state_;

int loadingResources(void *data)
{
    ThreadData *threadData = reinterpret_cast<ThreadData *>(data);
    PlayState *playState = threadData->playState;
    SDL_Renderer *ren = threadData->ren;
    playState->loadResources(ren);
    delete threadData;
    return 1;
}

LoadingScreenState::LoadingScreenState()
{
    start_time_ = 0;
    loadingThread_ = NULL;
}

LoadingScreenState *LoadingScreenState::get()
{
    return &s_loading_screen_state_;
}

bool LoadingScreenState::enter(SDL_Renderer *ren)
{
    bool success = true;
    start_time_ = SDL_GetTicks();

    // Start the loading thread
    ThreadData *threadData = new ThreadData();
    threadData->playState = PlayState::get();
    threadData->ren = ren;
    loadingThread_ = SDL_CreateThread(loadingResources, "LoadingThread", threadData);

    return success;
}

bool LoadingScreenState::exit()
{
    bool success = true;

    // cleanup thread

    return success;
}

void LoadingScreenState::handleEvent(SDL_Event &e)
{
    // Handle input for the loading screen here
}

void LoadingScreenState::update(const float &dT)
{
int threadReturnValue =0;
    SDL_WaitThread(loadingThread_, &threadReturnValue);
    // Handle the error (e.g., by terminating the program or retrying the operation)
    if (threadReturnValue == 1)
    {
        start_time_ = SDL_GetTicks();
        // Handle the error
        threadReturnValue = 0;
    }
    if ((SDL_GetTicks() - start_time_ > 1000))
    {
        StateMachine::get()->setNextState(PlayState::get());
    }
}

void LoadingScreenState::render(SDL_Renderer *ren)
{
    // Render the loading screen here
int threadReturnValue =0;
 SDL_WaitThread(loadingThread_, &threadReturnValue);
    // Fade-in effect
  

        Uint8 alpha = static_cast<Uint8>((SDL_GetTicks() - start_time_)/1000 * 255);
        SDL_RenderFillRect(ren, NULL);
        SDL_SetRenderDrawColor(ren, 0, 0, 0, alpha);
    
}
