#include "Entity.h"
#include "EntityManager.h"
#include "../ImGui/EditorLayout.h"

void Entity::InitializeEntity(Entity* entity)
{
	EntityManager::GetInstance().AddEntity(entity);
}

void Entity::Destroy()
{
	EntityManager::GetInstance().RemoveEntity(entityID);
}

void Entity::DrawProperties()
{
	ImGui::InputText("##EntityName", &name[0], 256);
	ImGui::SameLine();
	ImGui::InputText("##Tag", &tag[0], 256);
	transform.DrawProperties();
}

void Entity::SceneDraw()
{
	if (ImGui::Selectable(name.c_str(), &isSelected))
	{
		EditorLayout::GetInstance().SetSelectedObjects({ this });
	}
}
