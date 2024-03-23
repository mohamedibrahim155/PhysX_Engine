#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <PxPhysicsAPI.h>
#include "../Vertex.h"
#include <vector>
using namespace physx;


extern glm::vec3 PxVec3ToGLM(const PxVec3& value);

extern PxVec3 GLMToPxVec3(const glm::vec3& value);
extern glm::quat PxQuatToGLM(const PxQuat& value);
extern PxQuat GLMToPxQuat(const glm::quat& value);

extern PxBounds3 CalculateAABB(std::vector<Vertex> vertices);
//extern PxBounds3 CalculateModelAABB(PxBounds3& outAABB);


