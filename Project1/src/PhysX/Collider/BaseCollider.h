#pragma once
#include "../../Object.h"
#include <PxShape.h>

using namespace physx;

class PhysXObject;
class BoxCollider;

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
	virtual PxShape* GetShape() = 0;

	ColliderShape shapeType;


	BoxCollider* AsBoxCollider();

	PhysXObject* physicsObject;
	PxShape* shape = nullptr;
	//Transform* physXTransform;
};

