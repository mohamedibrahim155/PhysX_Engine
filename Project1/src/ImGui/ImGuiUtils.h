#pragma once

#include <string>
#include <glm/glm.hpp>
#include <imgui_internal.h>
#include <imgui.h>


extern void DrawTransformVector3ImGui(std::string label, glm::vec3& values, float resetValue, float& columnWidth);
extern bool DrawTransformVector2ImGui(std::string label, glm::vec2& values, float resetValue, float& columnWidth);
extern bool DrawDropDownImGui(std::string label, int& currentItem, const char* const* items, int size);
extern bool DrawDragFloatImGui(std::string label, float& value, float speed, float min, float max);
extern void DrawFloatImGui(std::string label, float& value);
extern void DrawBoolImGui(std::string label, bool& value);
extern bool DrawIntImGui(std::string label, int& value);