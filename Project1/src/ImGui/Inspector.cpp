#include "Inspector.h"
#include "EditorLayout.h"
void Inspector::OnRender(float windowWidth, float windowHeight)
{
    if (!isPanelOpen)
    {
        return;
    }

    //windowWidth = 400;
  //  windowHeight = 400;

    if (!ImGui::Begin("Inspector", &isPanelOpen) || !isEnable)
    {
       
        ImGui::End();
        return;

    }
   
    DrawEntityProperties();

    ImGui::End();
}

void Inspector::DrawEntityProperties()
{
    std::vector<Object*> selectedObjects = EditorLayout::GetInstance().GetSelectedObjects();

    if (selectedObjects.size() == 0) return;

    for (Object* obj : selectedObjects)
    {
        obj->DrawProperties();
    }
}
