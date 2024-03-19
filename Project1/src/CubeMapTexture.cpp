#include "CubeMapTexture.h"

CubeMapTexture::CubeMapTexture()
{
    GLCALL(glGenTextures(1, &textureId));
    GLCALL(glBindTexture(GL_TEXTURE_CUBE_MAP, textureId));
}

CubeMapTexture::~CubeMapTexture()
{
}

void CubeMapTexture::Bind()
{
	GLCALL(glBindTexture(GL_TEXTURE_CUBE_MAP, textureId));
}

void CubeMapTexture::LoadTexture(std::vector<std::string> faces)
{
    int width, height, channels;

    for (unsigned int i = 0; i < faces.size(); i++)
    {

        if (!IsFileExists(faces[i]))
        {
            std::cout << "No file found!";
        }

        unsigned char* imageData = stbi_load(faces[i].c_str(), &width, &height, &channels, 0);

        if (!imageData)
        {
            std::cerr << "Failed to load image at path: " << faces[i] << "\n"  << "Reason: " << stbi_failure_reason() << std::endl;

           
            return;
        }

        GLCALL(glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, imageData));
    }

    GLCALL(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    GLCALL(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
    GLCALL(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
    GLCALL(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
    GLCALL(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE));
}

bool CubeMapTexture::IsFileExists(const std::string& path)
{
    std::ifstream file(path);
    return file.good();
}

void CubeMapTexture::Unbind()
{
    GLCALL(glBindTexture(GL_TEXTURE_CUBE_MAP, 0));
}

void CubeMapTexture::SetTextureSlot(int place)
{
    GLCALL(glActiveTexture(GL_TEXTURE0 + place));
}

void CubeMapTexture::DrawProperties()
{
}

void CubeMapTexture::SceneDraw()
{
}
