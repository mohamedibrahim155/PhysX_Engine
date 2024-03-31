#pragma once
#include "PxPhysicsAPI.h"
#include "RigidBody.h"
#include "../model.h"
#include "CollisionInfo.h"
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

	virtual void Start() override;
	virtual void Update(float deltaTime) override;
	virtual void OnDestroy() override;

	virtual void OnTriggerEnter(PhysXObject* otherObject);
	virtual void OnTriggerStay(PhysXObject* otherObject);
	virtual void OnTriggerExit(PhysXObject* otherObject);

	virtual void OnCollisionEnter(PhysXObject* otherObject, CollisionInfo& collisionInfo);
	virtual void OnCollisionStay(PhysXObject* otherObject);
	virtual void OnCollisionExit(PhysXObject* otherObject);

	RigidBody* GetRigidBody();
	glm::vec3 GetVelocity();

	PxRigidActor* rigidActor = nullptr;
	BaseCollider* collider;
	RigidBody* rigidBody;

private:


	

};

