#pragma once

#include "Light.h"

class LightManager 
{
public:

    static LightManager& GetInstance();
   

    void SetUniforms(GLuint shaderID);
    void AddLight(Light* light);
    void RemoveLight(Light* light);

    // This is called every frame
    void UpdateUniformValues(GLuint shaderID);
    void UpdateUniformValuesToShader(Shader* shader);
    static const unsigned int MAX_LIGHT = 11;
    
    const std::vector<Light*>& GetLightList();
private:
    std::vector<Light*> lightList;

};



