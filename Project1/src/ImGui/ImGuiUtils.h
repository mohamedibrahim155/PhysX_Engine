#pragma once

#include <string>
#include <glm/glm.hpp>
#include <imgui_internal.h>
#include <imgui.h>


extern void DrawTransformVector3ImGui(std::string label, glm::vec3& values, float resetValue, float& columnWidth);