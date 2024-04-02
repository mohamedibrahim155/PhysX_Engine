#pragma once

#include <string>
#include <glm/glm.hpp>
#include <imgui_internal.h>
#include <imgui.h>


extern bool DrawTransformVector3ImGui(std::string label, glm::vec3& values, float resetValue, float& columnWidth);
extern bool DrawTransformVector2ImGui(std::string label, glm::vec2& values, float resetValue, float& columnWidth);
extern bool DrawDropDownImGui(std::string label, int& currentItem, const char* const* items, int size, float columnWidth);
extern bool DrawDragFloatImGui(std::string label, float& value, float speed = 0.1f, float min = 0, float max = 0 , float columnWidth = 150.0f);
extern bool DrawFloatImGui(std::string label, float& value, float columnWidth = 150.0f);
extern bool DrawBoolImGui(std::string label, bool& value , float columnWidth = 150.0f);
extern bool DrawIntImGui(std::string label, int& value, float columnWidth = 150.0f);