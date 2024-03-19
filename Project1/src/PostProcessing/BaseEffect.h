#pragma once
#include "../Shader.h"
#include "../FrameBuffer.h"
#include "../Object.h"
class BaseEffect : public Object
{
public:

	int effectOrder = 0;
	std::string name =  "baseeffect";
	virtual void ApplyEffect(FrameBuffer* frameBuffer) = 0;

	// Inherited via Object
	virtual void DrawProperties()=0;
	virtual void SceneDraw()=0;
};

