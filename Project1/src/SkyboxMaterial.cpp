#include "SkyboxMaterial.h"

SkyboxMaterial::SkyboxMaterial()
{
    skyBoxTexture = new CubeMapTexture();
}

SkyboxMaterial::~SkyboxMaterial()
{
}

void SkyboxMaterial::UpdateMaterial(Shader* shader)
{
    this->skyBoxTexture->SetTextureSlot(0);
    shader->setInt("skybox", 0);
    this->skyBoxTexture->Bind();
}

void SkyboxMaterial::ResetMaterial(Shader* shader)
{
}

BaseMaterial* SkyboxMaterial::DuplicateMaterial()
{
    return nullptr;
}
