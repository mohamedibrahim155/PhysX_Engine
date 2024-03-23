#include "RigidBody.h"
#include "PhysXEngine.h"
#include "PhysXUtils.h"
RigidBody::RigidBody()
{
	physics = PhysXEngine::GetInstance().GetPhysics();
}

RigidBody::~RigidBody()
{
	if (pxRigidActor)
	{
		pxRigidActor->release();
	}
}

void RigidBody::SetRigidBodyType(RigidBodyType type)
{
	rigidBodyType = type;
}

void RigidBody::SetDrag(float drag)
{
	
}

void RigidBody::SetMass(float mass)
{
	((PxRigidDynamic*)pxRigidActor)->setMass(mass);
}

void RigidBody::SetVelocity(const glm::vec3& velocity)
{
	AsDynamicRigidBody()->setLinearVelocity(GLMToPxVec3(velocity));
}

void RigidBody::SetPosition(glm::vec3 position)
{
	PxTransform localTm(PxVec3(position.x, position.y, position.z));
	pxTransform = localTm;
}

PxRigidDynamic* RigidBody::AsDynamicRigidBody()
{
	return (PxRigidDynamic*)pxRigidActor;
}

PxRigidStatic* RigidBody::AsStaticRigidBody()
{
	return (PxRigidStatic*)pxRigidActor;

}

PxRigidActor* RigidBody::GetPxRigidBody()
{
	return pxRigidActor;
}

void RigidBody::InitilizeRigidBody(BaseCollider::ColliderShape colliderShape)
{

	switch (colliderShape)
	{
	case BaseCollider::ColliderShape::NONE:
		break;
	case BaseCollider::ColliderShape::BOX:
		collider = new BoxCollider();
		break;
	case BaseCollider::ColliderShape::SPHERE:
		break;
	default:
		break;
	}

	collider->ConstructCollider();

	switch (rigidBodyType)
	{
	case RigidBody::RigidBodyType::DYNAMIC:

		pxRigidActor = physics->createRigidDynamic(pxTransform);
		break;
	case RigidBody::RigidBodyType::STATIC:
		pxRigidActor = physics->createRigidStatic(pxTransform);
		break;
	}

	pxRigidActor->attachShape(*collider->GetShape());
}

