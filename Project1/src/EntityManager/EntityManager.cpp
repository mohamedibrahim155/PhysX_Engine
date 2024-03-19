#include "EntityManager.h"

EntityManager& EntityManager::GetInstance()
{
    // TODO: insert return statement here

    static EntityManager instance;

    return instance;
}

void EntityManager::AddEntity(Entity* entity)
{
    std::string entityId = std::to_string((int)listOfEntities.size());
    entity->entityID = entityId;
    listOfEntities[entityId] = entity;
}

void EntityManager::AddEntity(const std::string& entityId, Entity* entity)
{
    listOfEntities[entityId] = entity;
    entity->entityID = entityId;

}

void EntityManager::RemoveEntity(Entity* entity)
{
    for (it = listOfEntities.begin(); it!= listOfEntities.end(); it++)
    {
        if (it->second == entity)
        {
            Destroy(entity);

            destroyedEntityList.push_back(entity->entityID);

            return;

        }
    }
}

void EntityManager::RemoveEntity(const std::string& entityId)
{
    for (it = listOfEntities.begin(); it != listOfEntities.end(); it++)
    {
        if (it->first == entityId)
        {
            Destroy(listOfEntities[entityId]);

            destroyedEntityList.push_back(entityId);

            return;
        }
    }
}

void EntityManager::Start()
{
    for (it = listOfEntities.begin(); it!=listOfEntities.end(); it++)
    {
        it->second->Start();
        it->second->isStartInvoked = true;
    }
}

void EntityManager::Update(float deltaTime)
{
    for (const std::string& id : destroyedEntityList)
    {
        listOfEntities[id] = nullptr;
        delete listOfEntities[id];

        listOfEntities.erase(id);
    }
    destroyedEntityList.clear();

    try
    {
        for (std::pair<const std::string&, Entity*> item : listOfEntities)
        {
            if (item.second->isEnabled && !item.second->isStartInvoked)
            {
                item.second->Start();
                item.second->isStartInvoked = true;
            }

            item.second->Update(deltaTime);
        }
    }
    catch (const std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }
}

void EntityManager::Destroy(Entity* entity)
{
    entity->OnDestroy();
}

void EntityManager::Render()
{
    for (const std::string& id : destroyedEntityList)
    {
        listOfEntities[id] = nullptr;
        delete listOfEntities[id];

        listOfEntities.erase(id);
    }
    destroyedEntityList.clear();

    try
    {
        for (std::pair<const std::string&, Entity*> item : listOfEntities)
        {
            if (item.second->isEnabled)
            {
                item.second->Render();
            }
        }
    }
    catch (const std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }
}
