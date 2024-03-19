#pragma once
#include"IndexBuffer.h"


IndexBufferObject::IndexBufferObject(const unsigned int* data, unsigned int count) : Count(count)	
{
	GLCALL(glGenBuffers(1, &m_RendererID));
	GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
	GLCALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));
}

IndexBufferObject::~IndexBufferObject()
{
	GLCALL(glDeleteBuffers(1, &m_RendererID));
}

 void IndexBufferObject::Bind()
{
	GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID))
}

 void IndexBufferObject::Unbind()
{
	GLCALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0))
}

 inline unsigned int IndexBufferObject::GetCount()
 {
	 return this->Count;
 }
