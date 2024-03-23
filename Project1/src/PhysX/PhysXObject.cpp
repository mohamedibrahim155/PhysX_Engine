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
	case BaseCollider::ColliderShape::NONE:
		break;
	case BaseCollider::ColliderShape::BOX:
		collider = new BoxCollider();
		break;
	case BaseCollider::ColliderShape::SPHERE:
		break;
	}

	collider->InitializeCollider(this);

    rigidBody->SetRigidBodyType(bodyType);

	//rigidBody->InitializeRigidBody(this);


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

void PhysXObject::Start()
{
}

void PhysXObject::Update(float deltaTime)
{
}

void PhysXObject::Render()
{
	if (collider)
	{
		collider->Render();
	}
}

void PhysXObject::OnDestroy()
{
}

RigidBody* PhysXObject::GetRigidBody()
{
	return rigidBody;
}
