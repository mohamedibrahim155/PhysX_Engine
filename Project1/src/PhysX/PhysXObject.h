#pragma once
#include "PxPhysicsAPI.h"
#include "RigidBody.h"
#include "../model.h"

using namespace physx;

class PhysXObject : public Model
{
public:
	PhysXObject();
	~PhysXObject();

	void Initialize(RigidBody::RigidBodyType bodyType , BaseCollider::ColliderShape colliderShape);

	void DrawProperties()override;
	void SceneDraw()override;
	void Render()override;

	RigidBody* GetRigidBody();

	PxRigidActor* rigidActor;
	BaseCollider* collider;
	RigidBody* rigidBody;
private:


	

};

