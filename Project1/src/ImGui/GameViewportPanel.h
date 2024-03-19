#pragma once
#include "BasePanel.h"
#include "../FrameBuffer.h"
class GameViewportPanel : public BasePanel
{
public:

	// Inherited via BasePanel
	void OnRender(float windowWidth, float windowHeight) override;

	FrameBuffer* frameBuffer = nullptr;
	ImVec2 gameViewportResolution;
	ImVec2 gameViewportSize;

	ImVec4 windowColor = ImVec4(0.21f, 0.1f, 0.1f, 1.0f);
};

