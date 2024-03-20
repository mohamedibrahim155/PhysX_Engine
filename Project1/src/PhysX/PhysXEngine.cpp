#include "PhysXEngine.h"

PhysXEngine::PhysXEngine()
{
}

PhysXEngine::~PhysXEngine()
{
}

PhysXEngine& PhysXEngine::GetInstance()
{
	static PhysXEngine instance;

	return instance;
}

void PhysXEngine::InitializePhysX()
{
	//foundation = PxCreateFoundation(PX_PHYSICS_VERSION, gAllocator, gErrorCallback);
}
