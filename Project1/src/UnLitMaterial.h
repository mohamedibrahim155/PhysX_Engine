#pragma once

#include "BaseMaterial.h"


class UnLitMaterial : public BaseMaterial
{
	
public : 
	UnLitMaterial();
	~UnLitMaterial();

	glm::vec4 GetBaseColor();

	void SetBaseColor(glm::vec4 color);

	// Inherited via BaseMaterial
	void UpdateMaterial(Shader* shader) override;
	void ResetMaterial(Shader* shader) override;

	BaseMaterial* DuplicateMaterial() override;

private:
	glm::vec4 baseColor = glm::vec4(1);

};

