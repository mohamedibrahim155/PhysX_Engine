#pragma once
#include "../ImGui/BasePanel.h"
#include <iostream>

class EntityManager;
class LightManager;

class Heirachy : public BasePanel
{
public:

	Heirachy();
	void OnRender(float windowWidth, float windowHeight) override;

	EntityManager* entityManager = nullptr;
	LightManager* lightManager = nullptr;

private :

	void ShowAllEntities();
	void ShowLights();
};

