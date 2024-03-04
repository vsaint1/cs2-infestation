/*
 *   Copyright (c) 2024 vsantos1
 *   All rights reserved.
 */

#ifndef WINDOW_MENU_MENU_HPP_
#define WINDOW_MENU_MENU_HPP_

#include "../../utils/ui/custom_components.h"
#include "../window_manager.h"

void show_menu(GLFWwindow *window) {
    ImGuiIO &io = ImGui::GetIO();

    if (WindowManager::mouse_state(window, GLFW_MOUSE_BUTTON_LEFT)) {
        io.MouseDown[0] = true;
        io.MouseClicked[0] = true;
        io.MouseClickedPos[0].x = io.MousePos.x;
        io.MouseClickedPos[0].y = io.MousePos.y;
    } else
        io.MouseDown[0] = false;

    glfwSetWindowAttrib(window, GLFW_MOUSE_PASSTHROUGH, GLFW_FALSE);

    component::create_style();
    ImGui::SetNextWindowSize(ImVec2(500.0f, 400.0f), ImGuiCond_Once);
    ImGui::Begin(("Infestation"), &settings::show_menu,
                 ImGuiWindowFlags_::ImGuiWindowFlags_NoResize | ImGuiWindowFlags_::ImGuiWindowFlags_NoCollapse);

    ImGui::BeginTabBar(("##tabs"), ImGuiTabBarFlags_None);
    ImGui::SetCursorPos(ImVec2(ImGui::GetWindowSize().x / 2 - 100, 50));

    ImGui::SetNextItemWidth(100);

    if (ImGui::BeginTabItem(("Aimbot"))) {
        ImGui::Text("Aimbot");
        ImGui::Checkbox("Enabled", &settings::aimbot::aimbot);
		ImGui::Checkbox("Visible Check", &settings::aimbot::visible_check);
		component::set_helper("Enable/Disable Visible Check");
		ImGui::SliderFloat("FOV", &settings::aimbot::fov, 0.f, 100.f, "%.0f");
		component::set_helper("Aimbot FOV");
		ImGui::Combo("Target", &settings::aimbot::selectedhitbox, settings::aimbot::hitbox, IM_ARRAYSIZE(settings::aimbot::hitbox));
		ImGui::SliderInt("Smooth", &settings::aimbot::smooth, 0, 10, "%d");
        ImGui::EndTabItem();
    }

    ImGui::SetNextItemWidth(100);

    if (ImGui::BeginTabItem(("ESP"))) {
        ImGui::Columns(2, NULL, false);
        ImGui::SetColumnOffset(1, 150);
        ImGui::Text("Player");
        ImGui::Checkbox("Enabled", &settings::visuals::player_esp);
        component::set_helper("Enable/Disable ESP");
        ImGui::Checkbox("Weapon", &settings::visuals::player_weapon);
        component::set_helper("Draw player current weapon");
        ImGui::Checkbox("Name", &settings::visuals::player_name);
        component::set_helper("Draw player name");
        ImGui::Checkbox("Health", &settings::visuals::player_health);
        component::set_helper("Draw player health");
        ImGui::Checkbox("SnapLines", &settings::visuals::player_snaplines);
        component::set_helper("Draw line to player");
        ImGui::Checkbox("Distance", &settings::visuals::player_distance);
        component::set_helper("Draw player distance");
        ImGui::Checkbox("Skeleton", &settings::visuals::player_skeleton);
        component::set_helper("Draw player skeleton");

        ImGui::NextColumn();

        ImGui::Text("World");
        ImGui::Checkbox("Enabled##1", &settings::world::esp);
        component::set_helper("Enable/Disable World ESP");
        ImGui::Spacing();
        ImGui::Checkbox("Chicken", &settings::world::chicken_esp);
        component::set_helper("Draw chickens meme");
        if (settings::world::esp) {

            ImGui::Checkbox("Weapons", &settings::world::weapon_esp);
            ImGui::SameLine();
            component::set_helper("Enable/Disable Weapons ESP");
            if (settings::world::weapon_esp) {
                ImGui::Checkbox("Weapon Icon", &settings::world::weapon_icon);
                component::set_helper("Draw weapon icon");
                ImGui::Checkbox("Weapon Name", &settings::world::weapon_name);
                component::set_helper("Draw weapon name");
                component::color_picker("##weapon_name", settings::colors::weapon_dropped);
                ImGui::Checkbox("Weapon Distance", &settings::world::weapon_distance);
                component::set_helper("Draw distance to weapon");
                component::color_picker("##weapon_distance", settings::colors::weapon_distance);
            }

            ImGui::Spacing();
            ImGui::Checkbox("Grenades", &settings::world::grenade_esp);
            component::set_helper("Enable/Disable Grenades ESP");

            if (settings::world::grenade_esp) {
                ImGui::Checkbox("Grenade Warning", &settings::world::grenade_warning);
                component::set_helper("Grenade projectile warning");
                ImGui::Checkbox("Grenade Name", &settings::world::grenade_name);
                component::set_helper("Grenade projectile name");
                ImGui::Checkbox("Grenade Distance", &settings::world::grenade_distance);
                component::set_helper("Grenade projectile distance");

                if (settings::misc::experimental_features) {

                    ImGui::Checkbox("Grenade Trajectory", &settings::world::grenade_trajectory);
                    component::set_helper("This is experimental feature", ImColor(211, 67, 18, 255), '!');
                    component::color_picker("##nade_trail", settings::colors::grenade_trails);

                    ImGui::Checkbox("Grenade Molotov", &settings::world::grenade_inferno_esp);
                    component::set_helper("Grenade molotov's on group", ImColor(211, 67, 18, 255), '!');
                }
            }
        }

        ImGui::EndTabItem();
    }

    ImGui::SetNextItemWidth(100);

    if (ImGui::BeginTabItem("Misc")) {

        ImGui::Checkbox("Performance Metrics", &settings::misc::performance);
        component::set_helper("Enable/Disable performance metrics");

        ImGui::Checkbox("Bomb-Timer", &settings::misc::bomb_timer);
        component::set_helper("Enable/Disable C4 timer");

        ImGui::Checkbox("Team-Check", &settings::misc::team_check);
        component::set_helper("Enable/Disable Team-Check");

        ImGui::Checkbox("Experimental", &settings::misc::experimental_features);
        component::set_helper(
                "This enables using features under development, may also experience bugs and possible crashes",
                ImColor(211, 67, 18, 255), '!');

        if (ImGui::Button("Github"))
            ShellExecuteA(NULL, "open", "https://github.com/vsaint1/cs2-infestation", NULL, NULL, SW_SHOWNORMAL);

        ImGui::EndTabItem();
    }

    ImGui::EndTabBar();
    ImGui::End();
}

#endif // WINDOW_MENU_MENU_HPP_
