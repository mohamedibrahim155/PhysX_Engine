#pragma once

#include "../Object.h"
#include <vector>
#include "Heirachy.h"
#include "Inspector.h"
#include "WindowDockingPanel.h"
#include "SceneViewportPanel.h"
#include "ToolPanel.h"
#include "GameViewportPanel.h"
class ApplicationRenderer;
class EditorLayout
{
public :
	static EditorLayout& GetInstance();

	void InitializeEditors();
	void SetSelectedObjects(std::vector<Object*> objects);
	void SetSelectedObjectsEnable(bool isEnable);

	bool IsViewportHovered();

	Object* GetCurrentSelectedObject();
	std::vector<Object*> GetSelectedObjects();

	ApplicationRenderer* applicationRenderer;
private:

	Heirachy* hierarchyPanel;
	Inspector* inspectorPanel;
	WindowDockingPanel* windowDockingPanel;
	SceneViewportPanel* sceneViewportPanel;
	ToolPanel* toolPanel;
	GameViewportPanel* gameviewportPanel;

	Object* currentSelectedObject = nullptr;

	std::vector<Object*> selectedObjectsList;

};

