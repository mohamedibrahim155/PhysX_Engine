
#pragma once
#include"Renderer.h"
class VertexBuffer
{
public:
	//VertexBuffer() { }
	VertexBuffer(const void* data, unsigned int size);
	~VertexBuffer();
	void Bind();
	void Unbind();
	void UpdateVertexData(unsigned int size, const void* data);

private:
	unsigned int m_RendererID;

};

