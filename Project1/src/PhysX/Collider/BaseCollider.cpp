#include "BaseCollider.h"
#include "BoxCollider.h"
#include "SphereCollider.h"
#include "../PhysXObject.h"
#include "../PhysXUtils.h"

void BaseCollider::InitializeCollider(PhysXObject* object)
{
	physicsObject = object;

	physXTransform = &object->transform;

	modelAABB = CalculatePxModelAABB();

	modelAABB.minimum.x *= physXTransform->scale.x;
	modelAABB.minimum.y *= physXTransform->scale.y;
	modelAABB.minimum.z *= physXTransform->scale.z;

	modelAABB.maximum.x *= physXTransform->scale.x;
	modelAABB.maximum.y *= physXTransform->scale.y;
	modelAABB.maximum.z *= physXTransform->scale.z;

	
}

BoxCollider* BaseCollider::AsBoxCollider()
{
	return (BoxCollider*)this;
}

SphereCollider* BaseCollider::AsSphereCollider()
{
	return (SphereCollider*)this;
}

PxBounds3 BaseCollider::CalculatePxModelAABB()
{
	if (physicsObject->meshes.empty())
	{
		return PxBounds3{ PxVec3(0.0f), PxVec3(0.0f) };
	}

	PxBounds3 minMax;

	minMax.minimum = GLMToPxVec3(physicsObject->meshes[0]->vertices[0].Position);
	minMax.maximum = GLMToPxVec3(physicsObject->meshes[0]->vertices[0].Position);

	for (std::shared_ptr<Mesh> mesh : physicsObject->meshes)
	{
		PxBounds3 temp = CalculateAABB(mesh->vertices);

		minMax.minimum.x = PxMin(temp.minimum.x, minMax.minimum.x);
		minMax.minimum.y = PxMin(temp.minimum.y, minMax.minimum.y);
		minMax.minimum.z = PxMin(temp.minimum.z, minMax.minimum.z);

		minMax.maximum.x = PxMax(temp.maximum.x, minMax.maximum.x);
		minMax.maximum.y = PxMax(temp.maximum.y, minMax.maximum.y);
		minMax.maximum.z = PxMax(temp.maximum.z, minMax.maximum.z);
	}

	return PxBounds3(minMax.minimum, minMax.maximum);
}
