#pragma once


class Time
{
public :
	static Time& GetInstance();

	void SetCurrentTime(double currentFrame);

	double deltaTime;
	double currentFrame;
	double lastFrame;
};

