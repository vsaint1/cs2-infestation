/*
 *   Copyright (c) 2024 vsantos1
 *   All rights reserved.
 */
#ifndef WINDOW_WINDOW_MANAGER_H_
#define WINDOW_WINDOW_MANAGER_H_
#include "../utils/macros.h"
#include "fonts/tahoma_font.h"
#include "fonts/weapon_font.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include "imgui/imgui_internal.h"
#include <GLFW/glfw3.h>

class WindowManager {

public:
  int m_width, m_height;

  GLFWwindow *m_window;

  bool create(const char* window_name);

  bool should_close();

  void pool_events();

  void render();

  void begin_frame();

  void cleanup();

  static bool mouse_state(GLFWwindow * window,int key);

  static bool key_state(GLFWwindow* window,int key);
};

#endif // WINDOW_WINDOW_MANAGER_H_