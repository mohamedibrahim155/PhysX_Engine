#pragma once
#include <PxShape.h>
#include "glm/glm.hpp"
#include "../PhysicsMaterial/PhysicsMaterial.h"
using namespace physx;

class PhysXObject;
class BoxCollider;
class SphereCollider;
class CapsuleCollider;
class Transform;
class BaseCollider
{
public:
	enum class ColliderShape
	{
		BOX = 0,
		SPHERE = 1,
		CAPSULE = 2,
		MESH =3
	};

	virtual void ConstructCollider() = 0;
	virtual void Render() = 0;
	virtual void InitializeCollider(PhysXObject* object);
	virtual void SetPhysicsMaterial(PhysicsMaterial& material) = 0;
	virtual void SetCentreOffset(const glm::vec3& offsetValue);

	virtual PxShape* GetShape() = 0;
	virtual glm::vec3 GetPosition();
	virtual glm::vec3 GetOffsetPosition();
	virtual glm::quat GetRotation();
	virtual PxTransform GetLocalShapeTransfom();

	ColliderShape shapeType;


	BoxCollider* AsBoxCollider();
	SphereCollider* AsSphereCollider();
	CapsuleCollider* AsCapsuleCollider();
	PxShape* shape = nullptr;
	PhysXObject* physicsObject;
	Transform* modelTransform;

	PxBounds3 modelAABB;

	glm::vec3 offsetPosition =  glm::vec3(0);
	glm::vec3 localShapePosition = glm::vec3(0);
private:

	PxBounds3 CalculatePxModelAABB();

};

