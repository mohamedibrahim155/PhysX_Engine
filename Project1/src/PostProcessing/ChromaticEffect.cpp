#include "ChromaticEffect.h"
#include "../Renderer.h"
#include"../Time.h"
#include "../GraphicsRender.h"
ChromaticEffect::ChromaticEffect()
{
	name = "Chromatic";
	//InitializeChromaticEffect();

	InitializeEffect("Shaders/PostProcessing/Chromatic.vert", "Shaders/PostProcessing/Chromatic.frag");
}

ChromaticEffect::ChromaticEffect(float width, float height)
{
	name = "Chromatic";
	
	framebufferWidthAndHeight.x = width;
	framebufferWidthAndHeight.y = height;

	InitializeEffect("Shaders/PostProcessing/Chromatic.vert", "Shaders/PostProcessing/Chromatic.frag");
}

void ChromaticEffect::InitializeEffect(const std::string& vertex, const std::string& fragment)
{
	shader = new Shader(vertex.c_str(), fragment.c_str());

	FrameBufferSpecification specification;

	specification.width = framebufferWidthAndHeight.x;
	specification.height = framebufferWidthAndHeight.y;

	specification.attachments = { FramebufferTextureFormat::RGBA8, FramebufferTextureFormat::DEPTH };

	singlepassFramebuffer = new FrameBuffer(specification);

}

void ChromaticEffect::SetShaderUniforms()
{

	shader->setInt("sceneTexture", 0);  // Scene texture from framebuffer
	shader->setFloat("aberration", aberrationValue);   // abreation
	shader->setFloat("time", time);   // abreation


}

void ChromaticEffect::DrawProperties()
{
	SinglePassEffect::DrawProperties();

	if (isEnabled)
	{
		if (!ImGui::TreeNodeEx("properties", ImGuiTreeNodeFlags_DefaultOpen))
		{
			return;
		}
		ImGui::Text("Aberration Amount");
		ImGui::SameLine();
		ImGui::InputFloat("###amount", &aberrationValue);
		ImGui::TreePop();
	}
	
}

void ChromaticEffect::SceneDraw()
{
}

