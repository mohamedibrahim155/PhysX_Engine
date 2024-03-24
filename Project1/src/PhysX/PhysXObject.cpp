#include "PhysXObject.h"
#include "PhysXEngine.h"
PhysXObject::PhysXObject()
{
}

PhysXObject::~PhysXObject()
{
}

void PhysXObject::Initialize(RigidBody::RigidBodyType bodyType, BaseCollider::ColliderShape colliderShape)
{
	rigidBody = new RigidBody();

	
	switch (colliderShape)
	{

	case BaseCollider::ColliderShape::BOX:
		collider = new BoxCollider();
		break;
	case BaseCollider::ColliderShape::SPHERE:
		collider = new SphereCollider();
		break;
	}

	collider->InitializeCollider(this);

    rigidBody->SetRigidBodyType(bodyType);

	PhysXEngine::GetInstance().AddPhysXObject(this);
}

void PhysXObject::DrawProperties()
{
	Model::DrawProperties();
}

void PhysXObject::SceneDraw()
{
	Model::SceneDraw();
}



void PhysXObject::Render()
{
	if (collider)
	{
		collider->Render();
	}
}



RigidBody* PhysXObject::GetRigidBody()
{
	return rigidBody;
}
