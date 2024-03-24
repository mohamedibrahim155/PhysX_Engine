#include "RigidBody.h"
#include "PhysXEngine.h"
#include "PhysXUtils.h"
RigidBody::RigidBody()
{
	physics = PhysXEngine::GetInstance().GetPhysics();
}

RigidBody::~RigidBody()
{
	if (rigidActor)
	{
		rigidActor->release();
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
	((PxRigidDynamic*)rigidActor)->setMass(mass);
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
	return (PxRigidDynamic*)rigidActor;
}

PxRigidStatic* RigidBody::AsStaticRigidBody()
{
	return (PxRigidStatic*)rigidActor;

}

PxRigidActor* RigidBody::GetPxRigidBody()
{
	return physicsObject->rigidActor;
}


void RigidBody::InitializeRigidBody(PhysXObject* object)
{
	physicsObject = object;
	modelTransform = &object->transform;
	rigidActor = object->rigidActor;
	collider = object->collider;

	/*PxTransform transform(GLMToPxVec3(modelTransform->position),
		       GLMToPxQuat(modelTransform->quaternionRotation));*/

	PxTransform transform(GLMToPxVec3(collider->GetPosition()),
		GLMToPxQuat(collider->GetRotation()));

	switch (rigidBodyType)
	{
	case RigidBody::RigidBodyType::DYNAMIC:
		rigidActor = physics->createRigidDynamic(transform);

		break;
	case RigidBody::RigidBodyType::STATIC:

		rigidActor = physics->createRigidStatic(transform);
		break;
	default:
		break;
	}

	if (rigidActor)
	{
		rigidActor->userData = object;

		rigidActor->attachShape(*collider->GetShape());
		PhysXEngine::GetInstance().GetPhysicsScene()->addActor(*rigidActor);

	}
	



}

