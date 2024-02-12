#include "custom_components.h"

void component::color_picker(ImColor& original_color) {

	ImGui::SameLine();
	ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 5);
	ImVec4 color = ImVec4(original_color.Value.x, original_color.Value.y, original_color.Value.z, original_color.Value.w);
	ImGui::ColorButton("##color_btn", ImVec4(original_color.Value.x, original_color.Value.y, original_color.Value.z, original_color.Value.w), ImGuiColorEditFlags_NoTooltip, ImVec2(15, 10));

	if (ImGui::IsItemClicked())
		ImGui::OpenPopup("##color_picker");


	if (ImGui::BeginPopup("##color_picker")) {
		if (ImGui::ColorPicker4("##picker", &color.x, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_AlphaBar))
			original_color = ImColor(color.x, color.y, color.z, color.w);

		ImGui::EndPopup();
	}

}


void component::set_helper(const char* text,ImColor color,char symbol) {

	std::string str = "( ? )";

	std::replace(str.begin(), str.end(), '?', symbol);
	ImGui::SameLine();
	ImGui::TextColored(color, str.c_str());
	if (ImGui::IsItemHovered())
		ImGui::SetTooltip(text);
}


void component::create_style() {
	ImGuiStyle* style = &ImGui::GetStyle();

	style->WindowRounding = 5.3f;
	style->FrameRounding = 2.3f;
	style->ScrollbarRounding = 5.f;
	style->WindowTitleAlign = ImVec2(0.5f, 0.5f);
	style->GrabMinSize = 20.0f;

	style->Colors[ImGuiCol_Text] = ImVec4(0.80f, 0.80f, 0.83f, 1.00f);
	style->Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.30f, 0.09f, 0.12f, 1.00f);
	style->Colors[ImGuiCol_TitleBgActive] = ImVec4(1.0f, 0.23f, 0.29f, 1.00f);
	style->Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(1.0f, 0.23f, 0.29f, 1.00f);
	style->Colors[ImGuiCol_TextDisabled] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
	style->Colors[ImGuiCol_WindowBg] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	style->Colors[ImGuiCol_ChildBg] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
	style->Colors[ImGuiCol_PopupBg] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
	style->Colors[ImGuiCol_Border] = ImVec4(0.80f, 0.80f, 0.83f, 0.88f);
	style->Colors[ImGuiCol_BorderShadow] = ImVec4(0.92f, 0.91f, 0.88f, 0.00f);
	style->Colors[ImGuiCol_FrameBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style->Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.92f, 0.18f, 0.29f, 0.78f);
	style->Colors[ImGuiCol_FrameBgActive] = ImVec4(0.80f, 0.56f, 0.58f, 1.00f);
	style->Colors[ImGuiCol_TitleBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style->Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(1.00f, 0.98f, 0.95f, 0.75f);
	style->Colors[ImGuiCol_TitleBgActive] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
	style->Colors[ImGuiCol_MenuBarBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style->Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style->Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
	style->Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style->Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	style->Colors[ImGuiCol_Tab] = ImLerp(style->Colors[ImGuiCol_Header], style->Colors[ImGuiCol_TitleBgActive], 1.00f);
	style->Colors[ImGuiCol_TabHovered] = ImLerp(style->Colors[ImGuiCol_TabActive], style->Colors[ImGuiCol_TabActive], 0.50f);
	style->Colors[ImGuiCol_TabActive] = ImVec4(0.30f, 0.09f, 0.12f, 1.00f);
	style->Colors[ImGuiCol_TabUnfocused] = ImLerp(style->Colors[ImGuiCol_Tab], style->Colors[ImGuiCol_TitleBg], 0.80f);
	style->Colors[ImGuiCol_TabUnfocusedActive] = ImLerp(style->Colors[ImGuiCol_TabActive], style->Colors[ImGuiCol_TitleBg], 0.40f);
	style->Colors[ImGuiCol_CheckMark] = ImVec4(0.30f, 0.09f, 0.12f, 1.00f);
	style->Colors[ImGuiCol_SliderGrab] = ImVec4(0.30f, 0.09f, 0.12f, 1.00f);
	style->Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.25f, 0.09f, 0.12f, 1.00f);
	style->Colors[ImGuiCol_Button] = ImVec4(0.30f, 0.09f, 0.12f, 1.00f);
	style->Colors[ImGuiCol_ButtonHovered] = ImVec4(0.25f, 0.09f, 0.12f, 1.00f);
	style->Colors[ImGuiCol_ButtonActive] = ImVec4(0.20f, 0.09f, 0.12f, 1.00f);
	style->Colors[ImGuiCol_Header] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style->Colors[ImGuiCol_HeaderHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style->Colors[ImGuiCol_HeaderActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	style->Colors[ImGuiCol_ResizeGrip] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	style->Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style->Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	style->Colors[ImGuiCol_PlotLines] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
	style->Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
	style->Colors[ImGuiCol_PlotHistogram] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
	style->Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);

	style->Colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.20f, 0.22f, 0.27f, 0.73f);
}
