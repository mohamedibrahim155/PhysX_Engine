#include "PhysXEngine.h"

PhysXEngine::PhysXEngine()
{
	InitializePhysX();
}

PhysXEngine::~PhysXEngine()
{
	ShutDown();
}

PhysXEngine& PhysXEngine::GetInstance()
{
	static PhysXEngine instance;

	return instance;
}

void PhysXEngine::InitializePhysX()
{
	foundation = PxCreateFoundation(PX_PHYSICS_VERSION, allocator, errorCallback);

	physXDebuggerDisplay = PxCreatePvd(*foundation);
	PxPvdTransport* transport = PxDefaultPvdSocketTransportCreate(host.c_str(), 5425, 10);
	physXDebuggerDisplay->connect(*transport, PxPvdInstrumentationFlag::eALL);

	physics = PxCreatePhysics(PX_PHYSICS_VERSION, *foundation, PxTolerancesScale(), true, physXDebuggerDisplay);



	PxSceneDesc sceneDesc(physics->getTolerancesScale());
	sceneDesc.gravity = PxVec3(0.0f, -9.81f, 0.0f);
	dispatcher = PxDefaultCpuDispatcherCreate(2);
	sceneDesc.cpuDispatcher = dispatcher;
	sceneDesc.filterShader = PxDefaultSimulationFilterShader;
	scene = physics->createScene(sceneDesc);


	PxPvdSceneClient* pvdClient = scene->getScenePvdClient();

	if (pvdClient)
	{
		pvdClient->setScenePvdFlag(PxPvdSceneFlag::eTRANSMIT_CONSTRAINTS, true);
		pvdClient->setScenePvdFlag(PxPvdSceneFlag::eTRANSMIT_CONTACTS, true);
		pvdClient->setScenePvdFlag(PxPvdSceneFlag::eTRANSMIT_SCENEQUERIES, true);
	}

	pxMaterial = physics->createMaterial(defaultPhysicsMaterial.staticFriction, defaultPhysicsMaterial.dynamicFriction, defaultPhysicsMaterial.bounciness);

	pxMaterial->setDynamicFriction(PxCombineToLocal(defaultPhysicsMaterial.frictionCombine));
	pxMaterial->setRestitutionCombineMode(PxCombineToLocal(defaultPhysicsMaterial.bounceCombine));


	PxRigidStatic* groundPlane = PxCreatePlane(*physics, PxPlane(0, 1, 0, 0), *pxMaterial);

	scene->addActor(*groundPlane);



}

void PhysXEngine::ShutDown()
{
	PX_RELEASE(scene);
	PX_RELEASE(dispatcher);
	PX_RELEASE(physics);
	if (physXDebuggerDisplay)
	{
		PxPvdTransport* transport = physXDebuggerDisplay->getTransport();
		physXDebuggerDisplay->release();	physXDebuggerDisplay = NULL;
		PX_RELEASE(transport);
	}
	PX_RELEASE(foundation);
}

void PhysXEngine::Update(float deltaTime)
{
	if (scene)
	{
		scene->simulate(deltaTime);
		scene->fetchResults(true);
	}
}

void PhysXEngine::AddPhysXObject(PhysXObject* object)
{
	scene->addActor(*object->GetRigidBody()->GetPxRigidBody());

	physicsObjects.push_back(object);
}

void PhysXEngine::RemovePhysXObject(PhysXObject* object)
{
	std::vector<PhysXObject*>::iterator it = std::find(physicsObjects.begin(), physicsObjects.end(), object);

	if (it!=physicsObjects.end())
	{
		physicsObjects.erase(it);
	}
}


PxPhysics* PhysXEngine::GetPhysics()
{
	return physics;
}

PxScene* PhysXEngine::GetPhysicsScene() const
{
	return scene;
}

PhysicsMaterial* PhysXEngine::GetDefaultPhysicsMaterial() 
{
	return &defaultPhysicsMaterial;
}

PxMaterial* PhysXEngine::GetPxPhysicsMaterial()
{
	return pxMaterial;
}


