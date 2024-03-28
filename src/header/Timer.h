#ifndef TIMER_H_
#define TIMER_H_
#include "Constants.h"
class Timer {
public:
	Timer();

	void start();
	void stop();
	void pause();
	void unpause();
	Uint32 getTicks() const;

	bool isStarted() const;
	bool isPaused() const;
private:
	bool started_;
	bool paused_;

	Uint32 start_ticks_;
	Uint32 paused_ticks_;
};
#endif // !TIMER_H_

