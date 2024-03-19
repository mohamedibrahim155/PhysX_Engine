#include "ToolPanel.h"

void ToolPanel::OnRender(float windowWidth, float windowHeight)
{
    if (!isPanelOpen)
    {
        return;
    }

    ImGuiWindowFlags flag = 0;


    flag |= ImGuiWindowFlags_NoTitleBar;
    flag |= ImGuiWindowFlags_NoResize;
    flag |= ImGuiWindowFlags_MenuBar;

    float panelSizeX = windowWidth;
    float panelSizeY = windowHeight / 70;

    float panelPosX = 0;
    float panelPosY = 0 + panelSizeY / 10;

    ImGui::SetNextWindowSize(ImVec2(panelSizeX, panelSizeY));
    ImGui::SetNextWindowPos(ImVec2(panelPosX, panelPosY));


    //ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));

    if (!ImGui::Begin("ToolPanel", &isPanelOpen, flag) || !isEnable)
    {
        ImGui::End();
        //  ImGui::PopStyleVar();
        return;

    }

	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			ImGui::EndMenu();

		}
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(panelSizeX * 0.5f, 0));
		ImGui::Spacing();
		ImGui::PopStyleVar();

		if (ImGui::Button((*isApplicationPlayMode) ? "PAUSE" : "PLAY"))
		{
			*isApplicationPlayMode = !(*isApplicationPlayMode);
		}

		ImGui::EndMenuBar();
	}


	ImGui::End();

}
