
#include "ImGuiUtils.h"

bool DrawTransformVector3ImGui(std::string label, glm::vec3& values, float resetValue, float& columnWidth)
{
	bool initiated = false;

	ImGui::PushID(label.c_str());

	ImGui::Columns(2);
	ImGui::SetColumnWidth(0, columnWidth);
	ImGui::Text(label.c_str());
	ImGui::NextColumn();

	ImGui::PushMultiItemsWidths(3, ImGui::CalcItemWidth());
	ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));

	ImGuiStyle& style = ImGui::GetStyle();

	float lineHeight = ImGui::GetFontSize() + style.FramePadding.y * 2;
	ImVec2 buttonSize = { lineHeight + 3.0f, lineHeight };

	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.8f, 0.1f, 0.15f, 1.0f));
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.9f, 0.2f, 0.2f, 1.0f));
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.8f, 0.1f, 0.15f, 1.0f));

	if (ImGui::Button("X", buttonSize))
	{
		values.x = resetValue;
		initiated = true;
	}

	ImGui::PopStyleColor(3);

	ImGui::SameLine();
	if(ImGui::DragFloat("##X", &values.x, 0.1f, 0, 0, "%0.2f")) { initiated = true; }
	ImGui::PopItemWidth();
	ImGui::SameLine();


	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.2f, 0.7f, 0.3f, 1.0f));
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.3f, 0.8f, 0.3f, 1.0f));
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.2f, 0.7f, 0.2f, 1.0f));
	if (ImGui::Button("Y", buttonSize))
	{
		values.y = resetValue;
		initiated = true;
	}
	ImGui::PopStyleColor(3);


	ImGui::SameLine();
	if (ImGui::DragFloat("##Y", &values.y, 0.1f, 0, 0, "%0.2f")) { initiated = true; }
	ImGui::PopItemWidth();
	ImGui::SameLine();

	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.1f, 0.25f, 0.8f, 1.0f));
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.2f, 0.35f, 0.9f, 1.0f));
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.1f, 0.25f, 0.8f, 1.0f));
	if (ImGui::Button("Z", buttonSize))
	{
		values.z = resetValue;
		initiated = true;
	}
	ImGui::PopStyleColor(3);

	ImGui::SameLine();
	if(ImGui::DragFloat("##Z", &values.z, 0.1f, 0, 0, "%0.2f")) { initiated = true; }
	ImGui::PopItemWidth();

	ImGui::PopStyleVar();

	ImGui::Columns(1);

	ImGui::PopID();

	return initiated;
}

bool DrawTransformVector2ImGui(std::string label, glm::vec2& values, float resetValue, float& columnWidth)
{
	bool initiated = false;

	ImGui::PushID(label.c_str());

	ImGui::Columns(2);
	ImGui::SetColumnWidth(0, columnWidth);
	ImGui::Text(label.c_str());
	ImGui::NextColumn();

	ImGui::PushMultiItemsWidths(3, ImGui::CalcItemWidth());
	ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));

	ImGuiStyle& style = ImGui::GetStyle();

	float lineHeight = ImGui::GetFontSize() + style.FramePadding.y * 2;
	ImVec2 buttonSize = { lineHeight + 3.0f, lineHeight };

	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.8f, 0.1f, 0.15f, 1.0f));
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.9f, 0.2f, 0.2f, 1.0f));
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.8f, 0.1f, 0.15f, 1.0f));

	if (ImGui::Button("X", buttonSize))
	{
		values.x = resetValue;
		initiated = true;
	}

	ImGui::PopStyleColor(3);

	ImGui::SameLine();
	if (ImGui::DragFloat("##X", &values.x, 0.1f, 0, 0, "%0.2f")) { initiated = true; }
	ImGui::PopItemWidth();
	ImGui::SameLine();


	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.2f, 0.7f, 0.3f, 1.0f));
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.3f, 0.8f, 0.3f, 1.0f));
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.2f, 0.7f, 0.2f, 1.0f));
	if (ImGui::Button("Y", buttonSize))
	{
		values.y = resetValue;
		initiated = true;
	}
	ImGui::PopStyleColor(3);


	ImGui::SameLine();
	if (ImGui::DragFloat("##Y", &values.y, 0.1f, 0, 0, "%0.2f")) { initiated = true; }
	ImGui::PopItemWidth();

	ImGui::Columns(1);
	ImGui::PopStyleVar();
	ImGui::PopID();

	return initiated;
}

bool DrawDropDownImGui(std::string label, int& currentItem, const char* const* items, int size, float columnWidth)
{
	bool initiated = false;

	ImGui::PushID(label.c_str());

	ImGui::Columns(2);
	ImGui::SetColumnWidth(0, columnWidth);
	ImGui::Text(label.c_str());
	ImGui::NextColumn();

	if (ImGui::Combo(("###" + label).c_str(), &currentItem, items, size))
	{
		initiated = true;
	}

	ImGui::Columns(1);
	ImGui::PopID();

	
	return initiated;

}

bool DrawDragFloatImGui(std::string label, float& value, float speed, float min, float max, float columnWidth)
{
	bool initiated = false;

	ImGui::PushID(label.c_str());

	ImGui::Columns(2);
	ImGui::SetColumnWidth(0, columnWidth);
	ImGui::Text(label.c_str());
	ImGui::NextColumn();

	if (ImGui::DragFloat(("###" + label).c_str(), &value, speed, min, max, "%.2f"))
	{
		initiated = true;
	}

	ImGui::Columns(1);

	ImGui::PopID();

	return initiated;
}

bool DrawFloatImGui(std::string label, float& value, float columnWidth)
{
	bool isUpdated = false;

	ImGui::PushID(label.c_str());

	ImGui::Columns(2);
	ImGui::SetColumnWidth(0, columnWidth);
	ImGui::Text(label.c_str());
	ImGui::NextColumn();

	if (ImGui::InputFloat(("###" + label).c_str(), &value, 0, 0, "%.2f"))
	{
		isUpdated = true;
	}

	ImGui::Columns(1);

	ImGui::PopID();

	return isUpdated;
}

bool DrawBoolImGui(std::string label, bool& value, float columnWidth)
{
	bool isUpdated = false;
	ImGui::PushID(label.c_str());

	ImGui::Columns(2);
	ImGui::SetColumnWidth(0, columnWidth);
	ImGui::Text(label.c_str());
	ImGui::NextColumn();

	if (ImGui::Checkbox(("###" + label).c_str(), &value))
	{
		isUpdated = true;
	}

	ImGui::Columns(1);

	ImGui::PopID();

	return isUpdated;
}

bool DrawIntImGui(std::string label, int& value, float columnWidth)
{
	bool initiated = false;

	ImGui::PushID(label.c_str());

	ImGui::Columns(2);
	ImGui::SetColumnWidth(0, columnWidth);
	ImGui::Text(label.c_str());
	ImGui::NextColumn();

	if (ImGui::InputInt(("###" + label).c_str(), &value, 0, 0))
	{
		initiated = true;
	}

	ImGui::Columns(1);

	ImGui::PopID();

	return initiated;
}
