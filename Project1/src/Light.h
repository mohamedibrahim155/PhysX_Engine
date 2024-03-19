#pragma once
#include<glm/glm.hpp>
#include "Shader.h"
#include "Model.h"
#include <vector>

class LightManager;
class GraphicsRender;

enum LightType
{
    DIRECTION_LIGHT =0,
    POINT_LIGHT=1,
    SPOT_LIGHT =2
};

class Light : public Model
{
public:
    Light();
    void Initialize(const LightType& type);
    void Initialize(const LightType& type = LightType::POINT_LIGHT, const float& intensity =0.5f );
    void SetColor(const float x, const float y ,const float z ,const float w);
    void SetColor(const glm::vec4& color);
    void SetAmbientColor(const glm::vec4& ambient);
    void SetAttenuation(const float&  constant, const float&  linear, const float&  quadratic);
    void SetIntensity(const float& intensity);
    void SetCutoffAngle(float cutOffAngle);
    void SetOuterCutoffAngle(float OutercutOffAngle);
    void SetInnerAndOuterCutoffAngle(float cuttOffAngle,float OutercutOffAngle);
    void SetLightType(const LightType& type = LightType::POINT_LIGHT);
    void SetNameBaseOnType();



    glm::vec4& GetLightColor();
    glm::vec4& GetAmbientColor();
    glm::vec3& GetAttenuation();
    float& GetIntensityValue();
    glm::vec2& GetInnerAndOuterAngle();


    ~Light() { };

    void DrawProperties() override;
    void SceneDraw() override;

    void Start() override;
    void Update(float deltaTime) override;
    void OnDestroy() override;
    void Render() override;

    LightType lightType;
private:
    Material material;

    glm::vec4 ambient;

    glm::vec4 color;
    

     //for pointLight
    float constant;
    float linear;
    float quadratic;
    float intensity = 0.5f;

    //spot Lights
    float cutOffAngle;
    float outerCutOffAngle;

    float lightTransformScale = 0.25f;
};







