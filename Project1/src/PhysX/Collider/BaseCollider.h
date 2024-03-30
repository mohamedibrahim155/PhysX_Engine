#pragma once
#include <PxShape.h>
#include "glm/glm.hpp"
#include <PxPhysicsAPI.h>
#include "../PhysicsMaterial/PhysicsMaterial.h"
#include "../../ImGui/ImGuiUtils.h"
using namespace physx;

class PhysXObject;
class BoxCollider;
class SphereCollider;
class CapsuleCollider;
class MeshCollider;
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

	BaseCollider();
	virtual void ConstructCollider() = 0;
	virtual void DrawShape() = 0;
	virtual void DrawColliderProperties() = 0;
	virtual void InitializeCollider(PhysXObject* object);
	virtual void SetPhysicsMaterial(PhysicsMaterial& material);
	virtual void SetCentreOffset(const glm::vec3& offsetValue);

	virtual PxShape* GetShape();
	virtual glm::vec3 GetPosition();
	virtual glm::vec3 GetOffsetPosition();
	virtual glm::quat GetRotation();
	virtual PxTransform GetLocalShapeTransfom();

	void SetTriggerState(bool state);
	void TriggerState();


	BoxCollider* AsBoxCollider();
	SphereCollider* AsSphereCollider();
	CapsuleCollider* AsCapsuleCollider();
	MeshCollider* AsMeshCollider();

	ColliderShape shapeType;
	PxShape*    shape = nullptr;
	PxMaterial* physicsMaterial = nullptr;
	PxPhysics* physics = nullptr;
	PhysXObject* physicsObject = nullptr;
	Transform* modelTransform = nullptr;

	PxBounds3 modelAABB;

	glm::vec3 offsetPosition =  glm::vec3(0);
	glm::vec3 localShapePosition = glm::vec3(0);

	bool isTrigger = false;


private:

	PxBounds3 CalculatePxModelAABB();

};

