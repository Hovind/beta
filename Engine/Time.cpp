#include <SDL2/SDL.h>
#include "Time.h"

const float TICKS_PER_SEC = 0.001f;

namespace Engine {
	Time::Time()
	: _time(0) {}

	Time::~Time() {

	}

	float Time::getTime() {
		return TICKS_PER_SEC * _time;
	}

	float Time::getFrameCap() {
		return TICKS_PER_SEC * _frameCap;
	}

	void Time::begin(){
		_startTicks = SDL_GetTicks();
	}

	float Time::end() {
		float frameTicks = SDL_GetTicks() - _startTicks;
		if (frameTicks && frameTicks < _frameCap){
			SDL_Delay(_frameCap - frameTicks);
			_time += _frameCap;
			return TICKS_PER_SEC * _frameCap;
		}
		else {
			_time += frameTicks;
			return TICKS_PER_SEC * frameTicks;
		}
	}
}