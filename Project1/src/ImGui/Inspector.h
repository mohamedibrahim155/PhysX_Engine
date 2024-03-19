#pragma once
#include "../ImGui/BasePanel.h"
#include <iostream>
class Inspector : public BasePanel
{


public:

	void OnRender(float windowWidth, float windowHeight) override;

private: 

	void DrawEntityProperties();

};

