#pragma once
#include "Shader.h"

#include "Textures.h"
#include "BaseMaterial.h"
enum AmbientType
{
	Value,
	Color
};

class Material : public BaseMaterial
{

private:
	glm::vec4 baseColor;
	glm::vec4 ambientColor;
	
	
	
	

public:
	
	

	Material();
	Material(const Material& material);
	~Material();

	BaseTexture* diffuseTexture; 
	BaseTexture* specularTexture;
	BaseTexture* alphaTexture;
	AmbientType ambientType;

	float ambient;
	float specular;
	float shininess = 32;
	float alphaCutoffThreshold = 0.5f;
	bool useMaskTexture = false;

	void SetMaterialProperties(Shader& shader) ;

	void ResetMaterial();
	float GetSpecular();
	glm::vec4 GetBaseColor();
	glm::vec4 GetAmbientColor();

	void SetBaseColor(glm::vec4 color);
	void SetAmbientColor(glm::vec4 color);
	
	



	// Inherited via BaseMaterial
	void UpdateMaterial(Shader* shader) override;
	void ResetMaterial(Shader* shader) override;
	// Inherited via BaseMaterial
	BaseMaterial* DuplicateMaterial() override;



};