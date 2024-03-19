#pragma once
#include "../FrameBuffer.h"
#include "BasePanel.h"
#include "../Camera.h"
#include <ImGuizmo.h>
#include"../InputManager/InputManager.h"
class SceneViewportPanel : public BasePanel, public iInputObserver
{
public:
	SceneViewportPanel();
	void OnRender(float windowWidth, float windowHeight) override;

	FrameBuffer* frameBuffer = nullptr;

	ImVec2 viewportSize;
	ImGuizmo::OPERATION gizmoType = ImGuizmo::OPERATION::TRANSLATE;
	Camera* sceneViewportCamera;

	// Inherited via iInputObserver
	void OnKeyPressed(const int& key) override;
	void OnKeyReleased(const int& key) override;
	void OnKeyHold(const int& key) override;
};

