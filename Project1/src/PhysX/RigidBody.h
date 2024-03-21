#pragma once
#include <PxRigidBody.h>
#include <PxRigidDynamic.h>
#include <PxRigidStatic.h>
#include "Collider/BoxCollider.h"
#include <PxPhysics.h>
using namespace physx;

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
	PxRigidBody* GetRigidBody();

	BaseCollider* collider;
	RigidBodyType rigidBodyType;

	void InitilizeRigidBody(BaseCollider::ColliderShape colliderShape);
private:

	PxRigidBody* pxRigidBody;
	PxPhysics* physics;
	PxTransform transform;
};

