#include "PhysXUtils.h"

glm::vec3 PxVec3ToGLM(const PxVec3& value)
{
    return glm::vec3(value.x, value.y, value.z);
}

PxVec3 GLMToPxVec3(const glm::vec3& value)
{
    return PxVec3(value.x,value.y,value.z);
}

PxBounds3 CalculateAABB(std::vector<Vertex> vertices)
{
    if (vertices.size() == 0)
    {
		return PxBounds3{ PxVec3(0.0f), PxVec3(0.0f) };
    }

    PxVec3 min = GLMToPxVec3(vertices[0].Position);
    PxVec3 max = GLMToPxVec3(vertices[0].Position);



	for (const Vertex& vertex : vertices)
	{
		min.x = PxMin(min.x, vertex.Position.x);
		min.y = PxMin(min.y, vertex.Position.y);
		min.z = PxMin(min.z, vertex.Position.z);

		max.x = PxMax(max.x, vertex.Position.x);
		max.y = PxMax(max.y, vertex.Position.y);
		max.z = PxMax(max.z, vertex.Position.z);
	}

    return PxBounds3(min,max);
}

