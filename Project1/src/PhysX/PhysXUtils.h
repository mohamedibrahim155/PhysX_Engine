#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <PxPhysicsAPI.h>
#include "../Vertex.h"
#include <vector>
#include "../Layer.h"
using namespace physx;


extern glm::vec3 PxVec3ToGLM(const PxVec3& value);

extern PxVec3 GLMToPxVec3(const glm::vec3& value);
extern glm::quat PxQuatToGLM(const PxQuat& value);
extern PxQuat GLMToPxQuat(const glm::quat& value);

extern PxBounds3 CalculateAABB(std::vector<Vertex> vertices);

class PhysXObject;
struct RayCastHitInfo
{
	RayCastHitInfo() = default;
	glm::vec3 point= glm::vec3(0);
	glm::vec3 normal = glm::vec3(0);
	unsigned int faceID = 0;
	float distance = 0;
	PhysXObject* physObject = nullptr;
};

struct Ray
{
	Ray(glm::vec3 origin, glm::vec3 direction) : origin(origin)
	{
		this->direction = glm::normalize(direction);
	};
	glm::vec3 origin;
	glm::vec3 direction;

	glm::vec3 GetPoint(float distance) const
	{
		return origin + direction * distance;
	}

};

namespace Physics
{
	extern bool IsInLayer(const unsigned int& layer, const std::vector<unsigned int>& listOfLayers);
	extern bool rayCast(glm::vec3 rayOrigin, glm::vec3 direction, float maxDistance, RayCastHitInfo& rayInfo, const std::vector<unsigned int>& layerMask = { Layer::DEFAULT });
}

