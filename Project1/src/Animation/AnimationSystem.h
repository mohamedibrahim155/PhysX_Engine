#pragma once

#include "../EntityManager/Entity.h"
#include "Animation.h"
#include "AnimationSequence.h"

class Model;
class AnimationSystem
{
public :

	static AnimationSystem& GetInstance();

	void UpdateAnimationSequence(float deltaTime);
	void ToggleRewind();
	void TogglePlayOrPause();
	void AddAnimationSequence(AnimationSequence* animation);
	void RemoveAnimationSequence(AnimationSequence* animation);
	void SetSequence(AnimationSequence* sequence);
	void SetAnimationSpeed(int speed);
	void NextSequence();
	void PreviousSequence();

	void SequenceStart();

	AnimationSequence* currentSequence = nullptr;

private:

	std::vector<AnimationSequence*> animationSequences;

	int currentSequenceIndex = 0;

	float animationSystemTime = 0;
	float animationSpeed = 1;

	bool isAnimationPlaying = false;
	bool isRewind = false;

};

