#include "header/Timer.h"
void startClock() {}
Timer::Timer() {
	paused_ = false;
	started_ = false;

	start_ticks_ = 0;
	paused_ticks_ = 0;
}
void Timer::start() {
	started_ = true;
	paused_ = false;
	start_ticks_ = SDL_GetTicks();
	paused_ticks_ = 0;
}
void Timer::stop() {
	started_ = false;
	paused_ = true;
	start_ticks_ = 0;
	paused_ticks_ = 0;

}
void Timer::pause() {
	if (!paused_ && started_) {
		paused_ = true;
		paused_ticks_ = SDL_GetTicks() - start_ticks_;
		start_ticks_ = 0;
	}
}
void Timer::unpause() {
	if (paused_ && started_) {
		paused_ = false;
		start_ticks_ = SDL_GetTicks() - paused_ticks_;
		paused_ticks_ = 0;
	}
}
Uint32 Timer::getTicks() const {

	if (started_) {
		return (paused_)
			? paused_ticks_
			: SDL_GetTicks() - start_ticks_;
	}
	else return 0;
}

bool Timer::isStarted() const {
	return started_;
}
bool Timer::isPaused() const {
	return started_ && paused_;
}