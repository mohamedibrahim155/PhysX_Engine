#pragma once
#include "PxPhysicsAPI.h"
#include "PhysXObject.h"
#include "PhysicsMaterial/PhysicsMaterial.h"
#include <string>
#include <vector>
#include "TriggerEventCallback.h"

using namespace physx;

//static PxDefaultAllocator		gAllocator;
//static PxDefaultErrorCallback	gErrorCallback;
//static PxFoundation* gFoundation = NULL;
//static PxPhysics* gPhysics = NULL;
//static PxDefaultCpuDispatcher* dispatcher = NULL;
//static PxScene* gScene = NULL;
//static PxMaterial* gMaterial = NULL;
//static PxPvd* physxDebbuggerDisplay = NULL;


class PhysXEngine
{
	PhysXEngine();
	~PhysXEngine();
public:
	static PhysXEngine& GetInstance();


	PxPhysics* GetPhysics();
	PxScene* GetPhysicsScene() const;
	PhysicsMaterial* GetDefaultPhysicsMaterial();
	PxMaterial* GetPxPhysicsMaterial();

	void InitializePhysX();
	void ShutDown();

	void Update(float deltaTime);
	void UpdatePhysicsRenders();

	void AddPhysXObject(PhysXObject* object);
	void RemovePhysXObject(PhysXObject* object);
	void InitializePhysXObjects();

private:

	PxScene* scene = NULL;
    PxPhysics* physics = NULL;
	PxFoundation* foundation = NULL;
	PxMaterial* pxMaterial = NULL;
	PxDefaultAllocator allocator;
    PxDefaultErrorCallback	errorCallback;
    PxDefaultCpuDispatcher* dispatcher = NULL;
	PxPvd* physXDebuggerDisplay;

	CollisionEventCallback collisionEventCallback;
	PhysicsMaterial defaultPhysicsMaterial;
	std::vector<PhysXObject*> physicsObjects;

	const  static unsigned int MAXNUM_ACTOR_SHAPES = 128;
	const std::string host = "127.0.0.1";
	bool isApplicationPlay = false;

	static PxFilterFlags ContactReportFilterShader(PxFilterObjectAttributes attributes0, PxFilterData filterData0,
		PxFilterObjectAttributes attributes1, PxFilterData filterData1,
		PxPairFlags& pairFlags, const void* constantBlock, PxU32 constantBlockSize);
	
};

