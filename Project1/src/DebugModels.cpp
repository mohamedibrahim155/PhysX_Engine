#include "DebugModels.h"

DebugModels::DebugModels()
{
}

DebugModels::~DebugModels()
{
	delete defaultCube;
	delete defaultSphere;
}

DebugModels& DebugModels::GetInstance()
{
	static DebugModels instance;

	return instance;
}
