#pragma once
#include <PxRigidBody.h>
#include <PxRigidDynamic.h>
#include <PxRigidStatic.h>
#include "Collider/BoxCollider.h"
#include "Collider/SphereCollider.h"
#include "Collider/CapsuleCollider.h"
#include "Collider/MeshCollider.h"
#include <PxPhysics.h>
using namespace physx;

class PhysXObject;
class Transform;

struct Contraints
{
	Contraints() = default;
	Contraints(bool x, bool y, bool z) : x(x), y(y), z(z) {};

	bool x = false;
	bool y = false;
	bool z = false;
};
class RigidBody
{
public:

	enum class RigidBodyType
	{
		DYNAMIC = 0,
		STATIC =1,
	};
	RigidBody();
	~RigidBody();

	PxRigidDynamic* AsDynamicRigidBody();
	PxRigidStatic* AsStaticRigidBody();
	PxRigidActor* GetPxRigidBody();

	void InitializeRigidBody(PhysXObject* object);
	void SetRigidBodyType(RigidBodyType type); 
	void SetDrag(float drag);
	void SetMass(float mass);
	void SetKinematic(bool isKinematic);
	void SetGravity(bool useGravity);
	void SetVelocity(const glm::vec3& velocity);
	void DrawRigidProperties();

	bool IsRigidBodyIntialized() const { return isRigidBodyInitilized; };

	BaseCollider* collider;
	RigidBodyType rigidBodyType;

private:

	PxRigidActor* rigidActor =  nullptr;
	PxPhysics*    physics = nullptr;
	PxTransform   pxTransform;
	PhysXObject*  physicsObject =  nullptr;
	Transform*    modelTransform = nullptr;

	bool  isKinematic = false;
	bool  useGravity = true;
	bool  isRigidBodyInitilized = false;
	float mass = 1;

	void UpdateGravity(bool gravity);
	void UpdateKinematic(bool isKinematic);

	void SetPositionFreezeContraints(Contraints& position);
	void SetRotationFreezeContraints(Contraints& rotation);

	std::string type[2] = { "DYNAMIC", "STATIC" };

};

