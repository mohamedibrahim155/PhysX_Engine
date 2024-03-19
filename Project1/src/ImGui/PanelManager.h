#pragma once
#include "BasePanel.h"
#include "Heirachy.h"
#include "Inspector.h"
#include <iostream>
#include <vector>



class PanelManager
{

public:

	static PanelManager& GetInstance();


	void DrawDockSpace();

	void AddPanel(BasePanel* panel);
	void RemovePanel(BasePanel* panel);
	void EnablePanel(BasePanel* panel);
	void DisablePanel(BasePanel* panel);

	void Update(float windowWidth, float windowHeight);
private:


	bool dockOpen = true;


	std::vector<BasePanel*> listOfPanels;
};

