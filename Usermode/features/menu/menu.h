#pragma once



void create_style() {
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
void set_helper(const char* text) {

	ImGui::SameLine();
	ImGui::TextColored(ImColor(105, 105, 105), "(?)");
	if (ImGui::IsItemHovered())
		ImGui::SetTooltip(text);
}



void change_key(void* blank) {
	keystatus = 1;
	while (true) {
		for (int i = 0; i < 0x87; i++) {
			if (GetKeyState(i) & 0x8000) {
				hotkeys::aimkey = i;
				keystatus = 0;
				return;
			}
		}
	}
}


static bool key_array(void* data, int idx, const char** out_text) {
	const char* const* items = (const char* const*)data;
	if (out_text)
		*out_text = items[idx];
	return true;
}

void hotkey_button(int aimkey, void* changekey, int status) {
	const char* preview_value = NULL;
	if (aimkey >= 0 && aimkey < IM_ARRAYSIZE(key_names))
		key_array(key_names, aimkey, &preview_value);

	std::string aimkeys;

	if (preview_value == NULL)
		aimkeys = "Select any Key";
	else
		aimkeys = preview_value;

	if (status == 1)
		aimkeys = "Press the Key";

	if (ImGui::Button(aimkeys.c_str(), ImVec2(125, 20))) {
		if (status == 0)
			CreateThread(0, 0, (LPTHREAD_START_ROUTINE)changekey, nullptr, 0, nullptr);
	}

}

void draw_menu() {
	if (GetAsyncKeyState(VK_HOME) & 1)
		settings::bMenu = !settings::bMenu;


	if (!settings::bMenu)
		return;

	create_style();



	ImGui::SetNextWindowSize(ImVec2(500.0f, 350.0f), ImGuiCond_Once);
	ImGui::Begin(("Infestation - 4.5"), &settings::bMenu, ImGuiWindowFlags_::ImGuiWindowFlags_NoResize | ImGuiWindowFlags_::ImGuiWindowFlags_NoCollapse);

	ImGui::BeginTabBar(("##tabs"), ImGuiTabBarFlags_None);
	ImGui::SetCursorPos(ImVec2(ImGui::GetWindowSize().x / 2 - 100, 50));


	ImGui::SetNextItemwidth(100);

	if (ImGui::BeginTabItem(("Aimbot"))) {
		ImGui::Text("Aimbot");
		ImGui::Checkbox("Enabled", &settings::aimbot::aimbot);
		set_helper("Enable/Disable Aimbot");
		ImGui::Checkbox("Visible Check", &settings::aimbot::visible_check);
		set_helper("Enable/Disable Visible Check");
		ImGui::SliderFloat("FOV", &settings::aimbot::aim_fov, 0.f, 100.f, "%.0f");
		set_helper("Aimbot FOV");
		ImGui::Combo("Target", &settings::aimbot::selectedhitbox, settings::aimbot::hitbox, IM_ARRAYSIZE(settings::aimbot::hitbox));
		ImGui::SliderInt("Smooth", &settings::aimbot::smooth, 0, 10, "%d");
		set_helper("Aimbot Smooth");
		hotkey_button(hotkeys::aimkey, change_key, keystatus);

		ImGui::EndTabItem();
	}

	ImGui::SetNextItemwidth(100);



	if (ImGui::BeginTabItem(("ESP"))) {
		ImGui::Columns(2, NULL, false);
		ImGui::SetColumnOffset(1, 150);
		ImGui::Text("Player");
		ImGui::Checkbox("Enabled", &settings::visuals::esp);
		set_helper("Enable/Disable ESP");
		ImGui::Checkbox("Box", &settings::visuals::bBox);
		set_helper("Draw enemies 2D box");
		ImGui::Checkbox("Name", &settings::visuals::bName);
		set_helper("Draw enemies name");
		ImGui::Checkbox("Skeleton", &settings::visuals::bSkeleton);
		set_helper("Draw enemies skeleton");
		ImGui::Checkbox("Health", &settings::visuals::bHealth);
		set_helper("Draw enemies health");
		ImGui::Checkbox("Snap Lines", &settings::visuals::bSnaplines);
		set_helper("Draw lines to enemies");
		ImGui::Checkbox("Distance", &settings::visuals::distance);
		set_helper("Draw distance to enemies");
		ImGui::Checkbox("Weapon", &settings::visuals::bWeapon);
		set_helper("Draw enemies current weapon");

		ImGui::NextColumn();

		ImGui::Checkbox("World", &settings::world::esp);
		set_helper("Enable/Disable World ESP");
		ImGui::Spacing();

		if (settings::world::esp) {

			ImGui::Checkbox("Weapons", &settings::world::weapon_esp);
			ImGui::SameLine();
			set_helper("Enable/Disable Weapons ESP");
			if (settings::world::weapon_esp) {
				ImGui::Checkbox("Weapon Name", &settings::world::weapon_name);
				set_helper("Draw weapon name");
				ImGui::Checkbox("Weapon Distance", &settings::world::weapon_distance);
				set_helper("Draw distance to weapon");
				ImGui::Checkbox("Weapon Snap Lines", &settings::world::weapon_snaplines);
				set_helper("Draw lines to weapon");

			}

			ImGui::Spacing();
			ImGui::Checkbox("Grenades", &settings::world::grenade_esp);
			set_helper("Enable/Disable Grenades ESP");

			if (settings::world::grenade_esp) {
				ImGui::Checkbox("Grenade Name", &settings::world::grenade_name);
				set_helper("Grenade projectile name");
				ImGui::Checkbox("Grenade Distance", &settings::world::grenade_distance);
				set_helper("Grenade projectile distance");
				ImGui::Checkbox("Grenade Snap Lines", &settings::world::grenade_snaplines);
				set_helper("Draw lines to Grenade projectile");
				ImGui::Checkbox("Grenade Timer", &settings::world::grenade_timer);
				set_helper("Draw Grenade timer");
				ImGui::Checkbox("Grenade Trajectory - DEV", &settings::world::grenade_trajectory);
				set_helper("This feature is under development, need to fix bounces, velocity and trajectory calculations");

			}
		}

		ImGui::EndTabItem();

	}

	ImGui::SetNextItemwidth(100);

	if (ImGui::BeginTabItem("Misc")) {
		ImGui::Checkbox("Team-Check", &settings::misc::bTeamcheck);
		set_helper("Enable/Disable Team-Check");
		ImGui::Checkbox("Watermark", &settings::misc::bWatermark);
		set_helper("Enable/Disable Watermark");

		if (ImGui::Button("Github"))
			ShellExecuteA(NULL, "open", "https://github.com/vsaint1/cs2-infestation", NULL, NULL, SW_SHOWNORMAL);

		ImGui::EndTabItem();

	}

	ImGui::EndTabBar();
	ImGui::End();

}