#include <iostream>
#include "Camera.h"
#include "CameraManager.h"
#include "GraphicsRender.h"

Camera::Camera()
{
    name = "Camera";
    tag = "Camera";
    
    CameraManager::GetInstance().AddCamera(this);
}

Camera::~Camera()
{
    CameraManager::GetInstance().RemoveCamera(this);

}

//Camera::Camera(glm::vec3 position, glm::vec3 up) : MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), fov(ZOOM)
//{
//    // Position = position;
//   //  WorldUp = up;
//    // Yaw = yaw;
//    // Pitch = pitch;
//
//
//     //Initial Values
//    transform.SetPosition(glm::vec3(position));
//    transform.SetOrientationFromDirections(up, up);
//    transform.SetRotation(glm::vec3(0.0f, 180, 0.0f));
//    name = "Camera";
//
//    SetCameraType(CameraType::PERSPECTIVE);
//
//    SetProjection();
//
//    InitializeEntity(this);
//}
//
//Camera::Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) : MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), fov(ZOOM)
//{
//    // Position = glm::vec3(posX, posY, posZ);
//    // WorldUp = glm::vec3(upX, upY, upZ);
//    // Yaw = yaw;
//    // Pitch = pitch;
//    name = "Camera";
//
//    //Initial Values
//    transform.SetPosition(glm::vec3(posX, posY, posZ));
//    transform.SetOrientationFromDirections(glm::vec3(0, 1, 0), glm::vec3(0, 1, 0));
//    transform.SetRotation(glm::vec3(0.0f, 180.0f, 0.0f));
//
//    SetCameraType(CameraType::PERSPECTIVE);
//
//    SetProjection();
//
//    InitializeEntity(this);
//}



// returns the view matrix calculated using Euler Angles and the LookAt Matrix
glm::mat4 Camera::GetViewMatrix()
{
    glm::mat4 viewMat = glm::mat4(1.0f);
    viewMat = glm::lookAt(transform.position, transform.position + transform.GetForward(), transform.GetUp());
    return viewMat;
}

//void Camera::InitializeCamera(const CameraType& cameraType)
//{
//    transform.SetPosition(glm::vec3(glm::vec3(0.0f, 0.0f, 0.0f)));
//
//    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
//    transform.SetOrientationFromDirections(up, up);
//
//    transform.SetRotation(glm::vec3(0.0f, 180, 0.0f));
//
//    MovementSpeed = SPEED;
//    MouseSensitivity = SENSITIVITY;
//    fov = ZOOM;
//    nearPlane = DEFAULT_NEARPLANE;
//    farPlane = DEFAULT_FARPLANE;
//
//
//    SetCameraWidthAndHeight(DEFAULT_WIDTH, DEFAULT_HEIGHT);
//
//    SetCameraType(cameraType);
//
//
//    SetProjection();
//
//    InitializeEntity(this);
//}

void Camera::InitializeCamera(CameraType cameraType, float fov, float nearPlane, float farPlane)
{

    transform.SetPosition(glm::vec3(glm::vec3(0.0f, 0.0f, 0.0f)));

    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
    transform.SetOrientationFromDirections(up, up);

    transform.SetRotation(glm::vec3(0.0f, 180, 0.0f));

    MovementSpeed = SPEED;
    MouseSensitivity = SENSITIVITY;
    this->fov = fov;
    this->nearPlane = nearPlane;
    this->farPlane = farPlane;


    SetCameraWidthAndHeight(DEFAULT_WIDTH, DEFAULT_HEIGHT);

    SetCameraType(CameraType::PERSPECTIVE);


    SetProjection();

    postprocessing = new PostProcessing(glm::vec2(cameraWidth, cameraHeight));

    InitializeEntity(this);

 
}

void Camera::IntializeRenderTexture(FrameBufferSpecification framebufferSpecs)
{
    renderTexture = new RenderTexture(framebufferSpecs);


}

void Camera::SetProjection()
{
    aspectRatio = cameraWidth / cameraHeight;
    
    if (cameraType == CameraType::PERSPECTIVE)
    {
      

       projectionMatrix = glm::perspective(glm::radians(fov), aspectRatio, nearPlane, farPlane);
    }
    else
    {
       
        float orthoLeft = -cameraWidth / 2.0f;
        float orthoRight = cameraWidth / 2.0f;
        float orthoBottom = -cameraHeight / 2.0f;
        float orthoTop = cameraHeight / 2.0f;


        projectionMatrix = glm::ortho(orthoLeft, orthoRight, orthoBottom, orthoTop, nearPlane, farPlane);
     
    }
    
}

// processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
void Camera::ProcessKeyboard(Camera_Movement direction, float deltaTime)
{
    float velocity = MovementSpeed * deltaTime;
    if (direction == FORWARD)
        transform.position += transform.GetForward() * velocity;
    if (direction == BACKWARD)
        transform.position -= transform.GetForward() * velocity;
    if (direction == LEFT)
        transform.position -= transform.GetRight() * velocity;
    if (direction == RIGHT)
        transform.position += transform.GetRight() * velocity;
}

// processes input received from a mouse input system. Expects the offset value in both the x and y direction.
void Camera::ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch)
{
    xoffset *= MouseSensitivity;
    yoffset *= MouseSensitivity;

    transform.rotation.y -= xoffset;
    transform.rotation.x += yoffset;

    // make sure that when pitch is out of bounds, screen doesn't get flipped
    if (constrainPitch)
    {
        if (transform.rotation.z == 180 || transform.rotation.z == -180)
        {
            if (transform.rotation.x > 89.0f + 180)	transform.rotation.x = 89.0f + 180;
            if (transform.rotation.x < -89.0f - 180)	transform.rotation.x = -89.0f - 180;
        }
        else
        {
            if (transform.rotation.x > 89.0f)	transform.rotation.x = 89.0f;
            if (transform.rotation.x < -89.0f)	transform.rotation.x = -89.0f;
        }
    }

    // update Front, Right and Up Vectors using the updated Euler angles
    transform.SetRotation(transform.rotation);
}

// processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
void Camera::ProcessMouseScroll(float yoffset)
{
    fov -= (float)yoffset;
    if (fov < 1.0f)
        fov = 1.0f;
    if (fov > 45.0f)
        fov = 45.0f;
}


void Camera::updateCameraVectors()
{
    // calculate the new Front vector
    glm::vec3 front;
    front.x = cos(glm::radians(transform.rotation.y)) * cos(glm::radians(transform.rotation.x));
    front.y = sin(glm::radians(transform.rotation.x));
    front.z = sin(glm::radians(transform.rotation.y)) * cos(glm::radians(transform.rotation.x));

    transform.SetForward(glm::normalize(front));

    

    
}

void Camera::Resize(float width, float height)
{
    this->cameraWidth = width;
    this->cameraHeight = height;

    SetProjection();
}

void Camera::SetCameraType(const CameraType& type)
{
    this->cameraType = type;
}

void Camera::SetCameraWidthAndHeight(float width, float height)
{
    cameraWidth = width;
    cameraHeight = height;
}

Transform* Camera::GetTransform()
{
    return &transform;
}

glm::mat4 Camera::GetProjectionMatrix()
{
    return projectionMatrix;
}

void Camera::Start()
{
}

void Camera::Update(float deltaTime)
{
}

void Camera::OnDestroy()
{
}

void Camera::DrawProperties()
{
    Entity::DrawProperties();

    ImGui::NewLine();
    ImGui::Checkbox("Post processing", &isPostprocessing);

    if (isPostprocessing)
    {
        postprocessing->DrawProperties();
    }

}

void Camera::SceneDraw()
{
    Entity::SceneDraw();
   // postprocessing.SceneDraw();

}

void Camera::Render()
{
}
