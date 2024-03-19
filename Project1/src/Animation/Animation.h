#pragma once
#include "../model.h"
#include "Keyframe.h"


class Animation
{
public:

	void AddPositionKeyFrame(const glm::vec3& position, double time, EasingType easeType = EasingType::Linear);
	void AddRotationKeyFrame(const glm::quat& rotation, double time, EasingType easeType = EasingType::Linear);
	void AddRotationKeyFrame(const glm::vec3& rotation, double time, EasingType easeType = EasingType::Linear);
	void AddScaleKeyFrame(const glm::vec3& scale, double time, EasingType easeType = EasingType::Linear);
	void AddColoreKeyFrame(const glm::vec3& color, double time, EasingType easeType = EasingType::Linear);
	void AddEventKeyFrame( double time, std::function<void()> OnEventCallback = nullptr);

	void SetAnimationTime(float time);

	std::vector<PositionKeyFrame> positionKeyFrameList;
	std::vector<RotationKeyFrame> rotationKeyFrameList;
	std::vector<ScaleKeyFrame> scaleKeyFrameList;
	std::vector<ColorKeyFrame> colorKeyFrameList;
	std::vector<EventKeyFrame*> eventKeyFrameList;


	double time;
	bool isPaused = false;

};





