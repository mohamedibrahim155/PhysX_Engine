#pragma once
#include "../../Object.h"
#include <PxShape.h>

using namespace physx;

class BoxCollider;
class BaseCollider : public Object
{
public:
	enum class ColliderShape
	{
		NONE = -1,
		BOX = 0,
		SPHERE = 1
	};
	// Inherited via Object
	virtual void ConstructCollider() = 0;
	virtual void DrawProperties() override;
	virtual void SceneDraw() override;

	ColliderShape shapeType;
	PxShape* shape = nullptr;

	BoxCollider* AsBoxCollider();
};

