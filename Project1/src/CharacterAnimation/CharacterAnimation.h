#pragma once
#include "../SkinnedMeshRenderer.h"
#include "../InputManager/InputManager.h"
class CharacterAnimation : public SkinnedMeshRenderer,public iInputObserver
{
public:
	CharacterAnimation();
	
	~CharacterAnimation();

	// Inherited via iInputObserver
	void OnKeyPressed(const int& key) override;
	void OnKeyReleased(const int& key) override;
	void OnKeyHold(const int& key) override;

	
	 void SceneDraw() override;
	 void DrawProperties() override;


	 void Start() override;
	 void Update(float deltaTime) override;
	 void Render() override;
	 void OnDestroy() override;

	 bool isAnimationPlay = false;

};

