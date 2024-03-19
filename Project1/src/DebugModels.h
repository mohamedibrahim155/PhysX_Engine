#pragma once
#include "model.h"

class DebugModels
{
public:
	DebugModels();
	~DebugModels();

	static DebugModels& GetInstance();

	Model* defaultCube;
	Model* defaultSphere;
	Model* defaultQuad;


};

