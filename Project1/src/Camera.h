#pragma once
#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

//#include "Transform.h"
#include "EntityManager/Entity.h"
#include <vector>
#include "RenderTexture.h"
#include "PostProcessing/PostProcessing.h"

enum Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};


const float SPEED = 0.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;
const float DEFAULT_WIDTH = 1920;
const float DEFAULT_HEIGHT = 1080;
const float DEFAULT_NEARPLANE = 0.1f;
const float DEFAULT_FARPLANE = 100.0f;


enum class CameraType
{
    PERSPECTIVE = 0,
    ORTHOGRAPHIC = 1
};

class Camera : public Entity
{
public:
    
    // camera options
    float MovementSpeed;
    float MouseSensitivity;
    float fov;
    float cameraWidth;
    float cameraHeight;
    float nearPlane;
    float farPlane;
    bool isPostprocessing = false;
    RenderTexture* renderTexture = nullptr;
    CameraType cameraType = CameraType::PERSPECTIVE;
    PostProcessing* postprocessing;

        // constructor with vectors
    Camera();
    ~Camera();
   // Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f));
        

        // constructor with scalar values
   // Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);


   // Transform transform;


        // returns the view matrix calculated using Euler Angles and the LookAt Matrix
        glm::mat4 GetViewMatrix();

       // void InitializeCamera(const CameraType& cameraType = CameraType::PERSPECTIVE);
        void InitializeCamera(CameraType cameraType = CameraType::PERSPECTIVE, float fov = ZOOM, float nearPlane = DEFAULT_NEARPLANE, float farPlane = DEFAULT_FARPLANE);


        void IntializeRenderTexture(FrameBufferSpecification framebufferSpecs);

        void SetProjection();
  

        // processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
        void ProcessKeyboard(Camera_Movement direction, float deltaTime);


        // processes input received from a mouse input system. Expects the offset value in both the x and y direction.
        void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true);

        // processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
        void ProcessMouseScroll(float yoffset);
   
        void updateCameraVectors();

        void Resize(float width,float height);

        void SetCameraType(const CameraType& type);

        void SetCameraWidthAndHeight(float width, float height);

        Transform* GetTransform();
        glm::mat4 GetProjectionMatrix();

        // Inherited via Entity
        void Start() override;

        void Update(float deltaTime) override;

        void OnDestroy() override;

        // Inherited via object
        void DrawProperties() override;
        void SceneDraw() override;
        void Render() override;
private:
    glm::mat4 projectionMatrix;
    float aspectRatio;
};
#endif