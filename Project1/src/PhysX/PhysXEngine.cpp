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
	sceneDesc.filterShader = ContactReportFilterShader;
	sceneDesc.simulationEventCallback = &collisionEventCallback;
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
#pragma region Old



	//for (PhysXObject* physXObject : physicsObjects)
	//{
	//	if (physXObject->rigidBody->rigidBodyType == RigidBody::RigidBodyType::STATIC)
	//	{
	//		continue;
	//	}

	//	PxU32 nbActors = scene->getNbActors(PxActorTypeFlag::eRIGID_DYNAMIC | PxActorTypeFlag::eRIGID_STATIC);

	//	if (nbActors)
	//	{
	//		std::vector<PxRigidActor*> actors(nbActors);
	//		scene->getActors(PxActorTypeFlag::eRIGID_DYNAMIC | PxActorTypeFlag::eRIGID_STATIC, reinterpret_cast<PxActor**>(&actors[0]), nbActors);


	//		PxShape* shapes[MAXNUM_ACTOR_SHAPES];

	//		const PxU32 numActors = actors.size();

	//		for (PxU32 i = 0; i < numActors; i++)
	//		{
	//			const PxU32 nbShapes = actors[i]->getNbShapes();
	//			PX_ASSERT(nbShapes <= MAX_NUM_ACTOR_SHAPES);

	//			actors[i]->getShapes(shapes, nbShapes);


	//			
	//			for (PxU32 j = 0; j < nbShapes; j++)
	//			{
	//				const PxTransform shapePose = PxShapeExt::getGlobalPose(*shapes[j], *actors[i]);


	//				const PxVec3 translation = shapePose.p;
	//				const PxQuat rotation = shapePose.q;

	//				glm::quat glmRotation = PxQuatToGLM(rotation);
	//				glm::vec3 position = PxVec3ToGLM(translation);

	//				if (actors[i]->userData == physXObject)
	//				{
	//					physXObject->transform.SetPosition(position -  physXObject->collider->offsetPosition);
	//					physXObject->transform.SetQuatRotation(glmRotation);
	//				}
	//			}
	//		}



	//	}

	//}
#pragma endregion

	PxU32 nbActors = scene->getNbActors(PxActorTypeFlag::eRIGID_DYNAMIC | PxActorTypeFlag::eRIGID_STATIC);

	if (nbActors)
	{
		std::vector<PxRigidActor*> actors(nbActors);
		scene->getActors(PxActorTypeFlag::eRIGID_DYNAMIC | PxActorTypeFlag::eRIGID_STATIC, reinterpret_cast<PxActor**>(&actors[0]), nbActors);

		PxShape* shapes[MAXNUM_ACTOR_SHAPES];

		const PxU32 numActors = actors.size();

		for (PxRigidActor* actor : actors)
		{
			if (actor->userData == nullptr) continue;

			PhysXObject* physObject = (PhysXObject*)actor->userData;

			if (physObject->rigidBody->rigidBodyType == RigidBody::RigidBodyType::STATIC)
			{
				continue;
			}

			const PxU32 nbShapes = actor->getNbShapes();
			PX_ASSERT(nbShapes <= MAX_NUM_ACTOR_SHAPES);

			actor->getShapes(shapes, nbShapes);

			glm::vec3 position =glm::vec3(0);
			glm::vec3 rotation = glm::vec3(0);

			

			for (PxU32 j = 0; j < nbShapes; j++)
			{
				
				const PxTransform shapePose = actor->getGlobalPose();
				//const PxMat44 shapePose(actor->getGlobalPose());
				//const PxGeometry& geom = shapes[j]->getGeometry();

				const PxVec3 translation = shapePose.p;

				//PxMat33 rotationMatrix;
				/*PxMat33 rotationMatrix;
				rotationMatrix[0][0] = shapePose[0][0];
				rotationMatrix[0][1] = shapePose[0][1];
				rotationMatrix[0][2] = shapePose[0][2];

				rotationMatrix[1][0] = shapePose[1][0];
				rotationMatrix[1][1] = shapePose[1][1];
				rotationMatrix[1][2] = shapePose[1][2];

				rotationMatrix[2][0] = shapePose[2][0];
				rotationMatrix[2][1] = shapePose[2][1];
				rotationMatrix[2][2] = shapePose[2][2];*/

				const PxQuat pxRotation = shapePose.q;


				//PxQuat pxRotation(rotationMatrix);

				position += PxVec3ToGLM(translation);
				rotation += glm::degrees(glm::eulerAngles(PxQuatToGLM(pxRotation)));

			}

			position /= nbShapes;
			rotation /= nbShapes;

			if (physObject->freezePosition.x)
			{
				position.x = physObject->transform.position.x;
			}
			if (physObject->freezePosition.y)
			{
				position.y = physObject->transform.position.y;

			}
			if (physObject->freezePosition.z)
			{
				position.y = physObject->transform.position.y;
			}



			physObject->transform.SetPosition(position - physObject->collider->GetOffsetPosition());
			physObject->transform.SetRotation(rotation);

			PxVec3 colliderPos = GLMToPxVec3(physObject->collider->GetPosition());
			PxQuat colliderRot = GLMToPxQuat(physObject->collider->GetRotation());

			physObject->rigidActor->setGlobalPose(PxTransform(colliderPos, colliderRot));
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

PxFilterFlags PhysXEngine::ContactReportFilterShader(PxFilterObjectAttributes attributes0, PxFilterData filterData0, PxFilterObjectAttributes attributes1, PxFilterData filterData1, PxPairFlags& pairFlags, const void* constantBlock, PxU32 constantBlockSize)
{
	PX_UNUSED(attributes0);
	PX_UNUSED(attributes1);
	PX_UNUSED(filterData0);
	PX_UNUSED(filterData1);
	PX_UNUSED(constantBlockSize);
	PX_UNUSED(constantBlock);

	// all initial and persisting reports for everything, with per-point data
	pairFlags = PxPairFlag::eSOLVE_CONTACT | PxPairFlag::eDETECT_DISCRETE_CONTACT
		| PxPairFlag::eNOTIFY_TOUCH_FOUND
		| PxPairFlag::eNOTIFY_TOUCH_LOST
		| PxPairFlag::eNOTIFY_CONTACT_POINTS;

	return PxFilterFlag::eDEFAULT;
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


