#pragma once

#include<vector>
#include"Renderer.h"

struct VertexBufferElement
{
	unsigned int type;
	unsigned int count;
	unsigned char normalized;

	static unsigned int GetSizeType(unsigned int type)
	{
		switch (type)
		{
		case GL_FLOAT:
			return 4;
			break;
		case GL_UNSIGNED_INT: 
			return 4;
			break;
		}
		ASSERT(false);
		return 0;
	}

};

class VertexBufferLayout
{
public:
	VertexBufferLayout()
		: Stride(0)
	{

	}
	~VertexBufferLayout() 
	{
		elements.clear();
	}

	template<typename T>
	void Push(int count)
	{
		//static_assert(false);
	}

	template<>
	void Push<float>(int count)
	{
		VertexBufferElement vb;
		vb.type = GL_FLOAT;
		vb.count = count;
		vb.normalized = GL_FALSE;

		elements.push_back(vb);
		//Stride += count *  sizeof(GLfloat);
		Stride += count * VertexBufferElement::GetSizeType(GL_FLOAT);
	}

	template<>
	void Push<unsigned int>(int count)
	{
		VertexBufferElement vb;
		vb.type = GL_UNSIGNED_INT;
		vb.count = count;
		vb.normalized = GL_FALSE;

		elements.push_back(vb);
		//Stride += count * sizeof(GLuint);
		Stride += count * VertexBufferElement::GetSizeType(GL_UNSIGNED_INT);
	}

	inline const std::vector<VertexBufferElement> GetElements() const& { return elements; }
	inline unsigned int GetStride() { return Stride; };

	unsigned int Stride;


private:
	std::vector<VertexBufferElement> elements;

};
