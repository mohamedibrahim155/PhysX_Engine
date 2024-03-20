#pragma once
#include "PxPhysicsAPI.h"
#include "PhysXObject.h"

using namespace physx;

//static PxDefaultAllocator		gAllocator;
//static PxDefaultErrorCallback	gErrorCallback;
//static PxFoundation* gFoundation = NULL;
//static PxPhysics* gPhysics = NULL;
//static PxDefaultCpuDispatcher* gDispatcher = NULL;
//static PxScene* gScene = NULL;
//static PxMaterial* gMaterial = NULL;
//static PxPvd* gPvd = NULL;


class PhysXEngine
{

	PhysXEngine();
	~PhysXEngine();
public:
	static PhysXEngine& GetInstance();

private:

	PxScene* scene = NULL;
    PxPhysics* physics = NULL;
	PxFoundation* foundation = NULL;
	PxMaterial* material = NULL;

	void InitializePhysX();
};

