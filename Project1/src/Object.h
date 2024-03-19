#pragma once
#include <string>
#include <imgui.h>
#include <imgui_internal.h>

#include "ImGui/ImGuiUtils.h"
class Object
{
public :
//	Object();
  //  ~Object();

	static unsigned int ID;
	


	bool isSelected = false;
	bool isEnabled = true;

	virtual void DrawProperties() = 0;
	virtual void SceneDraw() = 0;
};

