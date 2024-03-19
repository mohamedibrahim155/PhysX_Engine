#pragma once

#include "BaseMaterial.h"
#include "CubeMapTexture.h" 

class SkyboxMaterial : public BaseMaterial
{
public :
	SkyboxMaterial();
	~SkyboxMaterial();

	CubeMapTexture* skyBoxTexture;



	// Inherited via BaseMaterial
	void UpdateMaterial(Shader* shader) override;
	void ResetMaterial(Shader* shader) override;
	BaseMaterial* DuplicateMaterial() override;
};

