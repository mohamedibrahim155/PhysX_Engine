#pragma once
#include "BaseTexture.h"
#include "FrameBuffer.h"
class RenderTexture : public BaseTexture
{
public:

	RenderTexture() = default;
	RenderTexture(FrameBufferSpecification framebufferSpec);
	~RenderTexture();
	// Inherited via BaseTexture
	void Bind() override;
	void Unbind() override;
	void SetTextureSlot(int place = 0) override;
	void DrawProperties() override;
	void SceneDraw() override;

	void CreateRenderTexture(FrameBufferSpecification framebufferSpec);

	FrameBuffer* framebuffer = nullptr;
};

