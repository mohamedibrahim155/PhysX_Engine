#include "SceneViewportPanel.h"
#include "../GraphicsRender.h"
#include "../Math.h"
SceneViewportPanel::SceneViewportPanel()
{
    InputManager::GetInstance().AddObserver(this);
}
void SceneViewportPanel::OnRender(float windowWidth, float windowHeight)
{
   // isEnable = false;
    if (!isPanelOpen)
    {
        return;
    }

    glm::mat4 cameraView = sceneViewportCamera->GetViewMatrix();
    glm::mat4 cameraProjection = sceneViewportCamera->GetProjectionMatrix();

  

    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));

    if (!ImGui::Begin("SceneView", &isPanelOpen) || !isEnable)
    {
        ImGui::End();
        ImGui::PopStyleVar();
        return;

    }

    ImVec2 viewPortPanelSize = ImGui::GetContentRegionAvail();

    isHovered = ImGui::IsWindowHovered();

    if (viewportSize.x!= viewPortPanelSize.x ||viewportSize.y !=viewPortPanelSize.y)
    {
        viewportSize = viewPortPanelSize;

        frameBuffer->Resize(viewportSize.x, viewportSize.y);
        sceneViewportCamera->Resize(viewportSize.x, viewportSize.y);
    }
   



    Model* selectedModel = GraphicsRender::GetInstance().GetSelectedModel();

    if (selectedModel != nullptr)
    {
        ImGuizmo::SetOrthographic(false);

        ImGuizmo::SetDrawlist();

        float windowWidth = (float)ImGui::GetWindowWidth();
        float windowHeight = (float)ImGui::GetWindowHeight();

        ImGuizmo::SetRect(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y, windowWidth, windowHeight);


        glm::mat4 transform = selectedModel->transform.GetModelMatrix();

        ImGuizmo::Manipulate(glm::value_ptr(cameraView), glm::value_ptr(cameraProjection),
            gizmoType, ImGuizmo::LOCAL, glm::value_ptr(transform));

        if (ImGuizmo::IsUsing())
        {
            glm::vec3 position, rotation, scale;
            MathUtils::Math::DecomposeTransform(transform, position, rotation, scale);


           // glm::vec3 deltaRotation = rotation - selectedModel->transform.rotation;


            selectedModel->transform.SetPosition(position);
           // selectedModel->transform.rotation += deltaRotation;

           // selectedModel->transform.SetRotation(selectedModel->transform.rotation + deltaRotation)
            selectedModel->transform.SetScale(scale);
        }

    }
  




    ImGui::Image((void*)frameBuffer->GetColorAttachmentID(), viewportSize, ImVec2(0, 1), ImVec2(1, 0));

    ImGui::End();

    ImGui::PopStyleVar();



}

void SceneViewportPanel::OnKeyPressed(const int& key)
{
    if (!isHovered)
    {
        return;
    }
    if (key == GLFW_KEY_W)
    {
        gizmoType = ImGuizmo::OPERATION::TRANSLATE;
    }
    else if (key == GLFW_KEY_E)
    {
        gizmoType = ImGuizmo::OPERATION::ROTATE;
    }
    else if (key == GLFW_KEY_R)
    {
        gizmoType = ImGuizmo::OPERATION::SCALE;
    }
}

void SceneViewportPanel::OnKeyReleased(const int& key)
{
}

void SceneViewportPanel::OnKeyHold(const int& key)
{
}
