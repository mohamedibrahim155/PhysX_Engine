#pragma once
#include "../../Object.h"
#include <PxShape.h>

using namespace physx;

class PhysXObject;
class BoxCollider;
class Transform;
class BaseCollider
{
public:
	enum class ColliderShape
	{
		NONE = -1,
		BOX = 0,
		SPHERE = 1
	};

	virtual void ConstructCollider() = 0;
	virtual void DrawRender() = 0;
	virtual void InitializeCollider(PhysXObject* object);

	virtual PxShape* GetShape() = 0;

	ColliderShape shapeType;


	BoxCollider* AsBoxCollider();

	PxShape* shape = nullptr;
	PhysXObject* physicsObject;
	Transform* physXTransform;

	PxBounds3 modelAABB;

private:

	PxBounds3 CalculatePxModelAABB();

};

