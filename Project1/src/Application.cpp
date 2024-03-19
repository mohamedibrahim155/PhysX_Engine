//
//
//
//#include "Shader.h"
//#include <glad/glad.h>
//
//
//#define GLFW_INCLUDE_NONE
//#include <GLFW/glfw3.h>
//
//#include "Application.h"
//
//#include <iostream>
//#include <fstream>
//#include <sstream>
//#include <Windows.h>
//
//#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/type_ptr.hpp>
//
//#include <imgui.h>
//#include <imgui_impl_glfw.h>
//#include <imgui_impl_opengl3.h>
//
//#include "Camera.h"
//#include "VertexBuffer.h"
//#include "VertexBufferLayout.h"
//#include "Renderer.h"
//#include "VertexArray.h"
//#include  "model.h"
//
//#include "material.h"
//#include "Light.h"
//
//#include "Transform.h"
//#include"LightManager.h"
//#include "Random.h"
//
//
//
//
//bool switchCamera = false;
//bool switchToPointLight = false;
//bool isTestingModel = false;
//
//Model* testMod;
//
//glm::vec3 currentLight(1.0f, 0.0f, 1.0f);
//glm::vec3 spotlightPos(1.0f, 0.0f, 1.0f);
//glm::vec3 PointLightPos(-1.0f, 0.0f, 1.0f);
//
//bool isMove = false;
//
//void processInput(GLFWwindow* window);
//void mouse_callback(GLFWwindow* window, double xpos, double ypos);
//void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
//void CheckingValues(Model* testModel, float x, float y, float z);
//void framebuffer_size_callback(GLFWwindow* window, int width, int height)
//{
//    glViewport(0, 0, width, height);
//}
//
//void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
//{
//    if (key == GLFW_KEY_V && action == GLFW_PRESS)
//    {
//        isMove =  !isMove;
//    }
//   
//
//}
//
//void Instantiate(Model* model);
//const unsigned int SCR_WIDTH = 1920;
//const unsigned int SCR_HEIGHT = 1080;
//
//glm::vec3 camPos;
//
//Camera camera(glm::vec3(camPos.x, camPos.y, camPos.z));
//
//
//float lastX = SCR_WIDTH / 2.0f;
//float lastY = SCR_HEIGHT / 2.0f;
//bool firstMouse = true;
//
//
//float deltaTime = 0.0f;
//float lastFrame = 0.0f;
//
//
//std::vector<Model*> loadedMeshes;
//std::vector<Model*> lights;
//
//struct ModelData 
//{
//    
//
//    std::string path;
//    glm::vec3 position;
//    float angle;
//    glm::vec3 rotation;
//    glm::vec3 scale;
//};
//
//std::vector<ModelData> loadModelDataFromFile(const std::string& filePath) 
//{
//
//
//    std::ifstream file(filePath);
//    std::vector<ModelData> modelData;
//
//    if (!file.is_open()) {
//        std::cerr << "Failed to open file: " << filePath << std::endl;
//        return modelData;
//    }
//
//    std::string line;
//    ModelData currentModel;
//
//    while (std::getline(file, line)) 
//    {
//        std::istringstream iss(line);
//        std::string token;
//        iss >> token;
//
//        if (token == "ModelPath:") {
//            iss >> currentModel.path;
//        }
//        else if (token == "ModelPosition:") {
//            iss >> currentModel.position.x >> currentModel.position.y >> currentModel.position.z;
//        }
//        else if (token == "angle:") {
//            iss >> currentModel.angle;
//        }
//        else if (token == "ModelRotation:") {
//           
//            iss >> currentModel.rotation.x >> currentModel.rotation.y >> currentModel.rotation.z;
//           
//        }
//        else if (token == "ModelScale:") {
//            iss >> currentModel.scale.x >> currentModel.scale.y >> currentModel.scale.z;
//            modelData.push_back(currentModel);
//        }
//    }
//
//    file.close();
//    return modelData;
//}
//
//int main()
//{
//
//
//
//    glfwInit();
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//
//
//
//
//    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "KAIZOKU", NULL, NULL);
//    if (window == NULL)
//    {
//        std::cout << "Failed to create GLFW window" << std::endl;
//        glfwTerminate();
//        return -1;
//    }
//    glfwMakeContextCurrent(window);
//    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
//    glfwSetCursorPosCallback(window, mouse_callback);
//    glfwSetScrollCallback(window, scroll_callback);
//    glfwSetKeyCallback(window, key_callback);
//
//    IMGUI_CHECKVERSION();
//    ImGui::CreateContext();
//    ImGuiIO& io = ImGui::GetIO(); (void)io;
//    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
//    ImGui::StyleColorsDark();
//    ImGui_ImplGlfw_InitForOpenGL(window, true);
//    ImGui_ImplOpenGL3_Init("#version 330");
//
//    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
//    {
//        std::cout << "Failed to initialize GLAD" << std::endl;
//        return -1;
//    }
//
//
//
//    glEnable(GL_DEPTH_TEST);
//
//
//
//   
//    Shader defaultShader("Shaders/Light_VertexShader.vert", "Shaders/Light_FragmentShader.frag");
//    Shader lightShader("Shaders/lighting.vert", "Shaders/lighting.frag");
//
//   
//    std::vector<ModelData> modelData = loadModelDataFromFile("../Project1/src/Model.txt");
//
//    camera.Position = modelData[50].position;
//    
//    Model* Table = new Model(modelData[0].path, false, true);
//    Table->transform.translate(glm::vec3(modelData[0].position.x, modelData[0].position.y, modelData[0].position.z));
//    loadedMeshes.push_back(Table);  
//
//
//    Model* TableOne = new Model(modelData[1].path, false, true);
//    TableOne->transform.translate(glm::vec3(modelData[1].position.x, modelData[1].position.y, modelData[1].position.z));
//    TableOne->transform.rotate(modelData[1].angle , glm::vec3(modelData[1].rotation.x, modelData[1].rotation.y, modelData[1].rotation.z));
//    loadedMeshes.push_back(TableOne);
//
//
//
//    Model* Floor = new Model(modelData[2].path, false, true);
//    Floor->transform.translate(glm::vec3(modelData[2].position.x, modelData[2].position.y, modelData[2].position.z));
//    loadedMeshes.push_back(Floor);
//
//    Model* FloorDeco = new Model(modelData[3].path, false, true);
//    FloorDeco->transform.translate(glm::vec3(modelData[3].position));
//    loadedMeshes.push_back(FloorDeco);
//
//
//    for (size_t i = 0; i < 5; i++)
//    {
//        for (size_t j = 0; j < 10; j++)
//        {
//
//            if (i == 2 && j == 6
//                || i == 3 && j == 6 )
//            {
//                continue;
//            }
//
//
//            Model* clonedFloor = new Model();
//            clonedFloor->meshes = std::vector<Mesh>(Floor->meshes.begin(), Floor->meshes.end());
//            clonedFloor->transform.translate(glm::vec3(modelData[4].position.x + (i * 2.0f),  0,  (j * 2.0f)));
//            loadedMeshes.push_back(clonedFloor);
//        }
//
//    }
//
//    for (size_t i = 1; i < 5; i++)
//    {
//        for (size_t j = 0; j < 2; j++)
//        {
//            Model* clonedFloorUp = new Model();
//            clonedFloorUp->meshes = std::vector<Mesh>(Floor->meshes.begin(), Floor->meshes.end());
//            clonedFloorUp->transform.translate(glm::vec3(i * 2.0f , modelData[5].position.y, modelData[5].position.z + (j*1.0f)));
//            loadedMeshes.push_back(clonedFloorUp);
//        }
//       
//
//    }
//   
//
//
//
//    Model* KeyTable = new Model(modelData[6].path, false, true);
//    KeyTable->transform.translate(glm::vec3(modelData[6].position.x, modelData[6].position.y, modelData[6].position.z));
//    loadedMeshes.push_back(KeyTable);
//
//
//    Model* Barrel = new Model(modelData[7].path, false, true);
//    Barrel->transform.translate(glm::vec3(modelData[7].position.x, modelData[7].position.y, modelData[7].position.z));
//    loadedMeshes.push_back(Barrel);
//
//    Model* Stairs = new Model(modelData[8].path, false, true);
//    Stairs->transform.translate(glm::vec3(modelData[8].position.x, modelData[8].position.y, modelData[8].position.z));
//    Stairs->transform.rotate(modelData[8].angle , glm::vec3(modelData[8].rotation.x, modelData[8].rotation.y, modelData[8].rotation.z));
//    loadedMeshes.push_back(Stairs);
//
//    Model* BoxStack = new Model(modelData[9].path, false, true);
//    BoxStack->transform.translate(glm::vec3(modelData[9].position.x, modelData[9].position.y, modelData[9].position.z));
//    loadedMeshes.push_back(BoxStack);
//    
//    Model* Torch = new Model(modelData[10].path, false, true);
//    Torch->transform.translate(glm::vec3(modelData[43].position.x, modelData[43].position.y, modelData[43].position.z));
//    Torch->transform.rotate(modelData[43].angle, glm::vec3(modelData[43].rotation.x, modelData[43].rotation.y, modelData[43].rotation.z));
//    loadedMeshes.push_back(Torch);
//
//    for (size_t i = 0; i < 2; i++)
//    {
//        Model* clonedTorch= new Model();
//        clonedTorch->meshes = std::vector<Mesh>(Torch->meshes.begin(), Torch->meshes.end());
//        clonedTorch->transform.translate(glm::vec3(modelData[10].position.x + (i * 1.8f), modelData[10].position.y, modelData[10].position.z));
//        loadedMeshes.push_back(clonedTorch);
//    }
//
//    for (size_t i = 0; i < 3; i++)  
//    {
//        Model* clonedTorch = new Model();
//        clonedTorch->meshes = std::vector<Mesh>(Torch->meshes.begin(), Torch->meshes.end());
//        clonedTorch->transform.translate(glm::vec3(modelData[11].position.x, modelData[11].position.y, modelData[11].position.z + (i * 3.5f)));
//        clonedTorch->transform.rotate(modelData[11].angle , glm::vec3(modelData[11].rotation.x, modelData[11].rotation.y, modelData[11].rotation.z));
//        loadedMeshes.push_back(clonedTorch);
//    }
//   
//
//    Model* ShieldSword = new Model(modelData[12].path, false, true);
//    ShieldSword->transform.translate(glm::vec3(modelData[12].position.x, modelData[12].position.y, modelData[12].position.z));
//    loadedMeshes.push_back(ShieldSword);
//
//    
//    Model* BarrierCorner = new Model(modelData[13].path, false, true);
//    BarrierCorner->transform.translate(glm::vec3(modelData[13].position.x, modelData[13].position.y, modelData[13].position.z));
//    loadedMeshes.push_back(BarrierCorner);
//
//
//    Model* BarrierCorner2 = new Model(modelData[14].path, false, true);
//    BarrierCorner2->transform.translate(glm::vec3(modelData[14].position.x, modelData[14].position.y, modelData[14].position.z));
//    BarrierCorner2->transform.rotate(modelData[14].angle, glm::vec3(modelData[14].rotation.x, modelData[14].rotation.y, modelData[14].rotation.z));
//    loadedMeshes.push_back(BarrierCorner2);
//
//
//
//
//    Model* BarrierColumn = new Model(modelData[15].path, false, true);
//
//    for (size_t i = 0; i < 2; i++)
//    {
//        Model* clonedBarrier = new Model();
//        clonedBarrier->meshes = std::vector<Mesh>(BarrierColumn->meshes.begin(), BarrierColumn->meshes.end());
//        clonedBarrier->transform.translate(glm::vec3(modelData[15].position.x + (i * 2.0f), modelData[15].position.y, modelData[15].position.z));
//        loadedMeshes.push_back(clonedBarrier);
//
//    }
//
//
//
//
//    
//
//
//    Model* Wall = new Model(modelData[16].path, false, true);
//   
//
//    for (size_t i = 0; i < 8; i++)
//    {
//
//        if (i == 6)
//        {
//            continue;
//        }
//        Model* clonedWall = new Model();
//        clonedWall->meshes = std::vector<Mesh>(Wall->meshes.begin(), Wall->meshes.end());
//        clonedWall->transform.translate(glm::vec3(modelData[16].position.x, modelData[16].position.y, modelData[16].position.z  + ( i* 2.0f)));
//        clonedWall->transform.rotate(modelData[16].angle, glm::vec3(modelData[16].rotation.x, modelData[16].rotation.y, modelData[16].rotation.z));
//        loadedMeshes.push_back(clonedWall);
//    }
//
//    for (size_t i = 0; i < 3; i++)
//    {
//        Model* clonedWall2 = new Model();
//        clonedWall2->meshes = std::vector<Mesh>(Wall->meshes.begin(), Wall->meshes.end());
//        clonedWall2->transform.translate(glm::vec3(modelData[17].position.x + (i * 2.0f), modelData[17].position.y, modelData[17].position.z));
//        loadedMeshes.push_back(clonedWall2);
//    }
//
//
//    for (size_t i = 0; i < 3; i++)
//    {
//        Model* clonedWall2 = new Model();
//        clonedWall2->meshes = std::vector<Mesh>(Wall->meshes.begin(), Wall->meshes.end());
//        clonedWall2->transform.translate(glm::vec3(modelData[18].position.x + (i * 2.0f), modelData[18].position.y, modelData[18].position.z));
//        loadedMeshes.push_back(clonedWall2);
//    }
//
//    for (size_t i = 0; i < 3; i++)
//    {
//        Model* clonedWall2 = new Model();
//        clonedWall2->meshes = std::vector<Mesh>(Wall->meshes.begin(), Wall->meshes.end());
//        clonedWall2->transform.translate(glm::vec3(modelData[19].position.x + (i * 2.0f), modelData[19].position.y, modelData[19].position.z));
//        loadedMeshes.push_back(clonedWall2);
//    }
//
//    for (size_t i = 0; i < 3; i++)
//    {
//        Model* clonedWall2 = new Model();
//        clonedWall2->meshes = std::vector<Mesh>(Wall->meshes.begin(), Wall->meshes.end());
//        clonedWall2->transform.translate(glm::vec3(modelData[20].position.x + (i * 2.0f), modelData[20].position.y, modelData[20].position.z));
//        loadedMeshes.push_back(clonedWall2);
//    }
//
//
//    for (size_t i = 0; i < 8; i++)
//    {
//        Model* clonedWall3 = new Model();
//        clonedWall3->meshes = std::vector<Mesh>(Wall->meshes.begin(), Wall->meshes.end());
//        clonedWall3->transform.translate(glm::vec3(modelData[21].position.x, modelData[21].position.y, modelData[21].position.z + (i * 2.0f)));
//        clonedWall3->transform.rotate(modelData[21].angle, glm::vec3(modelData[21].rotation.x, modelData[21].rotation.y, modelData[21].rotation.z));
//        loadedMeshes.push_back(clonedWall3);
//    }
//
//
//    for (size_t i = 0; i < 8; i++)
//    {
//        Model* clonedWall3 = new Model();
//        clonedWall3->meshes = std::vector<Mesh>(Wall->meshes.begin(), Wall->meshes.end());
//        clonedWall3->transform.translate(glm::vec3(modelData[22].position.x, modelData[22].position.y, modelData[22].position.z + (i * 2.0f)));
//        clonedWall3->transform.rotate(modelData[22].angle, glm::vec3(modelData[22].rotation.x, modelData[22].rotation.y, modelData[22].rotation.z));
//        loadedMeshes.push_back(clonedWall3);
//    }
//
//
//    for (size_t i = 0; i < 1; i++)
//    {
//        Model* clonedWall2 = new Model();
//        clonedWall2->meshes = std::vector<Mesh>(Wall->meshes.begin(), Wall->meshes.end());
//        clonedWall2->transform.translate(glm::vec3(modelData[23].position.x + (i * 2.0f), modelData[23].position.y, modelData[23].position.z));
//        loadedMeshes.push_back(clonedWall2);
//    }
//
//    
//
//    for (size_t i = 0; i < 8; i++)
//    {
//
//        if (i == 3 || i == 5 || i ==7 )
//        {
//            continue;
//        }
//
//
//        Model* clonedWallArched = new Model();
//        clonedWallArched->meshes = std::vector<Mesh>(Wall->meshes.begin(), Wall->meshes.end());
//        clonedWallArched->transform.translate(glm::vec3(modelData[24].position.x, modelData[24].position.y, modelData[24].position.z + (i * 2.0f)));
//        clonedWallArched->transform.rotate(modelData[24].angle, glm::vec3(modelData[24].rotation.x, modelData[24].rotation.y, modelData[24].rotation.z));
//        loadedMeshes.push_back(clonedWallArched);
//    }
//
//   
//
//
//    Model* WallGated = new Model(modelData[25].path, false, true);
//
//
//    for (size_t i = 0; i < 3; i++)
//    {
//        Model* clonedWallGated = new Model();
//        clonedWallGated->meshes = std::vector<Mesh>(WallGated->meshes.begin(), WallGated->meshes.end());
//        clonedWallGated->transform.translate(glm::vec3(modelData[25].position.x, modelData[25].position.y, modelData[25].position.z +(i* 4.0f)));
//        clonedWallGated->transform.rotate(modelData[25].angle, glm::vec3(modelData[25].rotation.x, modelData[25].rotation.y, modelData[25].rotation.z));
//        loadedMeshes.push_back(clonedWallGated);
//    }
//
//    
//    Model* WallDoorway = new Model(modelData[26].path, false, true);
//    WallDoorway->transform.translate(glm::vec3(glm::vec3(modelData[26].position.x, modelData[26].position.y, modelData[26].position.z)));
//    loadedMeshes.push_back(WallDoorway);
//
//    Model* WallDoorway2 = new Model(modelData[27].path, false, true);
//    WallDoorway2->transform.translate(glm::vec3(glm::vec3(modelData[27].position.x, modelData[27].position.y, modelData[27].position.z)));
//    WallDoorway2->transform.rotate(modelData[27].angle, glm::vec3(modelData[27].rotation.x, modelData[27].rotation.y, modelData[27].rotation.z));
//    loadedMeshes.push_back(WallDoorway2);
//
//    
//    Model* Crate = new Model(modelData[28].path, false, true);
//    Crate->transform.translate(glm::vec3(modelData[28].position.x, modelData[28].position.y, modelData[28].position.z));
//    loadedMeshes.push_back(Crate);
//
//
//
//    Model* Shelf = new Model(modelData[29].path, false, true);
//    Shelf->transform.translate(glm::vec3(modelData[29].position.x, modelData[29].position.y, modelData[29].position.z));
//    Shelf->transform.rotate(modelData[29].angle,glm::vec3(modelData[29].rotation.x, modelData[29].rotation.y, modelData[29].rotation.z));
//    loadedMeshes.push_back(Shelf);
//    
//
//    Model* WallCorner = new Model(modelData[30].path, false, true);
//    
//    WallCorner->transform.translate(glm::vec3(modelData[30].position.x, modelData[30].position.y, modelData[30].position.z));
//    loadedMeshes.push_back(WallCorner);
//
//    Model* WallCornerUp = new Model(modelData[31].path, false, true);
//    WallCornerUp->transform.translate(glm::vec3(modelData[31].position.x, modelData[31].position.y, modelData[31].position.z));
//    loadedMeshes.push_back(WallCornerUp);
//
//
//    Model* WallCorner2 = new Model(modelData[32].path, false, true);
//    WallCorner2->transform.translate(glm::vec3(modelData[32].position.x, modelData[32].position.y, modelData[32].position.z));
//    WallCorner2->transform.rotate(modelData[32].angle, glm::vec3(modelData[32].rotation.x, modelData[32].rotation.y, modelData[32].rotation.z));
//    loadedMeshes.push_back(WallCorner2);
//
//    Model* WallCorner2Up = new Model(modelData[33].path, false, true);
//    WallCorner2Up->transform.translate(glm::vec3(modelData[33].position.x, modelData[33].position.y, modelData[33].position.z));
//    WallCorner2Up->transform.rotate(modelData[33].angle, glm::vec3(modelData[33].rotation.x, modelData[33].rotation.y, modelData[33].rotation.z));
//    loadedMeshes.push_back(WallCorner2Up);
//
//
//
//    Model* WallCorner3 = new Model(modelData[34].path, false, true);
//    WallCorner3->transform.translate(glm::vec3(modelData[34].position.x, modelData[34].position.y, modelData[34].position.z));
//    WallCorner3->transform.rotate(modelData[34].angle, glm::vec3(modelData[34].rotation.x, modelData[34].rotation.y, modelData[34].rotation.z));
//    loadedMeshes.push_back(WallCorner3);
//
//    Model* WallCorner4 = new Model(modelData[35].path, false, true);
//    WallCorner4->transform.translate(glm::vec3(modelData[35].position.x, modelData[35].position.y, modelData[35].position.z));
//    loadedMeshes.push_back(WallCorner4);
//
//    Model* WallCorner5 = new Model(modelData[36].path, false, true);
//    WallCorner5->transform.translate(glm::vec3(modelData[36].position.x, modelData[36].position.y, modelData[36].position.z));
//    WallCorner5->transform.rotate(modelData[36].angle, glm::vec3(modelData[36].rotation.x, modelData[36].rotation.y, modelData[36].rotation.z));
//    loadedMeshes.push_back(WallCorner5);
//
//    Model* WallCorner6 = new Model(modelData[37].path, false, true);
//    WallCorner6->transform.translate(glm::vec3(modelData[37].position.x, modelData[37].position.y, modelData[37].position.z));
//    WallCorner6->transform.rotate(modelData[37].angle, glm::vec3(modelData[37].rotation.x, modelData[37].rotation.y, modelData[37].rotation.z));
//    loadedMeshes.push_back(WallCorner6);
//
//
//    Model* WallCorner7 = new Model(modelData[38].path, false, true);
//    WallCorner7->transform.translate(glm::vec3(modelData[38].position.x, modelData[38].position.y, modelData[38].position.z));
//    WallCorner7->transform.rotate(modelData[38].angle, glm::vec3(modelData[38].rotation.x, modelData[38].rotation.y, modelData[38].rotation.z));
//    loadedMeshes.push_back(WallCorner7);
//
//    Model* WallCorner3Up = new Model(modelData[39].path, false, true);
//    WallCorner3Up->transform.translate(glm::vec3(modelData[39].position.x, modelData[39].position.y, modelData[39].position.z));
//    WallCorner3Up->transform.rotate(modelData[39].angle, glm::vec3(modelData[39].rotation.x, modelData[39].rotation.y, modelData[39].rotation.z));
//    loadedMeshes.push_back(WallCorner3Up);
//    
//
//    Model* BannerShield = new Model(modelData[40].path, false, true);
//    BannerShield->transform.translate(glm::vec3(modelData[40].position.x, modelData[40].position.y, modelData[40].position.z));
//    BannerShield->transform.rotate(modelData[40].angle, glm::vec3(modelData[40].rotation.x, modelData[40].rotation.y, modelData[40].rotation.z));
//    loadedMeshes.push_back(BannerShield);
//
//
//    for (size_t i = 0; i < 3; i++)
//    {
//        Model* clonedBannerShield = new Model();
//        clonedBannerShield->meshes = std::vector<Mesh>(BannerShield->meshes.begin(), BannerShield->meshes.end());
//        clonedBannerShield->transform.translate(glm::vec3(modelData[41].position.x, modelData[41].position.y, modelData[41].position.z + (i * 3.5f)));
//        clonedBannerShield->transform.rotate(modelData[41].angle, glm::vec3(modelData[41].rotation.x, modelData[41].rotation.y, modelData[41].rotation.z));
//        loadedMeshes.push_back(clonedBannerShield);
//    }
//
//    Model* Chest = new Model(modelData[42].path, false, true);
//    for (size_t i = 0; i < 3; i++)
//    {
//        Model* clonedChest = new Model();
//        clonedChest->meshes = std::vector<Mesh>(Chest->meshes.begin(), Chest->meshes.end());
//
//        clonedChest->transform.translate(glm::vec3(modelData[42].position.x + (i * 1.0f), modelData[42].position.y, modelData[42].position.z));
//        clonedChest->transform.rotate(modelData[42].angle, glm::vec3(modelData[42].rotation.x, modelData[42].rotation.y, modelData[42].rotation.z));
//         loadedMeshes.push_back(clonedChest);
//    
//
//    }
//   
//
//    Model* LightSphere = new Model(modelData[44].path, false, true);
//
//    Material material( 128.0f);
//
//
//
//    Renderer render;
//   
//
//    LightManager lightManager;
//
//    Model* dirLightModel = new Model();
//    dirLightModel->meshes = std::vector<Mesh>(LightSphere->meshes.begin(), LightSphere->meshes.end());
//    lights.push_back(dirLightModel);
//    Light directionLight;
//    directionLight.lightType = LightType:: DIRECTION_LIGHT;
//    directionLight.lightModel = dirLightModel;
//    directionLight.ambient = glm::vec3 (0.1f);
//    directionLight.diffuse = glm::vec3 (0.1f);
//    directionLight.specular = glm::vec3 (0.1f);
//
//    Model* PointLightModel = new Model();
//    PointLightModel->meshes = std::vector<Mesh>(LightSphere->meshes.begin(), LightSphere->meshes.end());
//    PointLightModel->transform.scale = glm::vec3(modelData[44].scale);
//    lights.push_back(PointLightModel);
//    Light PointLight;
//    PointLight.lightType = LightType::POINT_LIGHT;
//    PointLight.lightModel = PointLightModel;
//    PointLight.ambient =  glm::vec3(1.7);
//    PointLight.specular = glm::vec3(1.7);
//    PointLight.diffuse =  glm::vec3(1.7);
//    PointLight.quadratic = .24f;
//    PointLight.color = glm::vec3(1, 0.6f, 0.2f);
//
//
//    Model* PointLightModel1 = new Model();
//    PointLightModel1->meshes = std::vector<Mesh>(LightSphere->meshes.begin(), LightSphere->meshes.end());
//    PointLightModel1->transform.scale = glm::vec3(modelData[44].scale);
//    lights.push_back(PointLightModel1);
//    Light PointLight1;
//    PointLight1.lightType = LightType::POINT_LIGHT;
//    PointLight1.lightModel = PointLightModel1;
//    PointLight1.ambient =  glm::vec3(1.7);
//    PointLight1.specular = glm::vec3(1.7);
//    PointLight1.diffuse =  glm::vec3(1.7);
//    PointLight1.quadratic = .24f;
//    PointLight1.color = glm::vec3(1, 0.6f, 0.2f);
//
//
//    Model* PointLightModel2 = new Model();
//    PointLightModel2->meshes = std::vector<Mesh>(LightSphere->meshes.begin(), LightSphere->meshes.end());
//    PointLightModel2->transform.scale = glm::vec3(modelData[44].scale);
//    lights.push_back(PointLightModel2);
//    Light PointLight2;
//   PointLight2.lightType = LightType::POINT_LIGHT;
//   PointLight2.lightModel = PointLightModel2;
//   PointLight2.ambient =  glm::vec3(1.7);
//   PointLight2.specular = glm::vec3(1.7);
//   PointLight2.diffuse =  glm::vec3(1.7);
//   PointLight2.quadratic = .24f;
//   PointLight2.color = glm::vec3(1, 0.5f, 0.5f);
//
//
//   Model* PointLightModel3 = new Model();
//   PointLightModel3->meshes = std::vector<Mesh>(LightSphere->meshes.begin(), LightSphere->meshes.end());
//   PointLightModel3->transform.scale = glm::vec3(modelData[44].scale);
//   lights.push_back(PointLightModel3);
//   Light PointLight3;
//   PointLight3.lightType = LightType::POINT_LIGHT;
//   PointLight3.lightModel = PointLightModel3;
//   PointLight3.ambient = glm::vec3(0.7);
//   PointLight3.specular = glm::vec3(0.7);
//   PointLight3.diffuse = glm::vec3(0.7);
//   PointLight3.quadratic = .24f;
//   PointLight3.color = glm::vec3(1, 0.6f, 0.2f);
//
//
//   Model* PointLightModel4 = new Model();
//   PointLightModel4->meshes = std::vector<Mesh>(LightSphere->meshes.begin(), LightSphere->meshes.end());
//   PointLightModel4->transform.scale = glm::vec3(modelData[44].scale);
//   lights.push_back(PointLightModel4);
//   Light PointLight4;
//  PointLight4.lightType = LightType::POINT_LIGHT;
//  PointLight4.lightModel = PointLightModel4;
//  PointLight4.ambient =  glm::vec3(1.7);
//  PointLight4.specular = glm::vec3(1.7);
//  PointLight4.diffuse =  glm::vec3(1.7);
//  PointLight4.quadratic = .24f;
//  PointLight4.color = glm::vec3(1, 0.5f, 0.5f);
//
//
//   Model* PointLightModel5 = new Model();
//   PointLightModel5->meshes = std::vector<Mesh>(LightSphere->meshes.begin(), LightSphere->meshes.end());
//   PointLightModel5->transform.scale = glm::vec3(modelData[44].scale);
//   lights.push_back(PointLightModel5);
//   Light PointLight5;
//  PointLight5.lightType = LightType::POINT_LIGHT;
//  PointLight5.lightModel = PointLightModel5;
//  PointLight5.ambient =   glm::vec3(1.7);
//  PointLight5.specular =  glm::vec3(1.7);
//  PointLight5.diffuse =   glm::vec3(1.7);
//  PointLight5.quadratic = .24f;
//  PointLight5.color = glm::vec3(1, 0.2f, 0.1f);
//
//
//   /*  
//   
//
//
//    
//
//   
//
//    Model* pLightModel5 = new Model();
//    pLightModel5->meshes = std::vector<Mesh>(LightSphere->meshes.begin(), LightSphere->meshes.end());
//    lights.push_back(pLightModel5);
//    Light spotLight5;
//    spotLight5.lightType = LightType::SPOT_LIGHT;
//    spotLight5.lightModel = pLightModel5;
//    spotLight5.direction = glm::vec3(0, -1, 0);
//    spotLight5.ambient = glm::vec3(15);
//    spotLight5.specular = glm::vec3(15);
//    spotLight5.diffuse = glm::vec3(15);
//    spotLight5.cutOffAngle = 2;
//    spotLight5.outerCutOffAngle = 15;
//
//    Model* pLightModel6 = new Model();
//    pLightModel6->meshes = std::vector<Mesh>(LightSphere->meshes.begin(), LightSphere->meshes.end());
//    lights.push_back(pLightModel6);
//    Light spotLight6;
//    spotLight6.lightType = LightType::SPOT_LIGHT;
//    spotLight6.lightModel = pLightModel6;
//    spotLight6.direction = glm::vec3(0, -1, 0);
//    spotLight6.ambient = glm::vec3(15);
//    spotLight6.specular = glm::vec3(15);
//    spotLight6.diffuse = glm::vec3(15);
//    spotLight6.cutOffAngle = 15;
//    spotLight6.outerCutOffAngle = 15;
//
//    Model* redSpotLight = new Model();
//    redSpotLight->meshes = std::vector<Mesh>(LightSphere->meshes.begin(), LightSphere->meshes.end());
//    lights.push_back(redSpotLight);
//    Light spotLight7;
//    spotLight7.lightType = LightType::SPOT_LIGHT;
//   spotLight7.lightModel = redSpotLight;
//   spotLight7.direction = glm::vec3(0, 0, -1);
//   spotLight7.ambient = glm::vec3(15);
//   spotLight7.specular = glm::vec3(15);
//   spotLight7.diffuse = glm::vec3(15);
//   spotLight7.cutOffAngle = 2;
//   spotLight7.outerCutOffAngle = 10;
//   spotLight7.color = glm::vec3(255, 0, 0);
//
//
//    Model* greenSpotLight = new Model();
//    greenSpotLight->meshes = std::vector<Mesh>(LightSphere->meshes.begin(), LightSphere->meshes.end());
//    lights.push_back(greenSpotLight);
//    Light spotLight8;
//    spotLight8.lightType = LightType::SPOT_LIGHT;
//    spotLight8.lightModel = greenSpotLight;
//    spotLight8.direction = glm::vec3(0, 0, 1);
//    spotLight8.ambient = glm::vec3(15);
//    spotLight8.specular = glm::vec3(15);
//    spotLight8.diffuse = glm::vec3(15);
//    spotLight8.cutOffAngle = 2;
//    spotLight8.outerCutOffAngle = 10;
//    spotLight8.color = glm::vec3(0, 255, 0);*/
//
//    Model* pLightModel = new Model();
//    pLightModel->meshes = std::vector<Mesh>(LightSphere->meshes.begin(), LightSphere->meshes.end());
//    pLightModel->transform.scale = glm::vec3(modelData[44].scale);
//
//    lights.push_back(pLightModel);
//    Light spotLight;
//    spotLight.lightType = LightType::SPOT_LIGHT;
//    spotLight.lightModel = pLightModel;
//    spotLight.direction = glm::vec3(0, 1, 0);
//    spotLight.ambient = glm::vec3(3);
//    spotLight.specular = glm::vec3(3);
//    spotLight.diffuse = glm::vec3(3);
//    spotLight.cutOffAngle = 15;
//    spotLight.outerCutOffAngle = 35;
//    spotLight.color = glm::vec3(1, 0.8f, 0);
//
//    Model* pLightModel2 = new Model();
//    pLightModel2->meshes = std::vector<Mesh>(LightSphere->meshes.begin(), LightSphere->meshes.end());
//    pLightModel2->transform.scale = glm::vec3(modelData[44].scale);
//    lights.push_back(pLightModel2);
//    Light spotLight2;
//    spotLight2.lightType = LightType::SPOT_LIGHT;
//    spotLight2.lightModel = pLightModel2;
//    spotLight2.direction = glm::vec3(0, 1, 0);
//    spotLight2.ambient = glm::vec3(3);
//    spotLight2.specular = glm::vec3(3);
//    spotLight2.diffuse = glm::vec3(3);
//    spotLight2.cutOffAngle = 15;
//    spotLight2.outerCutOffAngle = 35;
//    spotLight2.color = glm::vec3(1, 0.8f, 0);
//
//    Model* pLightModel3 = new Model();
//    pLightModel3->meshes = std::vector<Mesh>(LightSphere->meshes.begin(), LightSphere->meshes.end());
//    pLightModel3->transform.scale = glm::vec3(modelData[44].scale);
//    lights.push_back(pLightModel3);
//    Light spotLight3;
//    spotLight3.lightType = LightType::SPOT_LIGHT;
//    spotLight3.lightModel = pLightModel3;
//    spotLight3.direction = glm::vec3(0, 1, 0);
//    spotLight3.ambient = glm::vec3(3);
//    spotLight3.specular = glm::vec3(3);
//    spotLight3.diffuse = glm::vec3(3);
//    spotLight3.cutOffAngle = 15;
//    spotLight3.outerCutOffAngle = 35;
//    spotLight3.color = glm::vec3(1, 0.8f, 0);
//    Model* pLightModel4 = new Model();
//    pLightModel4->meshes = std::vector<Mesh>(LightSphere->meshes.begin(), LightSphere->meshes.end());
//    pLightModel4->transform.scale = glm::vec3(modelData[44].scale);
//    lights.push_back(pLightModel4);
//    Light spotLight4;
//    spotLight4.lightType = LightType::SPOT_LIGHT;
//    spotLight4.lightModel = pLightModel4;
//    spotLight4.direction = glm::vec3(0, 1, 0);
//    spotLight4.ambient = glm::vec3(3);
//    spotLight4.specular = glm::vec3(3);
//    spotLight4.diffuse = glm::vec3(3);
//    spotLight4.cutOffAngle = 15;
//    spotLight4.outerCutOffAngle = 35;
//    spotLight4.color = glm::vec3(1, 0.8f, 0);
//
//
//
//    lightManager.AddNewLight(spotLight);
//    lightManager.AddNewLight(spotLight2);
//    lightManager.AddNewLight(spotLight3);
//    lightManager.AddNewLight(spotLight4);
//
//    lightManager.AddNewLight(directionLight);
//    lightManager.AddNewLight(PointLight);
//    lightManager.AddNewLight(PointLight1);
//    lightManager.AddNewLight(PointLight2);
//    lightManager.AddNewLight(PointLight3);
//    lightManager.AddNewLight(PointLight4);
//    lightManager.AddNewLight(PointLight5);
//   /* 
//   
//    
//    
//    lightManager.AddNewLight(spotLight6);
//    lightManager.AddNewLight(spotLight7);
//    lightManager.AddNewLight(spotLight8);*/
//    lightManager.SetUniforms(defaultShader.ID);
//
//    
//   
//
//    float lightSize = 0.5f;
//    float xPos = 0.0f;
//    float yPos = 0.0f;
//    float zPos = 0.0f;
//
//    float lightX = 0.0f;
//    float lightY = 0.3f;
//    float lightZ = 10.0f;
//
//    float rotX = 1.0f;
//    float rotY = 0.0f;
//    float rotZ = 0.0f;
//
//    float color[3] = { 1.0f, 1.0f, 1.0f };
//    bool isWireFrame = false;
//
// 
//    float yAxis = 10;
//
//    glm::vec3 collisionPosition = glm::vec3(0.0f);
//    
//
//    double lastTime = glfwGetTime();
//    camPos = modelData[50].position;
//
//    while (!glfwWindowShouldClose(window))
//    {
//
//
//
//       
//
//
//
//
//
//
//
//        float currentFrame = static_cast<float>(glfwGetTime());
//        deltaTime = currentFrame - lastFrame;
//        lastFrame = currentFrame;
//
//      
//        processInput(window);
//
//    
//        render.Clear();
//
//        ImGui_ImplOpenGL3_NewFrame();
//        ImGui_ImplGlfw_NewFrame();
//        ImGui::NewFrame();
//
//
//        {
//
//            static float f = 0.0f;
//            static int counter = 0;
//
//
//            //add a Title to your GUI layout
//            ImGui::Begin("Media Player Lite!");
//            // ImGui::SetWindowFontScale(2.0f);
//            ImGui::SetWindowSize(ImVec2(800, 800));
//
//            //add a intro text
//            ImGui::Text("KAIZOKU ENGINE");
//
//            ImGui::NewLine();
//            ImGui::PushItemWidth(100);
//            ImGui::SliderFloat("##X Position", &xPos, -100.0f, 100.0f, "X: %.1f", ImGuiSliderFlags_AlwaysClamp);
//            ImGui::SameLine(0, 10);
//            ImGui::SliderFloat("##Y Position", &yPos, -100.0f, 100.0f, "Y: %.1f", ImGuiSliderFlags_AlwaysClamp);
//            ImGui::SameLine(0, 10);
//            ImGui::SliderFloat("##Z Position", &zPos, -100.0f, 100.0f, "Z: %.1f", ImGuiSliderFlags_AlwaysClamp);
//            ImGui::SameLine(0, 10); ImGui::Text("POSITION");
//
//            CheckingValues(testMod, xPos, yPos, zPos);
//
//
//
//            ImGui::NewLine();
//            ImGui::PushItemWidth(150);
//            ImGui::SliderFloat("SCALE", &lightSize, 0.0f, 10.0f);
//
//           
//
//            ImGui::NewLine();
//            ImGui::Checkbox("WIREFRAME", &isWireFrame);
//
//          
//
//
//
//
//
//             //framerate
//            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
//            ImGui::End();
//
//        }
//
//
//        glm::vec3 lightPos = glm::vec3(lightX, lightY, lightZ);
//
//    
//
//
//        
//
//        // view/projection transformations
//        glm::mat4 _projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
//        glm::mat4 _view = camera.GetViewMatrix();
//        glm::mat4 _lightModel = glm::mat4(1.0f);
//
//
//
//
//
//
//
//        lightShader.Bind();
//        lightShader.setMat4("projection", _projection);
//        lightShader.setVec3("objCol", color[0], color[1], color[2]);
//        lightShader.setMat4("view", _view);
//
//        PointLightModel->transform.position = glm::vec3 (modelData[44].position.x, modelData[44].position.y, modelData[44].position.z);
//        PointLightModel1->transform.position = glm::vec3(modelData[45].position.x, modelData[45].position.y, modelData[45].position.z);
//        PointLightModel2->transform.position = glm::vec3(modelData[46].position.x, modelData[46].position.y, modelData[46].position.z);
//        PointLightModel3->transform.position = glm::vec3(modelData[47].position.x, modelData[47].position.y, modelData[47].position.z);
//        PointLightModel4->transform.position = glm::vec3(modelData[48].position.x, modelData[48].position.y, modelData[48].position.z);
//        PointLightModel5->transform.position = glm::vec3(modelData[49].position.x, modelData[49].position.y, modelData[49].position.z);
//   
//
//
//         pLightModel->transform.position = glm::vec3(modelData[46].position.x, modelData[46].position.y, modelData[46].position.z);
//        pLightModel2->transform.position = glm::vec3(modelData[47].position.x, modelData[47].position.y, modelData[47].position.z);
//        pLightModel3->transform.position = glm::vec3(modelData[48].position.x, modelData[48].position.y, modelData[48].position.z);
//        pLightModel4->transform.position = glm::vec3(modelData[49].position.x, modelData[49].position.y, modelData[49].position.z);
//      
//       
//
//       
//        defaultShader.Bind();
//        lightManager.UpdateUniformValues(defaultShader.ID);
//         material.SetMaterialProperties(defaultShader);
//      
//         glm::mat4 projection2 = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
//         glm::mat4 view2 = camera.GetViewMatrix();
//         defaultShader.setMat4("projection", projection2);
//         defaultShader.setMat4("view", view2);
//        
//
//
//#pragma region Binding
//
//         for (size_t i = 0; i < loadedMeshes.size(); i++)
//         {
//             loadedMeshes[i]->Draw(defaultShader);
//         }
//
//         for (size_t i = 0; i < lights.size(); i++)
//         {
//            lights[i]->Draw(defaultShader);
//
//         }
//        
//
//
//      
//
//#pragma endregion
//
//
//       
//       
//         defaultShader.setVec3("objPos", xPos, yPos, zPos);
//
//         if (isWireFrame)
//         {
//             glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//         }
//         else
//         {
//             glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
//
//
//         }
//
//
//        ImGui::Render();
//        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
//        glfwSwapBuffers(window);
//        glfwPollEvents();
//
//    }
//
//    
//
//
//    ImGui_ImplOpenGL3_Shutdown();
//    ImGui_ImplGlfw_Shutdown();
//    ImGui::DestroyContext();
//    glfwTerminate();
//    return 0;
//
//
//}
//
//
//void Instantiate(Model* model)
//{
//
//    Model* temp = new Model();
//    temp->meshes = std::vector<Mesh>(model->meshes.begin(), model->meshes.end());
//    loadedMeshes.push_back(temp);
//
//
//}
//
//
//
//
//void processInput(GLFWwindow* window)
//{
//    float speed = 25.0f;
//
//    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
//        glfwSetWindowShouldClose(window, true);
//
//
//    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
//    {
//
//        if (switchCamera)
//        {
//            float velocity = camera.MovementSpeed * deltaTime ;
//            currentLight += camera.Front * velocity ;
//        }
//        else
//        {
//            camera.ProcessKeyboard(FORWARD, deltaTime * speed);
//        }
//
//
//    }
//    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
//    {
//
//        if (switchCamera)
//        {
//            float velocity = camera.MovementSpeed * deltaTime ;
//            currentLight -= camera.Front * velocity * speed;
//        }
//        else
//        {
//            camera.ProcessKeyboard(BACKWARD, deltaTime * speed);
//        }
//    }
//
//    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
//    {
//        if (switchCamera)
//        {
//            float velocity = camera.MovementSpeed * deltaTime ;
//            currentLight -= camera.Right * velocity ;
//        }
//        else
//        {
//            camera.ProcessKeyboard(LEFT, deltaTime * speed);
//
//        }
//
//    }
//    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
//    {
//        if (switchCamera)
//        {
//            float velocity = camera.MovementSpeed * deltaTime ;
//            currentLight += camera.Right * velocity ;
//
//        }
//        else
//        {
//            camera.ProcessKeyboard(RIGHT, deltaTime * speed);
//
//        }
//
//    }
//
//    if (switchToPointLight)
//    {
//        PointLightPos = currentLight;
//    }
//    else
//    {
//        spotlightPos = currentLight;
//    }
//}
//
//void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
//{
//    float xpos = static_cast<float>(xposIn);
//    float ypos = static_cast<float>(yposIn);
//
//    if (firstMouse)
//    {
//        lastX = xpos;
//        lastY = ypos;
//        firstMouse = false;
//    }
//
//    float xoffset = xpos - lastX;
//    float yoffset = lastY - ypos;
//
//    lastX = xpos;
//    lastY = ypos;
//
//    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
//    {
//        camera.ProcessMouseMovement(xoffset, yoffset);
//    }
//}
//
//
//void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
//{
//    camera.ProcessMouseScroll(static_cast<float>(yoffset));
//}
//
//void CheckingValues(Model* testModel, float x, float y, float z)
//{
//    if (isTestingModel)
//    {
//        testModel->transform.position = glm::vec3(x, y, z);
//
//    }
//}
//
//
//
//
//
//
