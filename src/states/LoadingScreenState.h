#ifndef LOADING_SCREEN_STATE_H
#define LOADING_SCREEN_STATE_H

#include "../core/StateMachine.h"

static int loadingResources(void *data);

class PlayState;
class LoadingScreenState: public GameState
{
public:
    static LoadingScreenState *get();
    bool enter(SDL_Renderer *ren);
    bool exit();
    void handleEvent(SDL_Event &e);
    void update(const float &dT);
    void render(SDL_Renderer *ren);
private:
    static LoadingScreenState s_loading_screen_state_;
    LoadingScreenState();
    Uint32 start_time_;
    SDL_Thread *loadingThread_;
    Uint32 fade_in_start_time_;
    Uint32 fade_out_start_time_;
    // another stuff
};

#endif // LOADING_SCREEN_STATE_H