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
	return physicsObject->rigidActor;
}

void RigidBody::InitializeRigidBody(BaseCollider::ColliderShape colliderShape)
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

void RigidBody::InitializeRigidBody(PhysXObject* object)
{
	physicsObject = object;
	modelTransform = &physicsObject->transform;

	pxRigidActor = physicsObject->rigidActor;

	switch (rigidBodyType)
	{
	case RigidBody::RigidBodyType::DYNAMIC:
		physicsObject->rigidActor = physics->createRigidDynamic(
			PxTransform(GLMToPxVec3(modelTransform->position)));

		break;
	case RigidBody::RigidBodyType::STATIC:

		physicsObject->rigidActor = physics->createRigidStatic(
			PxTransform(GLMToPxVec3(modelTransform->position)));
		break;
	default:
		break;
	}

	physicsObject->rigidActor->attachShape(*physicsObject->collider->GetShape());

}

