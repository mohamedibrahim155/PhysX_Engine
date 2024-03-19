#include "SinglePassEffect.h"
#include "../Time.h"
#include "../GraphicsRender.h"
SinglePassEffect::SinglePassEffect()
{
}



void SinglePassEffect::InitializeEffect(const std::string& vertex, const std::string& fragment)
{

}

void SinglePassEffect::ApplyEffect(FrameBuffer* frameBuffer)
{
	time += Time::GetInstance().deltaTime;

	singlepassFramebuffer->Bind();
	
	GraphicsRender::GetInstance().Clear();
	
	shader->Bind();
	GLCALL(glActiveTexture(GL_TEXTURE0));

	SetShaderUniforms();

	GLCALL(glBindTexture(GL_TEXTURE_2D, frameBuffer->GetColorAttachmentID()));

	Quad::GetInstance().RenderQuad();
	
	//shader->Unbind();
	
	singlepassFramebuffer->Unbind();


	
	frameBuffer->Bind();

	GraphicsRender::GetInstance().Clear();
	
	finalShader->Bind();

	GLCALL(glActiveTexture(GL_TEXTURE0));
	finalShader->setInt("sceneTexture", 0);
	GLCALL(glBindTexture(GL_TEXTURE_2D, frameBuffer->GetColorAttachmentID()));

	GLCALL(glActiveTexture(GL_TEXTURE1));
	finalShader->setInt("effectTexture", 1);
	GLCALL(glBindTexture(GL_TEXTURE_2D, singlepassFramebuffer->GetColorAttachmentID()));

	Quad::GetInstance().RenderQuad();

	//finalShader->Unbind();

	frameBuffer->Unbind();
}

void SinglePassEffect::DrawProperties()
{

	std::string title = "###" + name;
	ImGui::Checkbox(title.c_str(), &isEnabled);
	ImGui::SameLine();
	ImGui::Text(name.c_str());
}

void SinglePassEffect::SceneDraw()
{
}
