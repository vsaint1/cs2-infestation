/*
 *   Copyright (c) 2024 vsantos1
 *   All rights reserved.
 */
#include "../window_manager.h"
float a = 0.f;


void show_menu(GLFWwindow *window) {

  ImGuiIO &io = ImGui::GetIO();

  if (WindowManager::mouse_state(window, GLFW_MOUSE_BUTTON_LEFT)) {
    io.MouseDown[0] = true;
    io.MouseClicked[0] = true;
    io.MouseClickedPos[0].x = io.MousePos.x;
    io.MouseClickedPos[0].x = io.MousePos.y;
  } else
    io.MouseDown[0] = false;

  glfwSetWindowAttrib(window, GLFW_MOUSE_PASSTHROUGH, GLFW_FALSE);

  ImGui::SetNextWindowSize(ImVec2(500.0f, 350.0f), ImGuiCond_Once);
  ImGui::Begin(("Infestation - 0.5.0"), &settings::show_menu, ImGuiWindowFlags_::ImGuiWindowFlags_NoResize | ImGuiWindowFlags_::ImGuiWindowFlags_NoCollapse);

  ImGui::BeginTabBar(("##tabs"), ImGuiTabBarFlags_None);
  ImGui::SetCursorPos(ImVec2(ImGui::GetWindowSize().x / 2 - 100, 50));
  ImGui::Text("Hello world");
  if (ImGui::Button("Test"))
    SPDLOG_INFO("dwadwa");

  ImGui::SliderFloat("test", &a, 0, 100, "%.2fms");
  ImGui::EndTabBar();
  ImGui::End();
}
