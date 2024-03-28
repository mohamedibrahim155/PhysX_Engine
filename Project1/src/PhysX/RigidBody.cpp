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
		isRigidBodyInitilized = false;
	}
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

void RigidBody::SetKinematic(bool isKinematic)
{
	this->isKinematic = isKinematic;

}

void RigidBody::SetGravity(bool useGravity)
{
	this->useGravity = useGravity;
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

void RigidBody::UpdateGravity(bool gravity)
{
	if (PxRigidDynamic* dynamicActor = rigidActor->is<PxRigidDynamic>())
	{
		dynamicActor->setActorFlag(PxActorFlag::eDISABLE_GRAVITY, !(gravity));

		if (useGravity)
		{
			dynamicActor->wakeUp();
		}
	}
}

void RigidBody::UpdateKinematic(bool isKinematic)
{
	if (PxRigidDynamic* dynamicActor = rigidActor->is<PxRigidDynamic>())
	{
		dynamicActor->setRigidBodyFlag(PxRigidBodyFlag::eKINEMATIC, isKinematic);
		if (!isKinematic)
		{
			dynamicActor->wakeUp();
		}
	}
}




void RigidBody::InitializeRigidBody(PhysXObject* object)
{
	physicsObject = object;
	modelTransform = &object->transform;
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
	case RigidBody::RigidBodyType::KINEMATIC:
		rigidActor = physics->createRigidDynamic(transform);
		
	}

	if (rigidActor)
	{
		rigidActor->userData = object;

		rigidActor->attachShape(*collider->GetShape());

		//rigidActor->setGlobalPose(transform);

		object->rigidActor = rigidActor;

		PhysXEngine::GetInstance().GetPhysicsScene()->addActor(*rigidActor);

		switch (rigidBodyType)
		{
		case RigidBody::RigidBodyType::DYNAMIC:
			UpdateGravity(useGravity);
			break;
		case RigidBody::RigidBodyType::KINEMATIC:
			UpdateGravity(useGravity);
			UpdateKinematic(isKinematic);
			break;
		}
	}
	

	isRigidBodyInitilized = true;

}

