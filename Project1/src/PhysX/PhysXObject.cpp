#include "PhysXObject.h"

PhysXObject::PhysXObject()
{
}

PhysXObject::~PhysXObject()
{
}

void PhysXObject::Initialize(RigidBody::RigidBodyType bodyType, BaseCollider::ColliderShape colliderShape)
{
	rigidBody = new RigidBody();

	if (bodyType == RigidBody::RigidBodyType::DYNAMIC)
	{
		rigidBody->rigidBodyType = RigidBody::RigidBodyType::DYNAMIC;

	}
	else
	{
		rigidBody->rigidBodyType = RigidBody::RigidBodyType::STATIC;
	}

	rigidBody->InitilizeRigidBody(colliderShape);

}
