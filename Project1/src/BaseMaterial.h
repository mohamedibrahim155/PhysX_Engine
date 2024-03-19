#pragma once
#include "Shader.h"

class Material;
class SkyboxMaterial;
class UnLitMaterial;

class BaseMaterial
{
public:
	
	virtual void UpdateMaterial(Shader* shader) = 0;
	virtual void ResetMaterial(Shader* shader) = 0;
	virtual BaseMaterial* DuplicateMaterial() = 0;

	Material* material();
	SkyboxMaterial* skyboxMaterial();

	UnLitMaterial* unLitMaterial();

private:

};
