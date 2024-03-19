#pragma once
#include "Renderer.h"


class IndexBufferObject
{
public:

	IndexBufferObject(const unsigned int* data, unsigned int count);
	~IndexBufferObject();
	void Bind();
	void Unbind();
	inline unsigned int GetCount();
private:
	unsigned int m_RendererID;
	unsigned int Count;
};


