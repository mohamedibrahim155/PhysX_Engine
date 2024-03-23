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

	
   rigidBody->SetRigidBodyType(bodyType);

	rigidBody->SetPosition(transform.position);

	rigidBody->InitilizeRigidBody(colliderShape);



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
}

void PhysXObject::OnDestroy()
{
}

RigidBody* PhysXObject::GetRigidBody()
{
	return rigidBody;
}
