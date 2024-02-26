//
// Created by vsantos1 on 2/16/2024.
//
#include "features/esp/esp.hpp"
#include "features/misc/bomb.hpp"
#include "sdk/entity_list.hpp"
#include "window/menu/menu.hpp"

int main(int, char **) {

  memory.attach();

  // refactor this
  SPDLOG_INFO("PID {} \n", memory.get_pid());
  g_entity_list = memory.find_pattern("client.dll", "48 8B 0D ? ? ? ? 48 89 7C 24 ? 8B FA C1 EB")->rip().as<EntityList *>();

  auto local_pawn = memory.find_pattern("client.dll", "48 8D 05 ? ? ? ? C3 CC CC CC CC CC CC CC CC 48 83 EC ? 8B 0D")->rip().add(0x138);
  SPDLOG_INFO("LOCAL_PLAYER: {:#04x}", local_pawn.get_address());
  auto [address, size] = memory.get_module_info("client.dll");
  client = address.value();
  local_player = memory.readv<uintptr_t>(local_pawn.get_address());
  SPDLOG_INFO("MODULE_BASE: {}", address.value());

  static WindowManager manager;

  if (!manager.create("infestation")) {
    manager.cleanup();
    MessageBox(0, "Failed while trying to initialize modules", "Error", MB_ICONERROR);
  }

  while (!manager.should_close()) {

    if (WindowManager::key_state(manager.m_window, GLFW_KEY_END) & 1)
      exit(0);

    local_viewmatrix = memory.readv<ViewMatrix>(client + offsets::dwViewMatrix);

    manager.pool_events();

    manager.begin_frame();

    if (WindowManager::key_state(manager.m_window, GLFW_KEY_INSERT) & 1)
      settings::show_menu = !settings::show_menu;

    if (settings::show_menu)
      show_menu(manager.m_window);
    else
      glfwSetWindowAttrib(manager.m_window, GLFW_MOUSE_PASSTHROUGH, GLFW_TRUE);

    misc::bomb_timer();

    esp::weapon();

    ImGui::GetBackgroundDrawList()->AddCircle(ImVec2(width / 2, height / 2 - 25), 60, ImColor(255, 255, 255, 255), 100);

    manager.render();
  }

  manager.cleanup();
  return 0;
}