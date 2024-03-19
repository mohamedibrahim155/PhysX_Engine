#include "Time.h"

Time& Time::GetInstance()
{
	static Time instance;
	return instance;
}

void Time::SetCurrentTime(double currentFrame)
{
	this->currentFrame = currentFrame;

	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;
}
