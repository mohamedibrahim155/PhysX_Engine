#include "Textures.h"

#define STB_IMAGE_IMPLEMENTATION
#include "GLFW/stb_image.h"










Texture::Texture(std::string& filePath)
{
	this->path = filePath;
	this->id = LoadTextureID(filePath.c_str());
}

Texture::~Texture()
{
	GLCALL(glDeleteTextures(1, &id));
}



unsigned int Texture::LoadTextureID(char const* path)
{

	unsigned int textureID;
	GLCALL(glGenTextures(1, &textureID));

	int width, height, nrComponents;
	unsigned char* data = stbi_load(path, &width, &height, &nrComponents, 0);
	if (data)
	{
		GLenum format;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;

		GLCALL(glBindTexture(GL_TEXTURE_2D, textureID));
		GLCALL(glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data));
		GLCALL(glGenerateMipmap(GL_TEXTURE_2D));

		GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, format == GL_RGBA ? GL_CLAMP_TO_EDGE : GL_REPEAT));
		GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, format == GL_RGBA ? GL_CLAMP_TO_EDGE : GL_REPEAT));
		GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR));
		GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

		stbi_image_free(data);
	}
	else
	{
		std::cout << "Texture failed to load at path: " << path << std::endl;
		stbi_image_free(data);
	}
	std::cout << "LoadedTexture successfully : " << path << std::endl;
	return textureID;
}

void Texture::DrawProperties()
{
}

void Texture::SceneDraw()
{
}

void  Texture::LoadTexture(const std::string& filePath, const std::string& _type)
{
	this->path = filePath;
	this->type = _type;
	this->id = LoadTextureID(filePath.c_str());
}


void Texture::Bind()
{
	GLCALL(glBindTexture(GL_TEXTURE_2D, id));
}

void Texture::Unbind()
{
	GLCALL(glBindTexture(GL_TEXTURE_2D, 0));
}

void Texture::SetTextureSlot(int place)
{
	GLCALL(glActiveTexture(GL_TEXTURE0 + place));
}
