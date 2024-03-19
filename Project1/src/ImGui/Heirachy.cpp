#include "Heirachy.h"
#include "../EntityManager/EntityManager.h"
#include "../LightManager.h"
Heirachy::Heirachy()
{
    entityManager = &EntityManager::GetInstance();
    lightManager = &LightManager::GetInstance();
}

void Heirachy::OnRender(float windowWidth, float windowHeight)
{

    
    if (!isPanelOpen)
    {
        return;
    }

    if  (!ImGui::Begin("Hierarchy",&isPanelOpen) || !isEnable)
    {
        ImGui::End();
        return;
    }

    ShowAllEntities();
    ShowLights();
    ImGui::End();

    

}

void Heirachy::ShowAllEntities()
{
    if (!ImGui::CollapsingHeader("Entities", ImGuiTreeNodeFlags_DefaultOpen))
    {
        return;
    }

    std::unordered_map<std::string, Entity*>::iterator it;

    for (it = entityManager->listOfEntities.begin(); it != entityManager->listOfEntities.end(); ++it)
    {
        it->second->SceneDraw();
    }
}

void Heirachy::ShowLights()
{
    if (!ImGui::CollapsingHeader("Lights", ImGuiTreeNodeFlags_DefaultOpen))
    {
        return;
    }
    std::vector<Light*> lights = lightManager->GetLightList();

    for (Light* light : lights)
    {
        light->SceneDraw();
    }

}
