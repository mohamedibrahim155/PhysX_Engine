#include "UnLitMaterial.h"

UnLitMaterial::UnLitMaterial() 
{
}

UnLitMaterial::~UnLitMaterial()
{
}

glm::vec4 UnLitMaterial::GetBaseColor()
{
    return baseColor;
}

void UnLitMaterial::SetBaseColor( glm::vec4 color)
{
    baseColor = color;
}

void UnLitMaterial::UpdateMaterial(Shader* shader)
{
    shader->Bind();
    shader->setVec3("objectColor", this->GetBaseColor().x, this->GetBaseColor().y, this->GetBaseColor().z);

}

void UnLitMaterial::ResetMaterial(Shader* shader)
{
}

BaseMaterial* UnLitMaterial::DuplicateMaterial()
{
    UnLitMaterial* material = new UnLitMaterial();

    material->SetBaseColor(this->GetBaseColor());

    return material;
}
