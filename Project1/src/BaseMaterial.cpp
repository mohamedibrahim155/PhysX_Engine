#include "BaseMaterial.h"
#include "material.h"
#include "SkyboxMaterial.h"
#include "UnLitMaterial.h"


Material* BaseMaterial::material()
{
	return (Material*)this;
}

SkyboxMaterial* BaseMaterial::skyboxMaterial()
{
	return (SkyboxMaterial*)this;
}

UnLitMaterial* BaseMaterial::unLitMaterial()
{
	return (UnLitMaterial*)this;
}
