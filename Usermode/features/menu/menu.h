#pragma once
#include "../../utils/ui/custom_components.h"




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

	component::create_style();



	ImGui::SetNextWindowSize(ImVec2(500.0f, 350.0f), ImGuiCond_Once);
	ImGui::Begin(("Infestation - 6.5"), &settings::bMenu, ImGuiWindowFlags_::ImGuiWindowFlags_NoResize | ImGuiWindowFlags_::ImGuiWindowFlags_NoCollapse);

	ImGui::BeginTabBar(("##tabs"), ImGuiTabBarFlags_None);
	ImGui::SetCursorPos(ImVec2(ImGui::GetWindowSize().x / 2 - 100, 50));


	ImGui::SetNextItemwidth(100);

	if (ImGui::BeginTabItem(("Aimbot"))) {
		ImGui::Text("Aimbot");
		ImGui::Checkbox("Enabled", &settings::aimbot::aimbot);
		component::set_helper("Enable/Disable Aimbot");
		ImGui::Checkbox("Visible Check", &settings::aimbot::visible_check);
		component::set_helper("Enable/Disable Visible Check");
		ImGui::SliderFloat("FOV", &settings::aimbot::aim_fov, 0.f, 100.f, "%.0f");
		component::set_helper("Aimbot FOV");
		ImGui::Combo("Target", &settings::aimbot::selectedhitbox, settings::aimbot::hitbox, IM_ARRAYSIZE(settings::aimbot::hitbox));
		ImGui::SliderInt("Smooth", &settings::aimbot::smooth, 0, 10, "%d");
		component::set_helper("Aimbot Smooth");
		hotkey_button(hotkeys::aimkey, change_key, keystatus);

		ImGui::EndTabItem();
	}

	ImGui::SetNextItemwidth(100);



	if (ImGui::BeginTabItem(("ESP"))) {
		ImGui::Columns(2, NULL, false);
		ImGui::SetColumnOffset(1, 150);
		ImGui::Text("Player");
		ImGui::Checkbox("Enabled", &settings::visuals::esp);
		component::set_helper("Enable/Disable ESP");

		ImGui::Checkbox("Box", &settings::visuals::bBox);
		component::set_helper("Draw enemies 2D box");
		component::color_picker("##box", settings::colors::player_box);

		ImGui::Checkbox("Name", &settings::visuals::bName);
		component::set_helper("Draw enemies name");
		component::color_picker("##name", settings::colors::player_name);

		ImGui::Checkbox("Skeleton", &settings::visuals::bSkeleton);
		component::set_helper("Draw enemies skeleton");
		component::color_picker("##visible", settings::colors::skeleton_visible_color);
		component::color_picker("#hidden", settings::colors::skeleton_hidden_color);

		ImGui::Checkbox("Health", &settings::visuals::bHealth);
		component::set_helper("Draw enemies health");

		ImGui::Checkbox("Snap Lines", &settings::visuals::bSnaplines);
		component::set_helper("Draw lines to enemies");
		component::color_picker("##snap_lines", settings::colors::player_snaplines);

		ImGui::Checkbox("Distance", &settings::visuals::distance);
		component::set_helper("Draw distance to enemies");
		component::color_picker("##distance", settings::colors::player_distance);

		ImGui::Checkbox("Weapon", &settings::visuals::bWeapon);
		component::set_helper("Draw enemies current weapon");
		component::color_picker("##weapon", settings::colors::player_weapon);

		ImGui::NextColumn();

		ImGui::Checkbox("World", &settings::world::esp);
		component::set_helper("Enable/Disable World ESP");
		ImGui::Spacing();

		if (settings::world::esp) {

			ImGui::Checkbox("Weapons", &settings::world::weapon_esp);
			ImGui::SameLine();
			component::set_helper("Enable/Disable Weapons ESP");
			if (settings::world::weapon_esp) {
				ImGui::Checkbox("Weapon Icon", &settings::world::weapon_name);
				component::set_helper("Draw weapon name");
				ImGui::Checkbox("Weapon Distance", &settings::world::weapon_distance);
				component::set_helper("Draw distance to weapon");
				ImGui::Checkbox("Weapon Snap Lines", &settings::world::weapon_snaplines);
				component::set_helper("Draw lines to weapon");

			}

			ImGui::Spacing();
			ImGui::Checkbox("Grenades", &settings::world::grenade_esp);
			component::set_helper("Enable/Disable Grenades ESP");

			if (settings::world::grenade_esp) {
				ImGui::Checkbox("Grenade Name", &settings::world::grenade_name);
				component::set_helper("Grenade projectile name");
				ImGui::Checkbox("Grenade Distance", &settings::world::grenade_distance);
				component::set_helper("Grenade projectile distance");
				ImGui::Checkbox("Grenade Snap Lines", &settings::world::grenade_snaplines);
				component::set_helper("Draw lines to Grenade projectile");

				if (settings::misc::bExperimentalFeatures) {

					ImGui::Checkbox("Grenade Timer", &settings::world::grenade_timer);
					component::set_helper("This is experimental feature", ImColor(211, 67, 18, 255), '!');

					ImGui::Checkbox("Grenade Trajectory", &settings::world::grenade_trajectory);
					component::set_helper("This is experimental feature", ImColor(211, 67, 18, 255), '!');
					component::color_picker("##nade_trail", settings::colors::grenade_trail_color);

				}



			}
		}

		ImGui::EndTabItem();

	}

	ImGui::SetNextItemwidth(100);

	if (ImGui::BeginTabItem("Misc")) {
		ImGui::Checkbox("Team-Check", &settings::misc::bTeamcheck);
		component::set_helper("Enable/Disable Team-Check");
		ImGui::Checkbox("Watermark", &settings::misc::bWatermark);
		component::set_helper("Enable/Disable Watermark");
		ImGui::Checkbox("Anti-Screencapture", &settings::misc::bAntiScreencapture);
		component::set_helper("Hides your ESP from being captured by OBS only");
		ImGui::Checkbox("Experimental", &settings::misc::bExperimentalFeatures);
		component::set_helper("This enables using features under development, may also experience bugs and possible crashes", ImColor(211, 67, 18, 255), '!');
		ImGui::SliderInt("##save_fps", &settings::misc::sleep_for_ms, 0, 1000, "%dms");
		component::set_helper("Using higher number will update slowly but reduces [CPU/Memory] usage", ImColor(211, 67, 18, 255), '!');

		if (ImGui::Button("Github"))
			ShellExecuteA(NULL, "open", "https://github.com/vsaint1/cs2-infestation", NULL, NULL, SW_SHOWNORMAL);


		ImGui::EndTabItem();
	}

	ImGui::EndTabBar();
	ImGui::End();

}