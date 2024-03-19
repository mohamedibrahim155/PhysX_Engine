#pragma once

#include "Renderer.h"
#include <GLFW/stb_image.h>
#include "BaseTexture.h"

class CubeMapTexture :public BaseTexture
{
public : 

	

	CubeMapTexture();
	~CubeMapTexture();

	unsigned int textureId;

	void LoadTexture(std::vector<std::string> faces);

	bool IsFileExists(const std::string& path);

	// Inherited via BaseTexture
	void Bind() override;
	void Unbind() override;
	void SetTextureSlot(int place) override;
	void DrawProperties() override;
	void SceneDraw() override;
};

