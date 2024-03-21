#pragma once
#include "PxPhysicsAPI.h"
#include "RigidBody.h"

using namespace physx;

class PhysXObject
{
public:
	PhysXObject();
	~PhysXObject();

	void Initialize(RigidBody::RigidBodyType bodyType , BaseCollider::ColliderShape colliderShape);

private:

	RigidBody* rigidBody;
};

