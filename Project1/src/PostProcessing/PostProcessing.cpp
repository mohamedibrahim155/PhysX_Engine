#include "PostProcessing.h"

PostProcessing::PostProcessing()
{
}

PostProcessing::PostProcessing(const glm::vec2& cameraWidthAndHeight)
{
	SetCameraWidthAndHeight(cameraWidthAndHeight);
}

PostProcessing::~PostProcessing()
{
}

void PostProcessing::SetCameraWidthAndHeight(const glm::vec2& value)
{
	cameraWidthAndHeight = value;
}

void PostProcessing::InitializePostProcessing()
{
	isPostProccesingEnabled = true;

	finalShader = new Shader("Shaders/PostProcessing/FinalOutputShader.vert", "Shaders/PostProcessing/FinalOutputShader.frag");

	chromatic = new ChromaticEffect(cameraWidthAndHeight.x, cameraWidthAndHeight.y);
	chromatic->finalShader = finalShader;
	AddEffect(chromatic);

	pixelization = new PixelizationEffect(cameraWidthAndHeight.x, cameraWidthAndHeight.y);
	pixelization->finalShader = finalShader;
	AddEffect(pixelization);
}

void PostProcessing::ApplyPostprocessing(FrameBuffer* framebuffer)
{
	//if (!isPostProccesingEnabled) return;

	for (BaseEffect* effect :  listOfeffects)
	{
		if (!effect->isEnabled) continue;

		effect->ApplyEffect(framebuffer);
	}
}

void PostProcessing::AddEffect(BaseEffect* effect)
{
	listOfeffects.push_back(effect);
}

void PostProcessing::RemoveEffect(BaseEffect* effect)
{
	std::vector<BaseEffect*> ::iterator it = std::remove(listOfeffects.begin(), listOfeffects.end(), effect);

	listOfeffects.erase(it, listOfeffects.end());
}

void PostProcessing::DrawProperties()
{
	

	if (!ImGui::TreeNodeEx("Post processing properties", ImGuiTreeNodeFlags_DefaultOpen))
	{
		return;
	}


	for (BaseEffect* effect :  listOfeffects)
	{
		effect->DrawProperties();
	}

	ImGui::TreePop();
}

void PostProcessing::SceneDraw()
{
}
