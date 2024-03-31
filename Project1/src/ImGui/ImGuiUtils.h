#pragma once

#include <string>
#include <glm/glm.hpp>
#include <imgui_internal.h>
#include <imgui.h>


extern bool DrawTransformVector3ImGui(std::string label, glm::vec3& values, float resetValue, float& columnWidth);
extern bool DrawTransformVector2ImGui(std::string label, glm::vec2& values, float resetValue, float& columnWidth);
extern bool DrawDropDownImGui(std::string label, int& currentItem, const char* const* items, int size);
extern bool DrawDragFloatImGui(std::string label, float& value, float speed = 0.1f, float min = 0, float max = 0);
extern bool DrawFloatImGui(std::string label, float& value);
extern bool DrawBoolImGui(std::string label, bool& value);
extern bool DrawIntImGui(std::string label, int& value);