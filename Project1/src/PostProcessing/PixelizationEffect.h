#pragma once
#include "BaseEffect.h"
#include "../Shader.h"
#include "../Quad.h"
#include "SinglePassEffect.h"
class PixelizationEffect : public SinglePassEffect
{
public:
	PixelizationEffect();
	PixelizationEffect(float width, float height);

	//void InitializeEffect();
	// Inherited via BaseEffect
	//void ApplyEffect(FrameBuffer* frameBuffer) override;
	void DrawProperties() override;
	void SceneDraw() override;
	// Inherited via SinglePassEffect
	void InitializeEffect(const std::string& vertex, const std::string& fragment) override;
	void SetShaderUniforms() override;
	Shader* pixelShader;

private :

	//float time = 0;
	
};

