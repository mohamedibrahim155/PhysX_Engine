#include "VertexBuffer.h"



VertexBuffer::VertexBuffer(const void* data, unsigned int size)
{
	GLCALL(glGenBuffers(1, &m_RendererID));
	GLCALL(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
	GLCALL(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

VertexBuffer::~VertexBuffer()
{
	GLCALL(glDeleteBuffers(1, &m_RendererID));
}

void VertexBuffer::Bind()
{
	GLCALL(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID))
}

void VertexBuffer::Unbind()
{
	GLCALL(glBindBuffer(GL_ARRAY_BUFFER, 0))

}

void VertexBuffer::UpdateVertexData(unsigned int size, const void* data)
{
	Bind();
	GLCALL(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}
