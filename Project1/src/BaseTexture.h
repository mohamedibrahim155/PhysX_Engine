#pragma once
#include "Object.h"
class BaseTexture : public Object
{
public:

	virtual void Bind() = 0;
	virtual void Unbind() = 0;
	virtual void SetTextureSlot(int place = 0 )= 0;


	// Inherited via Object
	virtual void DrawProperties() = 0;
	virtual void SceneDraw() = 0;

};

