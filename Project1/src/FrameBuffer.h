#pragma once
#include "Renderer.h"

enum class FramebufferTextureFormat
{
	NONE = 0,

	//Color
	RGBA8,

	//Depth/Stencil
	DEPTH24STENCIL8,

	//Default
	DEPTH = DEPTH24STENCIL8

};

struct FramebufferTextureSpecification
{
	FramebufferTextureSpecification() = default;
	FramebufferTextureSpecification(FramebufferTextureFormat format)
	:textureFormat(format)
	{
	}

	FramebufferTextureFormat textureFormat = FramebufferTextureFormat::NONE;
};


struct FramebufferAttachmentSpecification
{
	FramebufferAttachmentSpecification() = default;
	FramebufferAttachmentSpecification(std::initializer_list<FramebufferTextureSpecification> attachments)
		: Attachments(attachments) 
	{
	}

	std::vector<FramebufferTextureSpecification> Attachments;
};

struct FrameBufferSpecification
{

	uint32_t  width;
	uint32_t  height;
	uint32_t  samples = 1;
	FramebufferAttachmentSpecification attachments;
	bool swapChainTarget = false;
};
class FrameBuffer
{
public:

	FrameBuffer( FrameBufferSpecification& specs);
	~FrameBuffer();

	void Bind();
	void Unbind();
	void Invalidate();
	void Resize(uint32_t width, uint32_t height);

	uint32_t& GetColorAttachmentID(int index = 0);
	unsigned int& GetRendererID();
	uint32_t& GetDepthAttachementID();
	FrameBufferSpecification specification;

private:

	unsigned int rendererID = 0;

	std::vector<FramebufferTextureSpecification> colorAttachmentSpecifications;
	FramebufferTextureSpecification depthAttachmentSpec;

	std::vector<uint32_t> colorAttachmentsID;
	uint32_t depthAttachmentID = 0;

};

