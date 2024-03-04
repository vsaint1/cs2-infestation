// Created by vsantos1 on 2/16/2024.
//
#include "features/aimbot/aimbot.h"
#include "features/esp/esp.hpp"
#include "features/misc/bomb.hpp"

#include "sdk/entity_list.hpp"
#include "window/menu/menu.hpp"

int main(int, char **) {

#if NDEBUG && WIN32
  ShowWindow(GetConsoleWindow(), SW_HIDE);
#else
  // TODO: add to others platforms
#endif

  memory.attach();
  g_entity_list = memory.find_pattern(CLIENT_MODULE_NAME, "48 8B 0D ? ? ? ? 48 89 7C 24 ? 8B FA C1 EB")->rip().as<EntityList *>();
  g_global_vars = memory.find_pattern(CLIENT_MODULE_NAME, "48 89 0D ? ? ? ? 48 89 41")->rip().get_address();
  auto sig_vm = memory.find_pattern(CLIENT_MODULE_NAME, "48 8D 0D ? ? ? ? 48 C1 E0 06")->rip();
  auto local_pawn = memory.find_pattern(CLIENT_MODULE_NAME, "48 8D 05 ? ? ? ? C3 CC CC CC CC CC CC CC CC 48 83 EC ? 8B 0D")->rip().add(0x138);
  auto sig_bomb = memory.find_pattern(CLIENT_MODULE_NAME, "48 8B 15 ? ? ? ? FF C0 48 8D 4C 24 40")->rip();

  auto [address, size] = memory.get_module_info(CLIENT_MODULE_NAME);
  client = address.value();
  c4_planted = sig_bomb.get_address();

  static WindowManager manager;

  if (!manager.create("infestation")) {
    manager.cleanup();
    MessageBox(0, "Failed while trying to initialize modules", "Error", MB_ICONERROR);
  }

  while (!manager.should_close()) {

    const auto entity_list = EntityList::get();

    if (!entity_list)
      continue;

    entity_list->update();

    local_player = memory.readv<uintptr_t>(local_pawn.get_address());

    if (WindowManager::key_state(manager.m_window, GLFW_KEY_END) & 1)
      exit(0);

    local_viewmatrix = memory.readv<ViewMatrix>(sig_vm.get_address());

    manager.pool_events();

    manager.begin_frame();

    if (GetAsyncKeyState(VK_INSERT) & 1)
      settings::show_menu = !settings::show_menu;

    if (settings::show_menu)
      show_menu(manager.m_window);
    else
      glfwSetWindowAttrib(manager.m_window, GLFW_MOUSE_PASSTHROUGH, GLFW_TRUE);

    misc::bomb_timer();

    esp::render();

    if (settings::misc::performance)
      manager.performance_metrics();

    manager.render();
  }

  manager.cleanup();
  return 0;
}
