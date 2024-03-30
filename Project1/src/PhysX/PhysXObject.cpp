#include "PhysXObject.h"
#include "PhysXEngine.h"
PhysXObject::PhysXObject()
{
}

PhysXObject::~PhysXObject()
{
	if (rigidBody)
	{
		delete rigidBody;
	}
	if (collider)
	{
		delete collider;
	}

	if (rigidActor)
	{
		rigidActor->release();
	}
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

	case BaseCollider::ColliderShape::CAPSULE:
		collider = new CapsuleCollider();
		break;

	case BaseCollider::ColliderShape::MESH:
		collider = new MeshCollider();
		break;
	}

	collider->InitializeCollider(this);

    rigidBody->SetRigidBodyType(bodyType);

	PhysXEngine::GetInstance().AddPhysXObject(this);
}

void PhysXObject::DrawProperties()
{
	Model::DrawProperties();

	if (collider == nullptr)  return;

	collider->DrawColliderProperties();
}

void PhysXObject::SceneDraw()
{
	Model::SceneDraw();
}



void PhysXObject::Render()
{
	if (collider)
	{
		collider->DrawShape();
	}
}

void PhysXObject::Start()
{
}

void PhysXObject::Update(float deltaTime)
{
}

void PhysXObject::OnDestroy()
{
}

void PhysXObject::OnTriggerEnter(PhysXObject* otherObject)
{
	//std::cout << "On Trigger Enter " << std::endl;
}

void PhysXObject::OnTriggerStay(PhysXObject* otherObject)
{
	//std::cout << "On Trigger stay" << std::endl;
}

void PhysXObject::OnTriggerExit(PhysXObject* otherObject)
{
	//std::cout << "On Trigger Exit" << std::endl;
}

void PhysXObject::OnCollisionEnter(PhysXObject* otherObject, CollisionInfo& collisionInfo)
{
	//std::cout << "On Collision Enter" << std::endl;
}

void PhysXObject::OnCollisionStay(PhysXObject* otherObject)
{
	//std::cout << "On Collision stay" << std::endl;
}

void PhysXObject::OnCollisionExit(PhysXObject* otherObject)
{
	//std::cout << "On Collision Exit" << std::endl;
}



RigidBody* PhysXObject::GetRigidBody()
{
	return rigidBody;
}

