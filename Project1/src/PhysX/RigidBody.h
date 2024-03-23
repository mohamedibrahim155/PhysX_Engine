#pragma once
#include <PxRigidBody.h>
#include <PxRigidDynamic.h>
#include <PxRigidStatic.h>
#include "Collider/BoxCollider.h"
#include <PxPhysics.h>
using namespace physx;

class PhysXObject;
class Transform;

class RigidBody
{
public:

	enum class RigidBodyType
	{
		DYNAMIC,
		STATIC,
	};
	RigidBody();
	~RigidBody();


	PxRigidDynamic* AsDynamicRigidBody();
	PxRigidStatic* AsStaticRigidBody();
	PxRigidActor* GetPxRigidBody();

	BaseCollider* collider;
	RigidBodyType rigidBodyType;

	void InitializeRigidBody(BaseCollider::ColliderShape colliderShape);
	void InitializeRigidBody(PhysXObject* object);
	void SetRigidBodyType(RigidBodyType type); 
	void SetDrag(float drag);
	void SetMass(float mass);
	void SetVelocity(const glm::vec3& velocity);
	void SetPosition(glm::vec3 position);

private:

	PxRigidActor* pxRigidActor;
	PxPhysics* physics;
	PxTransform pxTransform;
	PhysXObject* physicsObject;
	Transform* modelTransform;
};

