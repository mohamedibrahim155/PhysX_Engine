#include "PhysXEngine.h"
#include "PhysXUtils.h"
PhysXEngine::PhysXEngine()
{
	//InitializePhysX();
}

PhysXEngine::~PhysXEngine()
{
	//ShutDown();
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

	defaultPhysicsMaterial.staticFriction = 0.6f;
	defaultPhysicsMaterial.dynamicFriction = 0.6f;
	defaultPhysicsMaterial.bounciness = 0;

	pxMaterial = physics->createMaterial(
		PxReal(defaultPhysicsMaterial.staticFriction),
		PxReal(defaultPhysicsMaterial.dynamicFriction),
		PxReal(defaultPhysicsMaterial.bounciness));

	/*pxMaterial = physics->createMaterial(
		0.5f,
		0,
		1);*/

	pxMaterial->setDynamicFriction(PxCombineToLocal(defaultPhysicsMaterial.frictionCombine));
	pxMaterial->setRestitutionCombineMode(PxCombineToLocal(defaultPhysicsMaterial.bounceCombine));
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

		UpdatePhysicsRenders();
	}
}

void PhysXEngine::UpdatePhysicsRenders()
{
	for (PhysXObject* physXObject : physicsObjects)
	{
		if (physXObject->rigidBody->rigidBodyType == RigidBody::RigidBodyType::STATIC)
		{
			continue;
		}

		PxU32 nbActors = scene->getNbActors(PxActorTypeFlag::eRIGID_DYNAMIC | PxActorTypeFlag::eRIGID_STATIC);

		if (nbActors)
		{
			std::vector<PxRigidActor*> actors(nbActors);
			scene->getActors(PxActorTypeFlag::eRIGID_DYNAMIC | PxActorTypeFlag::eRIGID_STATIC, reinterpret_cast<PxActor**>(&actors[0]), nbActors);


			PxShape* shapes[MAXNUM_ACTOR_SHAPES];

			const PxU32 numActors = actors.size();

			for (PxU32 i = 0; i < numActors; i++)
			{
				const PxU32 nbShapes = actors[i]->getNbShapes();
				PX_ASSERT(nbShapes <= MAX_NUM_ACTOR_SHAPES);

				actors[i]->getShapes(shapes, nbShapes);


				
				for (PxU32 j = 0; j < nbShapes; j++)
				{
					const PxTransform shapePose = PxShapeExt::getGlobalPose(*shapes[j], *actors[i]);


					const PxVec3 translation = shapePose.p;
					const PxQuat rotation = shapePose.q;

					glm::quat glmRotation = PxQuatToGLM(rotation);
					glm::vec3 position = PxVec3ToGLM(translation);

					if (actors[i]->userData == physXObject)
					{
						physXObject->transform.SetPosition(position -  physXObject->collider->offsetPosition);
						physXObject->transform.SetQuatRotation(glmRotation);
					}
				}
			}



		}

	}
}

void PhysXEngine::AddPhysXObject(PhysXObject* object)
{
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

void PhysXEngine::InitializePhysXObjects()
{
	if (isApplicationPlay)
	{
		return;
	}
	for (PhysXObject* physXObject : physicsObjects)
	{
		physXObject->rigidBody->InitializeRigidBody(physXObject);
	}

	isApplicationPlay = true;
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


