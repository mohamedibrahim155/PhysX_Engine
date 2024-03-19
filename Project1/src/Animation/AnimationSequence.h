#pragma once

#include "Animation.h"

class AnimationSystem;

enum Mode
{
	NORMAL = 0,
	REWIND = 1
};


class AnimationSequence
{

public:
	AnimationSequence();
	~AnimationSequence();

	void AddAnimationClip(Animation* animationClip, Model*  model);
	void RemoveAnimationClip(Animation* animationClip);

	void SetAnimationSequenceTime(float time);
	void CalculateSequenceTotalTime(Animation* animation);
	void UpdateCurrentSequenceTime(float deltaTime);

	void SetCurrentAnimation(int index);
	void SetModeState(const Mode& sequenceMode);

	void ResetTime();
	void ResetPositions();
	void SetVisibilityRenderers(bool isActive);

	float GetTotalTimeFrame();

	Mode SequenceMode = Mode::NORMAL;

private:

	std::map<Model*,Animation*> animationClipsWithObjectsList;
	std::map<Model*, Animation*>::iterator clipsIterator;

	float sequenceTotalTime = 0;
	float currentTime = 0;

	int currentIndex = 0;




};

