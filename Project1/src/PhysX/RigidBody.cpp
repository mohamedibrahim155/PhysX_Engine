#include "RigidBody.h"
#include "PhysXEngine.h"

RigidBody::RigidBody()
{
	physics = PhysXEngine::GetInstance().GetPhysics();
}

RigidBody::~RigidBody()
{
	if (pxRigidBody)
	{
		pxRigidBody->release();
	}
}

PxRigidDynamic* RigidBody::AsDynamicRigidBody()
{
	return (PxRigidDynamic*)pxRigidBody;
}

PxRigidStatic* RigidBody::AsStaticRigidBody()
{
	return (PxRigidStatic*)pxRigidBody;

}

PxRigidBody* RigidBody::GetRigidBody()
{
	return pxRigidBody;
}

void RigidBody::InitilizeRigidBody(BaseCollider::ColliderShape colliderShape)
{

	if (colliderShape == BaseCollider::ColliderShape::BOX)
	{
		collider = new BoxCollider();

		collider->ConstructCollider();
	}
	else if (colliderShape == BaseCollider::ColliderShape::SPHERE)
	{

	}

	if (rigidBodyType == RigidBodyType::DYNAMIC)
	{
		PxTransform localTm(PxVec3(PxReal(0), PxReal(10), 0));

		pxRigidBody = physics->createRigidDynamic(localTm);

		pxRigidBody->attachShape(*collider->AsBoxCollider()->shape);

		PhysXEngine::GetInstance().GetPhysicsScene()->addActor(*pxRigidBody);

	}
	else if (rigidBodyType == RigidBodyType::STATIC)
	{

	}

}

