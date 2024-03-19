#pragma once
#include <unordered_map>
#include <iostream>
#include "Entity.h"

class EntityManager
{
public:
	static EntityManager& GetInstance();

	std::unordered_map<std::string, Entity*> listOfEntities;

	void AddEntity(Entity* entity);
	void AddEntity(const std::string& entityId,Entity* entity);
	void RemoveEntity(Entity* entity);
	void RemoveEntity(const std::string& entityId);

	void Start();
	void Update(float deltaTime);
	void Destroy(Entity* entity);
	void Render();

private :
	std::unordered_map<std::string, Entity*>::iterator it;
	std::vector<std::string> destroyedEntityList;
};

