#include "PhysXUtils.h"
#include "PhysXEngine.h"
#include "PhysXObject.h"
glm::vec3 PxVec3ToGLM(const PxVec3& value)
{
    return glm::vec3(value.x, value.y, value.z);
}

PxVec3 GLMToPxVec3(const glm::vec3& value)
{
    return PxVec3(value.x,value.y,value.z);
}

glm::quat PxQuatToGLM(const PxQuat& value)
{
	return glm::quat(value.w, value.x, value.y, value.z);
}

PxQuat GLMToPxQuat(const glm::quat& glmQuat) 
{
	return PxQuat(glmQuat.x, glmQuat.y, glmQuat.z, glmQuat.w);
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


bool Physics::IsInLayer(const unsigned int& layer, const std::vector<unsigned int>& listOfLayers)
{
	for (const unsigned int& i : listOfLayers)
	{
		if (i == layer) return true;
	}
	return false;
}

bool Physics::rayCast(glm::vec3 rayOrigin, glm::vec3 direction, float maxDistance, RayCastHitInfo& rayInfo, const std::vector<unsigned int>& layerMask)
{
	for (PhysXObject* phys : PhysXEngine::GetInstance().GetListOfPhysicsObjects())
	{
		if (!IsInLayer(phys->entityLayer, layerMask)) continue;

		PxVec3 origin = GLMToPxVec3(rayOrigin);
		PxVec3 dir = GLMToPxVec3(direction);
		PxGeomRaycastHit mLocalHit;
		PxTransform pxTransform(GLMToPxVec3(phys->transform.position), GLMToPxQuat(phys->collider->GetRotation()));

		if ((PxGeometryQuery::raycast(origin, dir, phys->collider->GetShape()->getGeometry(), pxTransform, maxDistance,
			PxHitFlag::eDEFAULT| PxHitFlag::eANY_HIT , 1, &mLocalHit)))
		{
			rayInfo.physObject = phys;
			rayInfo.point = PxVec3ToGLM(mLocalHit.position);
			rayInfo.normal = PxVec3ToGLM(mLocalHit.normal);
			rayInfo.distance = mLocalHit.distance;
			rayInfo.faceID = mLocalHit.faceIndex;

			return true;
		}
	}
	return false;
}

