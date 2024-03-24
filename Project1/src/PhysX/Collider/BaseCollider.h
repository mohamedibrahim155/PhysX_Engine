#pragma once
#include <PxShape.h>
#include "glm/glm.hpp"
#include "../PhysicsMaterial/PhysicsMaterial.h"
using namespace physx;

class PhysXObject;
class BoxCollider;
class SphereCollider;
class Transform;
class BaseCollider
{
public:
	enum class ColliderShape
	{
		BOX = 0,
		SPHERE = 1
	};

	virtual void ConstructCollider() = 0;
	virtual void Render() = 0;
	virtual void InitializeCollider(PhysXObject* object);
	virtual void SetPhysicsMaterial(PhysicsMaterial& material) = 0;

	virtual PxShape* GetShape() = 0;
	virtual glm::vec3 GetPosition();
	virtual void SetCentreOffset(const glm::vec3& offsetValue);

	ColliderShape shapeType;


	BoxCollider* AsBoxCollider();
	SphereCollider* AsSphereCollider();
	PxShape* shape = nullptr;
	PhysXObject* physicsObject;
	Transform* physXTransform;

	PxBounds3 modelAABB;

	glm::vec3 offsetPosition =  glm::vec3(0);

private:

	PxBounds3 CalculatePxModelAABB();

};

