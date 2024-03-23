#include "PhysXUtils.h"

glm::vec3 PxVec3ToGLM(PxVec3& value)
{
    return glm::vec3(value.x, value.y, value.z);
}

PxVec3 GLMToPxVec3(const glm::vec3& value)
{
    return PxVec3(value.x,value.y,value.z);
}
