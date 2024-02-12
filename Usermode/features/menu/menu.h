#pragma once
#include "../../utils/helper.h"





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
	ImGui::Begin(("Infestation - 5.5"), &settings::bMenu, ImGuiWindowFlags_::ImGuiWindowFlags_NoResize | ImGuiWindowFlags_::ImGuiWindowFlags_NoCollapse);

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
		set_helper("Draw enemies skeleton, bones are with update issue",ImColor(211, 67, 18, 255),'!');
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
				ImGui::Checkbox("Weapon Icon", &settings::world::weapon_name);
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
				ImGui::Checkbox("Grenade Trajectory", &settings::world::grenade_trajectory);
				set_helper("This feature is under development, need to fix bounces, velocity and trajectory calculations",ImColor(211, 67, 18, 255),'!');

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
		ImGui::Checkbox("Anti-Screencapture", &settings::misc::bWatermark);
		set_helper("Hides your ESP from being captured by OBS only");

		ImGui::SliderInt("##save_fps",&settings::misc::sleep_for_ms, 0, 1000,"%dms");
		set_helper("Using higher number will update slowly but reduces [CPU/Memory] usage", ImColor(211, 67, 18, 255), '!');

		if (ImGui::Button("Github"))
			ShellExecuteA(NULL, "open", "https://github.com/vsaint1/cs2-infestation", NULL, NULL, SW_SHOWNORMAL);

		
		ImGui::EndTabItem();

	}

	ImGui::EndTabBar();
	ImGui::End();

}