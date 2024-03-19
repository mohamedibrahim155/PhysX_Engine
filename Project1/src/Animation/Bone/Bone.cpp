#include "Bone.h"

void AssimpToGLM(const aiMatrix4x4& a, glm::mat4& g)
{
	g[0][0] = a.a1; g[0][1] = a.b1; g[0][2] = a.c1; g[0][3] = a.d1;
	g[1][0] = a.a2; g[1][1] = a.b2; g[1][2] = a.c2; g[1][3] = a.d2;
	g[2][0] = a.a3; g[2][1] = a.b3; g[2][2] = a.c3; g[2][3] = a.d3;
	g[3][0] = a.a4; g[3][1] = a.b4; g[3][2] = a.c4; g[3][3] = a.d4;
}



NodeAnim::NodeAnim(const std::string& name, const aiNodeAnim* channel) :Name(name)
{

	int totalKeyFrames = channel->mNumPositionKeys;

	for (int i = 0; i < totalKeyFrames; i++)
	{
		aiVector3D aiPosition = channel->mPositionKeys[i].mValue;
		float timeStamp = channel->mPositionKeys[i].mTime;

		PositionKeyFrame data(GetGLMVec(aiPosition), timeStamp,EasingType::Linear);
		listOfPositionKeyFrames.push_back(data);
	}

	totalKeyFrames = channel->mNumRotationKeys;

	for (int rotationIndex = 0; rotationIndex < totalKeyFrames; rotationIndex++)
	{
		aiQuaternion aiOrientation = channel->mRotationKeys[rotationIndex].mValue;
		float timeStamp = channel->mRotationKeys[rotationIndex].mTime;

	
		glm::quat rot = GetGLMQuat(aiOrientation);

		glm::vec3 eulerRotation = glm::degrees(glm::eulerAngles(rot));

		RotationKeyFrame data(eulerRotation, timeStamp, EasingType::Linear);
		//RotationKeyFrame data(GetGLMQuat(aiOrientation), timeStamp, EasingType::Linear);

		listOfRotationKeyframes.push_back(data);
	}

	totalKeyFrames = channel->mNumScalingKeys;


	for (int scaleIndex = 0; scaleIndex < totalKeyFrames; scaleIndex++)
	{
		aiVector3D aiScale = channel->mScalingKeys[scaleIndex].mValue;
		float timeStamp = channel->mScalingKeys[scaleIndex].mTime;

		ScaleKeyFrame data(GetGLMVec(aiScale), timeStamp, EasingType::Linear);

		listOfScaleKeyFrames.push_back(data);
	}

}
