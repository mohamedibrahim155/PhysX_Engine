#include "BoxCollider.h"
#include "../PhysXEngine.h"

BoxCollider::BoxCollider()
{
	physics = PhysXEngine::GetInstance().GetPhysics();
}

BoxCollider::~BoxCollider()
{
	if (shape)
	{
		shape->release();
	}
}

void BoxCollider::ConstructCollider()
{
	shapeType = ColliderShape::BOX;

	physicsMaterial = physics->createMaterial(0.5f, 0.5f, 0.6f);

	shape = physics->createShape(PxBoxGeometry(sizeExtents.x, sizeExtents.y, sizeExtents.z), *physicsMaterial);
}

void BoxCollider::DrawProperties()
{
}

void BoxCollider::SceneDraw()
{
}

PxShape* BoxCollider::GetShape()
{
	return shape;
}
