#pragma once
#include "BasePanel.h"
class ToolPanel : public BasePanel
{
public:
	// Inherited via BasePanel
	void OnRender(float windowWidth, float windowHeight) override;

	bool* isApplicationPlayMode = nullptr;
};

