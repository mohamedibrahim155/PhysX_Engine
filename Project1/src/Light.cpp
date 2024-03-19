
#include "Light.h"
#include "DebugModels.h"
#include "LightManager.h"
#include "GraphicsRender.h"
#include "ImGui/EditorLayout.h"

Light::Light()
{
	SetLightType(DIRECTION_LIGHT);
	SetAmbientColor(glm::vec4(0.5f, 0.5f, 0.5f, 1.0f));
	SetIntensity(intensity);
	SetAttenuation(1, 1, 1);
	SetColor(1, 1, 1, 1);
	SetInnerAndOuterCutoffAngle(12.5f, 15);

}

void Light::Initialize(const LightType& type)
{
	SetLightType(type);
	SetAmbientColor(glm::vec4(0.5f, 0.5f, 0.5f, 1.0f));
	SetIntensity(0.5f);
	SetAttenuation(1, 1, 1);
	SetColor(1, 1, 1,1);
	SetInnerAndOuterCutoffAngle(12.5f, 15);

	LoadModel(*DebugModels::GetInstance().defaultSphere, true);

	transform.SetScale(glm::vec3(this->lightTransformScale));

	SetNameBaseOnType();

	LightManager::GetInstance().AddLight(this);
	GraphicsRender::GetInstance().AddModelAndShader(this, GraphicsRender::GetInstance().solidColorShader);


}

void Light::Initialize(const LightType& type, const float& intensity)
{

	SetLightType(type);
	SetAmbientColor(glm::vec4(0.5f, 0.5f, 0.5f, 1.0f));
	SetIntensity(intensity);
	SetAttenuation(1, 1, 1);
	SetColor(1, 1, 1, 1);
	SetInnerAndOuterCutoffAngle(12.5f, 15);

	LoadModel(*DebugModels::GetInstance().defaultSphere, true);

	transform.SetScale(glm::vec3(this->lightTransformScale));

	SetNameBaseOnType();

	LightManager::GetInstance().AddLight(this);
	GraphicsRender::GetInstance().AddModelAndShader(this, GraphicsRender::GetInstance().solidColorShader);

}


void Light::SetColor(const float x, const float y, const float z, const float w)
{
	this->color = glm::vec4(x, y, z, w);
}

void Light::SetColor(const glm::vec4& color)
{
	this->color = color;
}

void Light::SetAmbientColor(const glm::vec4& ambient)
{
	this->ambient = ambient;
}


void Light::SetAttenuation(const float& constant, const float& linear, const float& quadratic)
{
	this->constant = constant;
	this->linear = linear;
	this->quadratic = quadratic;
}

void Light::SetIntensity(const float& intensity)
{
	this->intensity = intensity;
}

void Light::SetCutoffAngle(float cutOffAngle)
{
	this->cutOffAngle = cutOffAngle;

}

void Light::SetOuterCutoffAngle(float OutercutOffAngle)
{
	this->outerCutOffAngle = OutercutOffAngle;
}

void Light::SetInnerAndOuterCutoffAngle(float cuttOffAngle, float OutercutOffAngle)
{
	this->cutOffAngle = cuttOffAngle;
	this->outerCutOffAngle = OutercutOffAngle;
}

void Light::SetLightType(const LightType& type)
{
	this->lightType = type;
}

void Light::SetNameBaseOnType()
{
	switch (lightType)
	{
	case DIRECTION_LIGHT:
		name = "Direction Light";
		break;
	case POINT_LIGHT:
		name = "Point Light";

		break;
	case SPOT_LIGHT:
		name = "Spot Light";
		break;

	}
}

glm::vec4& Light::GetLightColor()
{
	return color;
}

glm::vec4& Light::GetAmbientColor()
{
	return ambient;
}

glm::vec3& Light::GetAttenuation()  
{
	glm::vec3 attenuation = glm::vec3(linear, quadratic, constant);
	return attenuation;
}

float& Light::GetIntensityValue()
{
	return intensity;
}

glm::vec2& Light::GetInnerAndOuterAngle()
{
	glm::vec2 innerAndOuterAngle = glm::vec2(cutOffAngle, outerCutOffAngle);
	return innerAndOuterAngle;
}

void Light::DrawProperties()
{
	Model::DrawProperties();
}

void Light::SceneDraw()
{
	ImGuiTreeNodeFlags node_flags = ImGuiTreeNodeFlags_NoTreePushOnOpen;
	node_flags |= ImGuiTreeNodeFlags_SpanFullWidth;
	node_flags |= ImGuiTreeNodeFlags_Leaf;

	if (isSelected)
	{
		node_flags |= ImGuiTreeNodeFlags_Selected;
	}

	bool node_open = ImGui::TreeNodeEx(name.c_str(), node_flags);

	if (ImGui::IsItemClicked() && !ImGui::IsItemToggledOpen())
	{
		EditorLayout::GetInstance().SetSelectedObjects({ this });
	}
}

void Light::Start()
{
}

void Light::Update(float deltaTime)
{
}

void Light::OnDestroy()
{
}

void Light::Render()
{
}


