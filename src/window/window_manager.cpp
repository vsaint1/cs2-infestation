/*
 *   Copyright (c) 2024 vsantos1
 *   All rights reserved.
 */
#include "window_manager.h"

bool WindowManager::create(const char *window_name) {

  if (!glfwInit())
    return false;

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
  glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, 1);
  glfwWindowHint(GLFW_FLOATING, 1);
  glfwWindowHint(GLFW_MAXIMIZED, 1);
  glfwWindowHint(GLFW_RESIZABLE, false);

  GLFWmonitor *monitor = glfwGetPrimaryMonitor();

  const auto mode = glfwGetVideoMode(monitor);

  GLFWwindow *window = glfwCreateWindow(mode->width, mode->height, window_name, nullptr, nullptr);
  glfwSetWindowAttrib(window, GLFW_DECORATED, false);

  if (window == nullptr)
    return false;

  this->m_window = window;

  glfwMakeContextCurrent(window);
  glfwSwapInterval(GLFW_TRUE);

  IMGUI_CHECKVERSION();

  ImGui::CreateContext();
  ImGuiIO &io = ImGui::GetIO();
  (void)io;
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
  ImGui::StyleColorsClassic();
  io.Fonts->AddFontFromMemoryTTF(&tahoma_font, sizeof(tahoma_font), 13.0f, NULL, io.Fonts->GetGlyphRangesDefault());
	io.Fonts->AddFontFromMemoryTTF(&weapon_font_icon, sizeof(weapon_font_icon), 17.0f, NULL, io.Fonts->GetGlyphRangesDefault());
  
  ImGui_ImplGlfw_InitForOpenGL(window, false);

  ImGui_ImplOpenGL3_Init(GLSL_VERSION);

  return true;
}

bool WindowManager::should_close() { return glfwWindowShouldClose(this->m_window); }

void WindowManager::pool_events() {
  glfwWindowHint(GLFW_MOUSE_PASSTHROUGH, 1);

  glfwPollEvents();
}

void WindowManager::render() {
  ImGui::Render();
  int display_w, display_h;

  glfwGetFramebufferSize(this->m_window, &display_w, &display_h);

  glViewport(0, 0, display_w, display_h);
  glClear(GL_COLOR_BUFFER_BIT);
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

  glfwSwapBuffers(this->m_window);
}

void WindowManager::begin_frame() {
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();
}

void WindowManager::cleanup() {
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();

  glfwDestroyWindow(this->m_window);
  glfwTerminate();
}

bool WindowManager::mouse_state(GLFWwindow *window, int key) { return glfwGetMouseButton(window, key) == GLFW_PRESS; }

bool WindowManager::key_state(GLFWwindow *window, int key) {

  return glfwGetKey(window, key);
}
