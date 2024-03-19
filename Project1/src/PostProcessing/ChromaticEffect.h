#pragma once
#include "BaseEffect.h"
#include "../Quad.h"
#include "SinglePassEffect.h"

class ChromaticEffect : public SinglePassEffect
{
public :

	ChromaticEffect();
	ChromaticEffect(float width , float height);
	
	// Inherited via BaseEffect
	//void ApplyEffect(FrameBuffer* frameBuffer) override;
	void DrawProperties() override;
	void SceneDraw() override;
	void InitializeEffect(const std::string& vertex, const std::string& fragment) override;

	void SetShaderUniforms() override;
	FrameBuffer* chromaticFramebuffer;
private:
	float aberrationValue = 10;



};

