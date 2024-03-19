#pragma once
#include <glm/glm.hpp>
#include <assimp/scene.h>
#include <map>
#include <string>		
#include <vector>
#include "../Keyframe.h"


struct BoneInfo
{
	int id;
	glm::mat4 boneOffset;				// Offset from the parent bone/node
	glm::mat4 finalTransformation;		// Calculated transformation used for rendering
	glm::mat4 globalTransformation;		// used for the bone hierarchy transformation calculations when animating
};

struct BoneNode
{
	BoneNode(const std::string& name) : name(name) { }
	std::string name;
	int index;               // bone UID
	glm::mat4 transformation;
	std::vector<BoneNode*> children;
};

struct Armature
{
	std::vector<BoneNode> bones;  // Root bones of the armature
};

struct BoneWeightInfo 
{
	BoneWeightInfo() {
		boneID = glm::vec4(0);
		boneWeight = glm::vec4(0);
	}
	glm::vec4 boneID;
	glm::vec4 boneWeight;
};

void AssimpToGLM(const aiMatrix4x4& a, glm::mat4& g);

// Animation Node
struct NodeAnim
{
	NodeAnim(const std::string& name, const aiNodeAnim* channel);
	std::string Name;
	std::vector<PositionKeyFrame> listOfPositionKeyFrames;
	std::vector<ScaleKeyFrame> listOfScaleKeyFrames;
	std::vector<RotationKeyFrame> listOfRotationKeyframes;
};

struct SkeletonAnim
{
	SkeletonAnim() {}
	std::string Name;
	double TicksPerSecond;
	double Duration;
	//BoneNode* RootNode;
	std::vector<NodeAnim*> Channels;
};


//static inline glm::mat4 ConvertMatrixToGLMFormat(const aiMatrix4x4& from)
//{
//	glm::mat4 to;
//	to[0][0] = from.a1; to[1][0] = from.a2; to[2][0] = from.a3; to[3][0] = from.a4;
//	to[0][1] = from.b1; to[1][1] = from.b2; to[2][1] = from.b3; to[3][1] = from.b4;
//	to[0][2] = from.c1; to[1][2] = from.c2; to[2][2] = from.c3; to[3][2] = from.c4;
//	to[0][3] = from.d1; to[1][3] = from.d2; to[2][3] = from.d3; to[3][3] = from.d4;
//	return to;
//}

static inline glm::vec3 GetGLMVec(const aiVector3D& vec)
{
	return glm::vec3(vec.x, vec.y, vec.z);
}

static inline glm::quat GetGLMQuat(const aiQuaternion& pOrientation)
{
	return glm::quat(pOrientation.w, pOrientation.x, pOrientation.y, pOrientation.z);
}