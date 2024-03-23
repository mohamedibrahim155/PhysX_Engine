#pragma once
#include "Shader.h"
#include "Camera.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "Renderer.h"
#include "VertexArray.h"
#include  "model.h"
#include "material.h"
#include "Light.h"
#include "Transform.h"
#include"LightManager.h"
#include "Random.h"
#include "Time.h"
#include "SkyboxMaterial.h"
#include "GraphicsRender.h"
#include "ImGui/PanelManager.h" 
#include "ImGui/EditorLayout.h"

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "FrameBuffer.h"
#include "DebugModels.h"
#include "InputManager/InputManager.h"
#include "EntityManager/EntityManager.h"
#include "CameraManager.h"
#include "SkinnedMeshRenderer.h"
#include "CharacterAnimation/CharacterAnimation.h"
#include "PhysX/PhysXEngine.h"
class ApplicationRenderer
{
public:
	ApplicationRenderer();
	~ApplicationRenderer();

	static void SetViewPort(GLFWwindow* window, int width, int height);
	void KeyCallBack(GLFWwindow* window, int key, int scancode, int action, int mods);
	void MouseCallBack(GLFWwindow* window, double xposIn, double yposIn);
	void MouseScroll(GLFWwindow* window, double xoffset, double yoffset);
	
	void WindowInitialize(int width, int height,  std::string windowName ="Window");
	void InitializeShaders();
	void InitializeSkybox();
	
	void Start();
	void Render();
	void PostRender();
	void Clear();
	void ShutDown();

	void ProcessInput(GLFWwindow* window);

	void EngineGraphicsRender();
	void EngineGameLoop();
	void RenderForCamera(Camera* camera, FrameBuffer* framebuffer);
	
	FrameBufferSpecification specification;
	FrameBuffer* sceneViewframeBuffer;
	FrameBuffer* gameframeBuffer;
	Camera* sceneViewcamera;
	Camera* gameScenecamera;
	Camera* renderTextureCamera;
	bool isPlayMode = false;

	glm::mat4 projection;
	glm::mat4 view;
	glm::mat4 skyBoxView;
	int windowWidth;
	int  WindowHeight;
private:
	GLFWwindow* window;
	
	

	//GraphicsRender render;

	Shader* defaultShader;
	Shader* solidColorShader;
	Shader* alphaBlendShader;
	Shader* alphaCutoutShader;
	Shader* animationShader;

	Shader* stencilShader;
	Shader* skyboxShader;


	SkyboxMaterial* skyBoxMaterial;

	Model* skyBoxModel;


	 int selectedModelCount = 0;

	 float lastX;
	 float lastY;
	 float deltaTime;
	 double lastTime;
	 float lastFrame;

	 float scrollTime;

	 bool firstMouse;
	 bool isImguiPanelsEnable = false;

};

