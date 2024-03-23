#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <PxPhysicsAPI.h>
using namespace physx;


extern glm::vec3 PxVec3ToGLM(const PxVec3& value);

extern PxVec3 GLMToPxVec3(const glm::vec3& value);


