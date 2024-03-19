#include "material.h"



Material::Material()
{
    ambientType = AmbientType::Value;
    ambientColor = glm::vec4(1.0f);
    baseColor = glm::vec4(1.0f);
    ResetMaterial();
}


Material::Material(const Material& material)
{
    SetBaseColor(glm::vec4(material.baseColor.x, material.baseColor.y, material.baseColor.z, material.baseColor.w));
    SetAmbientColor(glm::vec4(material.ambientColor.x, material.ambientColor.y, material.ambientColor.z, material.ambientColor.w));
    diffuseTexture = material.diffuseTexture;
    specularTexture = material.specularTexture;
    alphaTexture = material.alphaTexture;

    ambientType = material.ambientType;
    ambient= material.ambient;
    specular = material.specular;
    shininess = material.shininess;

    useMaskTexture = material.useMaskTexture;
    alphaCutoffThreshold = material.alphaCutoffThreshold;
}

Material::~Material()
{
    delete diffuseTexture;
    delete specularTexture;
    delete alphaTexture;
}
   

void Material::SetMaterialProperties(Shader& shader) 
{

    
    shader.setFloat("material.shininess", this->shininess);
    

}

void Material::ResetMaterial()
{
    baseColor = glm::vec4(1.0f);
    ambient = 1.0f;
    specular = 0.5f;
}

float Material::GetSpecular()
{
    return specular;
}

glm::vec4 Material::GetBaseColor()
{
    return baseColor;
}

glm::vec4 Material::GetAmbientColor()
{
    switch (ambientType)
    {
    case AmbientType::Color:
        return ambientColor;
    case AmbientType::Value:
        return baseColor * ambient;
    }
}

void Material::SetBaseColor(glm::vec4 color)
{
    baseColor = color;
}

void Material::SetAmbientColor(glm::vec4 color)
{
    ambientColor = color;
}




void Material::ResetMaterial(Shader* shader)
{
}

BaseMaterial* Material::DuplicateMaterial()
{
    Material* material = new Material();

    material->SetBaseColor(this->GetBaseColor());
    material->SetAmbientColor(this->GetAmbientColor());
    material->diffuseTexture = this->diffuseTexture;
    material->specularTexture = this->specularTexture;
    material->alphaTexture = this->alphaTexture;
    material->ambientType = this->ambientType;
    material->ambient = this->ambient;
    material->specular = this->specular;
    material->shininess = this->shininess;
    material->useMaskTexture = this->useMaskTexture;
    material->alphaCutoffThreshold = this->alphaCutoffThreshold;

    return material;
}

void Material::UpdateMaterial(Shader* shader)
{
    shader->Bind();

    shader->setVec4("material.baseColor", this->GetBaseColor().x, this->GetBaseColor().y, this->GetBaseColor().z, this->GetBaseColor().w);
    shader->setVec4("material.ambientColor", this->GetAmbientColor().x, this->GetAmbientColor().y, this->GetBaseColor().z, this->GetAmbientColor().w);

    shader->setFloat("material.specularValue", this->GetSpecular());
    shader->setFloat("material.shininess", this->shininess);

    shader->setInt("ShaderBlend", (int)shader->blendMode);
    shader->setBool("ObjectBlend", this->useMaskTexture);
    shader->setFloat("alphaCutOffThreshold", this->alphaCutoffThreshold);

    if (this->diffuseTexture != nullptr)
    {
        this->diffuseTexture->SetTextureSlot(0);
        shader->setInt("diffuse_Texture", 0);
        this->diffuseTexture->Bind();

    }
    if (this->specularTexture != nullptr)
    {
        this->specularTexture->SetTextureSlot(1);
        shader->setInt("specular_Texture", 1);
        this->specularTexture->Bind();

    }

    if (this->alphaTexture != nullptr)
    {
        this->alphaTexture->SetTextureSlot(2);
        shader->setInt("opacity_Texture", 2);
        this->alphaTexture->Bind();
    }

}
