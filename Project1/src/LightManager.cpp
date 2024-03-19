#include"LightManager.h"




LightManager& LightManager::GetInstance()
{
    static LightManager instance;
    return instance;
}


void LightManager::SetUniforms(GLuint shaderID)
{

    //for (size_t i = 0; i < lightList.size(); i++)
    //{
    //    std::string index = std::to_string(i);
    //    this->lightList[i].position_UL =         glGetUniformLocation(shaderID, ("lights[" + index + "].position").c_str());
    // //   this->lightList[i].diffuse_UL =          glGetUniformLocation(shaderID, ("lights[" + index + "].diffuse").c_str());
    //   // this->lightList[i].specular_UL =         glGetUniformLocation(shaderID, ("lights[" + index + "].specular").c_str());
    //    this->lightList[i].ambient_UL =          glGetUniformLocation(shaderID, ("lights[" + index + "].ambient").c_str());
    //    this->lightList[i].direction_UL =        glGetUniformLocation(shaderID, ("lights[" + index + "].direction").c_str());
    //    this->lightList[i].lightType_UL =        glGetUniformLocation(shaderID, ("lights[" + index + "].lightType").c_str());
    //    this->lightList[i].linear_UL =           glGetUniformLocation(shaderID, ("lights[" + index + "].linear").c_str());
    //    this->lightList[i].quadratic_UL =        glGetUniformLocation(shaderID, ("lights[" + index + "].quadratic").c_str());
    //    this->lightList[i].constant_UL =         glGetUniformLocation(shaderID, ("lights[" + index + "].constant").c_str());
    //    this->lightList[i].cuttOffAngle_UL =     glGetUniformLocation(shaderID, ("lights[" + index + "].cutOff").c_str());
    //    this->lightList[i].outerCutOffAngle_UL = glGetUniformLocation(shaderID, ("lights[" + index + "].outerCutOff").c_str());
    //    this->lightList[i].color_UL =            glGetUniformLocation(shaderID, ("lights[" + index + "].color").c_str());
    //}

}

void LightManager::AddLight(Light* light)
{
    lightList.push_back(light);
}

void LightManager::RemoveLight(Light* light)
{
    lightList.erase(std::remove(lightList.begin(), lightList.end(), light), lightList.end());
}




void LightManager::UpdateUniformValues(GLuint shaderID)
{
    //for (unsigned int index = 0;index <lightList.size(); index++)
    //{
    //    if (lightList.size()>LightManager::MAX_LIGHT)
    //    {
    //        std::cout << "Light exceeded ...  File : " << __FILE__<< " Line : "  << __LINE__ << std::endl;
    //        break;
    //    }
    //    //lightList[index].lightModel->transform.position
    //    GLCALL(glUniform3f(lightList[index].position_UL, lightList[index].lightModel->transform.position.x ,lightList[index].lightModel->transform.position.y, lightList[index].lightModel->transform.position.z));
    //   
    //    glm::vec3 value = lightList[index].lightModel->transform.GetForward();

    // GLCALL(glUniform3f(lightList[index].direction_UL, value.x, value.y, value.z));

    //   // glUniform4f(lightList[index].diffuse_UL, lightList[index].diffuse.x,lightList[index].diffuse.y,   lightList[index].diffuse.z, lightList[index].diffuse.w);
    //             
    //   // glUniform4f(lightList[index].specular_UL,lightList[index].specular.x,lightList[index].specular.y, lightList[index].specular.z, lightList[index].diffuse.w);
    //             
    //    glUniform4f(lightList[index].ambient_UL, lightList[index].ambient.x, lightList[index].ambient.y,  lightList[index].ambient.z, lightList[index].diffuse.w);
    //             
    //   // glUniform3f(lightList[index].direction_UL,lightList[index].direction.x, lightList[index].direction.y,lightList[index].direction.z);

    //    glUniform1i(lightList[index].lightType_UL,  (int)lightList[index].lightType);


    //    glUniform1f(lightList[index].constant_UL,lightList[index].constant);


    //    glUniform1f(lightList[index].linear_UL,lightList[index].linear);


    //    glUniform1f(lightList[index].quadratic_UL,lightList[index].quadratic);


    //    glUniform1f(lightList[index].cuttOffAngle_UL, glm::cos(glm::radians( lightList[index].cutOffAngle)));

    //    glUniform1f(lightList[index].outerCutOffAngle_UL, glm::cos(glm::radians(lightList[index].outerCutOffAngle)));
    //    glUniform4f(lightList[index].color_UL,  lightList[index].color.x, lightList[index].color.y, lightList[index].color.z, lightList[index].color.w);
    //}


    return;

}

void LightManager::UpdateUniformValuesToShader(Shader* shader)
{
    shader->Bind();
    for (size_t i = 0; i < lightList.size(); i++)
    {
        if (lightList.size() > LightManager::MAX_LIGHT)
        {
            std::cout << "Light exceeded ...  File : " << __FILE__ << " Line : " << __LINE__ << std::endl;
            break;
        }
        std::string index = std::to_string(i);
        float intensity = lightList[i]->GetIntensityValue();
        shader->setVec3(  "lights[" + index + "].position", lightList[i]->transform.position.x, lightList[i]->transform.position.y, lightList[i]->transform.position.z);
        shader->setVec3(  "lights[" + index + "].direction", lightList[i]->transform.GetForward());
        shader->setVec4(  "lights[" + index + "].ambient", lightList[i]->GetAmbientColor().x * intensity,
            lightList[i]->GetAmbientColor().y * intensity, lightList[i]->GetAmbientColor().z * intensity, lightList[i]->GetAmbientColor().w);
        shader->setInt(   "lights[" + index + "].lightType", (int)lightList[i]->lightType);
        shader->setFloat( "lights[" + index + "].linear", lightList[i]->GetAttenuation().x);    // Linear
        shader->setFloat( "lights[" + index + "].quadratic", lightList[i]->GetAttenuation().y); // Quadratic
        shader->setFloat( "lights[" + index + "].constant", lightList[i]->GetAttenuation().z);  // Constant
        shader->setFloat( "lights[" + index + "].cutOff", glm::cos(glm::radians(lightList[i]->GetInnerAndOuterAngle().x)));
        shader->setFloat( "lights[" + index + "].outerCutOff", glm::cos(glm::radians(lightList[i]->GetInnerAndOuterAngle().y)));

       

        shader->setVec4(  "lights[" + index + "].color", lightList[i]->GetLightColor().x * intensity, lightList[i]->GetLightColor().y * intensity,
            lightList[i]->GetLightColor().z * intensity, lightList[i]->GetLightColor().w);

    }
    return;
}

const std::vector<Light*>& LightManager::GetLightList()
{
    return lightList;
}
