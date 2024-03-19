#pragma once

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
class VertexArray
{
public:
	VertexArray();
	~VertexArray();

	unsigned int m_RendererID;

	void AddBuffer(  VertexBuffer& vb,  VertexBufferLayout& layout);

	void Bind();
	void Unbind();

private:

};


