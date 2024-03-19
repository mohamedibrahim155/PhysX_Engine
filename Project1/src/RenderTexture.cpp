#include "RenderTexture.h"

RenderTexture::RenderTexture(FrameBufferSpecification framebufferSpec)
{
	framebuffer = new FrameBuffer(framebufferSpec);
}

RenderTexture::~RenderTexture()
{
}

void RenderTexture::Bind()
{
	GLCALL(glBindTexture(GL_TEXTURE_2D, framebuffer->GetColorAttachmentID()));
}

void RenderTexture::Unbind()
{
	GLCALL(glBindTexture(GL_TEXTURE_2D, 0));
}

void RenderTexture::SetTextureSlot(int place)
{	
	GLCALL(glActiveTexture(GL_TEXTURE0 + place));
}

void RenderTexture::DrawProperties()
{
}

void RenderTexture::SceneDraw()
{
}

void RenderTexture::CreateRenderTexture(FrameBufferSpecification framebufferSpec)
{
	framebuffer = new FrameBuffer(framebufferSpec);
}
