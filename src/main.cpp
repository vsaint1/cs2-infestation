//
// Created by vsantos1 on 2/16/2024.
//
#define SDL_MAIN_HANDLED
#include "features/misc/bomb.hpp"
#include "sdk/entity_list.hpp"

int main() {
  memory.attach();

  SPDLOG_INFO("PID {} \n", memory.get_pid());
  entity_list = memory.find_pattern("client.dll", "48 8B 0D ? ? ? ? 48 89 7C 24 ? 8B FA C1 EB")->rip().as<EntityList *>();


  auto local_pawn = memory.find_pattern("client.dll", "48 8D 05 ? ? ? ? C3 CC CC CC CC CC CC CC CC 48 83 EC ? 8B 0D")->rip().add(0x138);
  SPDLOG_INFO("LOCAL_PLAYER: {:#04x}", local_pawn.get_address());
  auto [address, size] = memory.get_module_info("client.dll");
  client = address.value();
  local_player = memory.readv<uintptr_t>(local_pawn.get_address());
  SPDLOG_INFO("MODULE_BASE: {}", address.value());
  static WindowManager manager;
  if (!manager.create()) {
    manager.cleanup();
    MessageBox(0, "Failed while trying to initialize modules", "Error", MB_ICONERROR);
  }

  manager.load_font("ProggyClean.ttf", 24);

  SDL_Event event;
  while (!manager.should_close(&event)) {

    for (auto i = 1; i < 2048; i++) {

     auto e_list = EntityList::get();
      if (!e_list)
        continue;
      const auto entity = e_list->get<uintptr_t>(i);
      if (!entity)
        continue;

      uintptr_t entity_identity = memory.readv<uintptr_t>(entity + 0x10);
      if (!entity_identity)
        continue;

      uintptr_t designer_name = memory.readv<uintptr_t>(entity_identity + 0x20);
      if (!designer_name)
        continue;

      std::string clazz_name = memory.read_str(designer_name);

      SPDLOG_INFO("ENTITY: {} name {}", entity, clazz_name);

    }

    manager.update();
    manager.make_window_transparent(manager.m_window, RGB(0, 0, 0));

    if (GetAsyncKeyState(VK_XBUTTON2))
      manager.draw_rect((manager.m_width - 100) / 2, (manager.m_height - 100) / 2, 100, 100, settings::colors::red);
    else
      manager.draw_rect((manager.m_width - 100) / 2, (manager.m_height - 100) / 2, 100, 100, settings::colors::green);

    misc::bomb_timer(manager);

    manager.render();

    // SPDLOG_INFO("MOUSE_X: {} MOUSE_Y {}", x, y);

    // if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) // TODO: change to SDL events
    // manager.send_events(manager.m_hwnd, x, y);
  }

  manager.cleanup();

  return EXIT_SUCCESS;
}