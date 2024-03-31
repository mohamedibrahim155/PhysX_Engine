#include"ApplicationRenderer.h"


ApplicationRenderer::ApplicationRenderer()
{
    sceneViewcamera = new Camera();
    sceneViewcamera->name = "Sceneview Camera";

    gameScenecamera = new Camera();
    gameScenecamera->name = "GameScene Camera";

    renderTextureCamera = new Camera();
    renderTextureCamera->name = "RenderTexture Camera";
}

ApplicationRenderer::~ApplicationRenderer()
{
}



void ApplicationRenderer::WindowInitialize(int width, int height,  std::string windowName)
{
    windowWidth = width;
    WindowHeight = height;
    lastX = windowWidth / 2.0f;
    lastY= WindowHeight / 2.0f;

    glfwInit();



    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    window = glfwCreateWindow(width, height, windowName.c_str(), NULL, NULL);

    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return;
    }
    glfwMakeContextCurrent(window);
    glfwSetWindowUserPointer(window, this);
    glfwSetFramebufferSizeCallback(window, [](GLFWwindow* w, int x, int y)
        {
            static_cast<ApplicationRenderer*>(glfwGetWindowUserPointer(w))->SetViewPort(w, x, y);
        });

    glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
        {
            static_cast<ApplicationRenderer*>(glfwGetWindowUserPointer(window))->KeyCallBack(window, key, scancode, action, mods);
        });


    glfwSetCursorPosCallback(window, [](GLFWwindow* window, double xposIn, double yposIn)
        {
            static_cast<ApplicationRenderer*>(glfwGetWindowUserPointer(window))->MouseCallBack(window, xposIn, yposIn);
        });

    glfwSetScrollCallback(window, [](GLFWwindow* window, double xoffset, double yoffset)
        {
            static_cast<ApplicationRenderer*>(glfwGetWindowUserPointer(window))->MouseScroll(window, xoffset, yoffset);
        });
   
   

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.FontGlobalScale = 2.0f;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;   

    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(this->window, true);
    ImGui_ImplOpenGL3_Init("#version 450");
   // ImGui_ImplOpenGL3_Init("#version 130");

    //Init GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return;
    }

    // Query and print OpenGL version
    const GLubyte* version = glGetString(GL_VERSION);
    if (version) {
        std::cout << "OpenGL Version: " << version << std::endl;
    }
    else 
    {
        std::cerr << "Failed to retrieve OpenGL version\n";
     
    }


    FrameBufferSpecification specification;

    specification.width = windowWidth;
    specification.height = WindowHeight;
    specification.attachments = { FramebufferTextureFormat::RGBA8, FramebufferTextureFormat::RGBA8, FramebufferTextureFormat::DEPTH };
    

    sceneViewframeBuffer = new FrameBuffer(specification);

    gameframeBuffer = new FrameBuffer(specification);

    EditorLayout::GetInstance().applicationRenderer = this;
  

    InitializeShaders();
   
    GraphicsRender::GetInstance().InitializeGraphics();

    DebugModels::GetInstance().defaultCube = new Model("Models/DefaultCube/DefaultCube.fbx", false, true);
    DebugModels::GetInstance().defaultSphere = new Model("Models/DefaultSphere/DefaultSphere.fbx", false, true);
    DebugModels::GetInstance().defaultQuad = new Model("Models/DefaultQuad/DefaultQuad.fbx", false, true);

    InitializeSkybox();

    GraphicsRender::GetInstance().SetCamera(sceneViewcamera);

    sceneViewcamera->InitializeCamera(CameraType::PERSPECTIVE, 45.0f, 0.1f, 100.0f);
    sceneViewcamera->transform.position = glm::vec3(0, 1.00, 5);
    sceneViewcamera->transform.SetRotation(glm::vec3(0));

    gameScenecamera->InitializeCamera(CameraType::PERSPECTIVE, 45.0f, 0.1f, 100.0f);
    gameScenecamera->transform.position = glm::vec3(0, 1.00, 5);
    gameScenecamera->transform.SetRotation(glm::vec3(0));

    renderTextureCamera->InitializeCamera(CameraType::PERSPECTIVE, 45.0f, 0.1f, 100.0f);
    renderTextureCamera->transform.position = glm::vec3(0, 0, -1.0f);

    renderTextureCamera->IntializeRenderTexture(specification);
   // renderTextureCamera->IntializeRenderTexture(new RenderTexture());
  
    isImguiPanelsEnable = true;

    PhysXEngine::GetInstance().InitializePhysX();
}

void ApplicationRenderer::InitializeShaders()
{
    defaultShader = new Shader("Shaders/DefaultShader_Vertex.vert", "Shaders/DefaultShader_Fragment.frag");
   
    solidColorShader = new Shader("Shaders/SolidColor_Vertex.vert", "Shaders/SolidColor_Fragment.frag", SOLID);
    stencilShader = new Shader("Shaders/StencilOutline.vert", "Shaders/StencilOutline.frag", OPAQUE);
    //ScrollShader = new Shader("Shaders/ScrollTexture.vert", "Shaders/ScrollTexture.frag");

    alphaBlendShader = new Shader("Shaders/DefaultShader_Vertex.vert", "Shaders/DefaultShader_Fragment.frag", ALPHA_BLEND);
    alphaBlendShader->blendMode = ALPHA_BLEND;

    alphaCutoutShader = new Shader("Shaders/DefaultShader_Vertex.vert", "Shaders/DefaultShader_Fragment.frag", ALPHA_CUTOUT);
    alphaCutoutShader->blendMode = ALPHA_CUTOUT;

    skyboxShader = new Shader("Shaders/SkyboxShader.vert", "Shaders/SkyboxShader.frag");
    skyboxShader->modelUniform = false;

    animationShader = new Shader("Shaders/AnimationShader.vert", "Shaders/AnimationShader.frag");
    animationShader->blendMode = OPAQUE;

    GraphicsRender::GetInstance().defaultShader = defaultShader;
    GraphicsRender::GetInstance().solidColorShader = solidColorShader;
    GraphicsRender::GetInstance().stencilShader = stencilShader; 
    GraphicsRender::GetInstance().animationShader = animationShader;

   

}

void ApplicationRenderer::InitializeSkybox()
{
    skyBoxModel = new Model("Models/DefaultCube/DefaultCube.fbx", false, true);
    skyBoxModel->meshes[0]->meshMaterial = new SkyboxMaterial();

    skyBoxMaterial = skyBoxModel->meshes[0]->meshMaterial->skyboxMaterial();

    std::vector<std::string> faces
    {
       ("Textures/skybox/right.jpg"),
       ("Textures/skybox/left.jpg"),
       ("Textures/skybox/top.jpg"),
       ("Textures/skybox/bottom.jpg"),
       ("Textures/skybox/front.jpg"),
       ("Textures/skybox/back.jpg")
    };

    skyBoxMaterial->skyBoxTexture->LoadTexture(faces);

    GraphicsRender::GetInstance().SkyBoxModel = skyBoxModel;
}



void ApplicationRenderer::Start()
{


    sceneViewcamera->postprocessing->InitializePostProcessing();

    gameScenecamera->postprocessing->InitializePostProcessing();

 

     Light* directionLight = new Light();
     directionLight->Initialize(LightType::DIRECTION_LIGHT, 1);
     directionLight->SetAmbientColor(glm::vec4(0.2f, 0.2f, 0.2f, 1.0f));

     directionLight->SetColor(glm::vec4(1, 1, 1, 1.0f));
     directionLight->SetAttenuation(1, 1, 0.01f);
     directionLight->SetInnerAndOuterCutoffAngle(11, 12);

     directionLight->transform.SetRotation(glm::vec3(0, 0, 5));
     directionLight->transform.SetPosition(glm::vec3(0, 0, 5));
    


     PhysXObject* cube = new PhysXObject();
     cube->LoadModel("Models/DefaultCube/DefaultCube.fbx");
     cube->name = "Cube";
     cube->transform.SetPosition(glm::vec3(0, 5, 0));
     cube->transform.SetRotation(glm::vec3(10, 0, 0));
     cube->transform.SetScale(glm::vec3(0.5f,0.25f,0.25f));
     GraphicsRender::GetInstance().AddModelAndShader(cube, defaultShader);
     cube->Initialize(RigidBody::RigidBodyType::DYNAMIC, BaseCollider::ColliderShape::BOX);
     cube->rigidBody->freezeRotation = Contraints(true, true, false);
    // cube->rigidBody->SetGravity(false);
     //cube->rigidBody->SetKinematic(true);
    /* PhysicsMaterial material;
     material.dynamicFriction = 2;
     material.bounciness = 1;
     cube->collider->SetPhysicsMaterial(material);*/

     //cube->collider->AsBoxCollider()->SetSize(glm::vec3(1, 2, 1));

     PhysXObject* floor = new PhysXObject();
     floor->LoadModel("Models/DefaultCube/DefaultCube.fbx");
     floor->name = "Floor";
     floor->transform.SetPosition(glm::vec3(0, 0, 0));
     //floor->transform.SetRotation(glm::vec3(0));
     floor->transform.SetScale(glm::vec3(2, 0.1f, 2));
     GraphicsRender::GetInstance().AddModelAndShader(floor, defaultShader);
     floor->Initialize(RigidBody::RigidBodyType::STATIC, BaseCollider::ColliderShape::BOX);

     PhysXObject* sphere = new PhysXObject();
     sphere->LoadModel("Models/DefaultSphere/DefaultSphere.fbx");
     sphere->name = "Sphere";
     sphere->transform.SetPosition(glm::vec3(0, 10, 1));
     sphere->transform.SetRotation(glm::vec3(0, 0, 0));
     sphere->transform.SetScale(glm::vec3(0.5f));
     GraphicsRender::GetInstance().AddModelAndShader(sphere, defaultShader);
     sphere->Initialize(RigidBody::RigidBodyType::DYNAMIC, BaseCollider::ColliderShape::CAPSULE);
     sphere->rigidBody->freezeRotation = Contraints(true, false, true);
  /*   sphere->collider->AsCapsuleCollider()->SetRadius(0.5f);
     sphere->collider->AsCapsuleCollider()->SetHalfLength(5);*/

      PhysicsMaterial material;
     material.dynamicFriction = 2;
     material.bounciness = 0.2f;
     sphere->collider->SetPhysicsMaterial(material);
     //sphere->collider->SetTriggerState(true);

    // PhysXObject* terrainPhyx = new PhysXObject();
    // terrainPhyx->LoadModel("Models/Terrain/Terrain.ply");
    // terrainPhyx->transform.SetPosition(glm::vec3(0, -10, 0));
     //floor->transform.SetRotation(glm::vec3(0));
    // terrainPhyx->transform.SetScale(glm::vec3(0.5f));
    // GraphicsRender::GetInstance().AddModelAndShader(terrainPhyx, defaultShader);
   //  terrainPhyx->Initialize(RigidBody::RigidBodyType::STATIC, BaseCollider::ColliderShape::MESH);

}


void ApplicationRenderer::Render()
{


    Start();
  
    EditorLayout::GetInstance().InitializeEditors();

    Time::GetInstance().lastFrame = glfwGetTime();
   // glEnable(GL_BLEND);
  //  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
   
    while (!glfwWindowShouldClose(window))
    {

        Time::GetInstance().SetCurrentTime(glfwGetTime());
       
      
       // scrollTime += Time::GetInstance().deltaTime;

        EngineGameLoop();

        EngineGraphicsRender();


        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    ShutDown();

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();
}

void ApplicationRenderer::EngineGraphicsRender()
{

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    ImGuizmo::BeginFrame();

    if (isImguiPanelsEnable)
    {
        PanelManager::GetInstance().Update((float)windowWidth, (float)WindowHeight);
    }

   


    /*sceneViewframeBuffer->Bind();

    GraphicsRender::GetInstance().Clear();
    PreRender();
    GraphicsRender::GetInstance().Draw();

    sceneViewframeBuffer->Unbind();*/
    RenderForCamera(sceneViewcamera, sceneViewframeBuffer);


  /*  RenderForCamera(gameScenecamera, gameframeBuffer);

    RenderForCamera(renderTextureCamera, renderTextureCamera->renderTexture->framebuffer);*/


    for (Camera* camera :  CameraManager::GetInstance().GetCameras())
    {
        if (camera->renderTexture == nullptr)
        {
            RenderForCamera(camera, gameframeBuffer);                  // GAME SCENE CAMERA

           
        }
        else
        {
            RenderForCamera(camera, camera->renderTexture->framebuffer); 
        }
       
    }

    //gameframeBuffer->Bind();
    //GraphicsRender::GetInstance().Clear();
    //PreRender();
    //GraphicsRender::GetInstance().Draw();

    //gameframeBuffer->Unbind();
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

}

void ApplicationRenderer::EngineGameLoop()
{
    ProcessInput(window);

    if (isPlayMode)
    {
        EntityManager::GetInstance().Update(Time::GetInstance().deltaTime);

        PhysXEngine::GetInstance().InitializePhysXObjects();
        PhysXEngine::GetInstance().Update(Time::GetInstance().deltaTime);
    }

    PostRender();
}
void ApplicationRenderer::RenderForCamera(Camera* camera, FrameBuffer* framebuffer)
{

  /*  sceneViewframeBuffer->Bind();

    GraphicsRender::GetInstance().Clear();
    PreRender();
    GraphicsRender::GetInstance().Draw();*/


    framebuffer->Bind();

    GraphicsRender::GetInstance().Clear();

    projection = camera->GetProjectionMatrix();

    view = camera->GetViewMatrix();

    skyBoxView = glm::mat4(glm::mat3(camera->GetViewMatrix()));


    defaultShader->Bind();
    LightManager::GetInstance().UpdateUniformValuesToShader(defaultShader);

    defaultShader->setMat4("projection", projection);
    defaultShader->setMat4("view", view);
    defaultShader->setVec3("viewPos", camera->transform.position.x, camera->transform.position.y, camera->transform.position.z);
    defaultShader->setFloat("time", scrollTime);
    defaultShader->setBool("isDepthBuffer", false);

    animationShader->Bind();
    LightManager::GetInstance().UpdateUniformValuesToShader(animationShader);
    animationShader->setMat4("projection", projection);
    animationShader->setMat4("view", view);
    animationShader->setVec3("viewPos", sceneViewcamera->transform.position.x, sceneViewcamera->transform.position.y, sceneViewcamera->transform.position.z);
    animationShader->setBool("isDepthBuffer", false);


    alphaBlendShader->Bind();
    LightManager::GetInstance().UpdateUniformValuesToShader(alphaBlendShader);
    alphaBlendShader->setMat4("projection", projection);
    alphaBlendShader->setMat4("view", view);
    alphaBlendShader->setVec3("viewPos", camera->transform.position.x, camera->transform.position.y, camera->transform.position.z);
    alphaBlendShader->setFloat("time", scrollTime);
    alphaBlendShader->setBool("isDepthBuffer", false);

    alphaCutoutShader->Bind();
    LightManager::GetInstance().UpdateUniformValuesToShader(alphaCutoutShader);
    alphaCutoutShader->setMat4("projection", projection);
    alphaCutoutShader->setMat4("view", view);
    alphaCutoutShader->setVec3("viewPos", camera->transform.position.x, camera->transform.position.y, camera->transform.position.z);
    alphaCutoutShader->setFloat("time", scrollTime);
    alphaCutoutShader->setBool("isDepthBuffer", false);

    solidColorShader->Bind();
    solidColorShader->setMat4("projection", projection);
    solidColorShader->setMat4("view", view);

    stencilShader->Bind();
    stencilShader->setMat4("projection", projection);
    stencilShader->setMat4("view", view);

    glDepthFunc(GL_LEQUAL);
    skyboxShader->Bind();
    skyboxShader->setMat4("projection", projection);
    skyboxShader->setMat4("view", skyBoxView);

    GraphicsRender::GetInstance().SkyBoxModel->Draw(skyboxShader);
    glDepthFunc(GL_LESS);

    
    /* ScrollShader->Bind();
       ScrollShader->setMat4("ProjectionMatrix", _projection);*/

    GraphicsRender::GetInstance().Draw();

    framebuffer->Unbind();

    if (camera->isPostprocessing)
    {
       // if (camera->postprocessing.isPostProccesingEnabled)
        {
            camera->postprocessing->ApplyPostprocessing(framebuffer);
        }
    }



}
void ApplicationRenderer::PostRender()
{
  

}

void ApplicationRenderer::Clear()
{
    GLCALL(glClearColor(0.1f, 0.1f, 0.1f, 0.1f));
    GLCALL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT));
   //glStencilMask(0x00);
}

void ApplicationRenderer::ShutDown()
{
    PhysXEngine::GetInstance().ShutDown();
}

void ApplicationRenderer::ProcessInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    float cameraSpeed=25;

    if (EditorLayout::GetInstance().IsViewportHovered())
    {
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        {
            sceneViewcamera->ProcessKeyboard(FORWARD, Time::GetInstance().deltaTime * cameraSpeed);
        }
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        {
            sceneViewcamera->ProcessKeyboard(BACKWARD, Time::GetInstance().deltaTime * cameraSpeed);
        }

        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        {
            sceneViewcamera->ProcessKeyboard(LEFT, Time::GetInstance().deltaTime * cameraSpeed);

        }
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        {
            sceneViewcamera->ProcessKeyboard(RIGHT, Time::GetInstance().deltaTime * cameraSpeed);

        }
    }

}


 void ApplicationRenderer::SetViewPort(GLFWwindow* window, int width, int height)
{
 //   glViewport(0, 0, width, height);
}

 void ApplicationRenderer::KeyCallBack(GLFWwindow* window, int key, int scancode, int action, int mods)
 {  
         if (key == GLFW_KEY_V && action == GLFW_PRESS)
         {

            
             std::cout << "V pressed" << std::endl;

             std::vector<Model*> listOfModels = GraphicsRender::GetInstance().GetModelList();
            
          

             selectedModelCount++;

             if (selectedModelCount > listOfModels.size()-1)
             {
                 selectedModelCount = 0;
             }

            
             GraphicsRender::GetInstance().selectedModel = listOfModels[selectedModelCount];


         }
     
         if (action == GLFW_PRESS)
         {
             InputManager::GetInstance().OnKeyPressed(key);
         }
         else if(action == GLFW_RELEASE)
         {
             InputManager::GetInstance().OnKeyReleased(key);
         }
         else if (action == GLFW_REPEAT)
         {
             InputManager::GetInstance().OnkeyHold(key);
         }
     
 }

 void ApplicationRenderer::MouseCallBack(GLFWwindow* window, double xposIn, double yposIn)
 {

    float xpos = static_cast<float>(xposIn);
        float ypos = static_cast<float>(yposIn);
     
        if (firstMouse)
        {

        }

         if (firstMouse)
         {
             lastX = xpos;
             lastY = ypos;
             firstMouse = false;
         }
     
         float xoffset = xpos - lastX;
         float yoffset = lastY - ypos;
     
         lastX = xpos;
         lastY = ypos;
     
         if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS && EditorLayout::GetInstance().IsViewportHovered())
         {
             sceneViewcamera->ProcessMouseMovement(xoffset, yoffset);
         }
 }

 void ApplicationRenderer::MouseScroll(GLFWwindow* window, double xoffset, double yoffset)
 {
     sceneViewcamera->ProcessMouseScroll(static_cast<float>(yoffset));
 }
