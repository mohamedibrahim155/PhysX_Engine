#pragma once

#include "Renderer.h"
#include "Textures.h"
#include "Shader.h"

class Skybox
{
public:

	Skybox();
	~Skybox();


	void SkyboxPrerender();
	void Skyboxrender();
	void SkyboxPostrender();

	void AssignSkyboxShader(Shader* shader);

	Texture* skyboxTexture = new Texture();

private:
	
	Shader* skyboxShader;
	unsigned int skyboxVAO;
	unsigned int skyboxVBO;
	unsigned int cubemapTexture;
};

