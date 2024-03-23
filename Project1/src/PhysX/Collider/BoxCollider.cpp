#include "BoxCollider.h"
#include "../PhysXEngine.h"

BoxCollider::BoxCollider()
{
	physics = PhysXEngine::GetInstance().GetPhysics();
}

BoxCollider::~BoxCollider()
{
	if (boxshape)
	{
		boxshape->release();
	}
}

void BoxCollider::ConstructCollider()
{
	shapeType = ColliderShape::BOX;

	physicsMaterial = PhysXEngine::GetInstance().GetPxPhysicsMaterial();

	boxshape = physics->createShape(PxBoxGeometry(sizeExtents.x, sizeExtents.y, sizeExtents.z), *physicsMaterial);
}

PxShape* BoxCollider::GetShape()
{
	return boxshape;
}



