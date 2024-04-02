#pragma once
#include "../Object.h"
#include"../Transform.h"
#include "../Layer.h"

class EntityManager;
class EditorLayout;

class Entity : public Object
{
public:

	std::string entityID;
	std::string tag = "untagged";
	std::string name = "EmptyGameObject";

	unsigned int entityLayer = Layer::DEFAULT;

	Transform transform;

	bool isStartInvoked = false;

	virtual ~Entity() {};

	virtual void InitializeEntity(Entity* entity);
	virtual void Start() = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void OnDestroy() = 0;
	virtual void Render() = 0;
	virtual void Destroy();

	 //Inherited from Object
	 virtual void DrawProperties();
	 virtual void SceneDraw();


};

