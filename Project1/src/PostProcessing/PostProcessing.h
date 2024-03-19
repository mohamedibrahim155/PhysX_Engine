#pragma once
//#include "BaseEffect.h"
#include "ChromaticEffect.h"
#include "PixelizationEffect.h"
class PostProcessing : public Object
{
public:

	PostProcessing();
	PostProcessing(const glm::vec2& cameraWidthAndHeight);
	~PostProcessing();
	void SetCameraWidthAndHeight(const glm::vec2& value);
	void InitializePostProcessing();

	void ApplyPostprocessing(FrameBuffer* framebuffer);

	 void AddEffect(BaseEffect* effect);
     void RemoveEffect(BaseEffect* effect);
	 bool isPostProccesingEnabled = false;

	 // Inherited via Object
	 void DrawProperties() override;

	 void SceneDraw() override;

private:

	std::vector<BaseEffect*> listOfeffects;

	ChromaticEffect* chromatic;
	PixelizationEffect* pixelization;

	Shader* finalShader;
	
	glm::vec2 cameraWidthAndHeight;


};

