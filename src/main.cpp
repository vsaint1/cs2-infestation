//
// Created by vsantos1 on 2/16/2024.
//
#define SDL_MAIN_HANDLED
#include "features/globals.h"
#include "sdk/entity_list.hpp"
#include "sdk/global_vars.hpp"
#include "window/window_manager.h"

int main() {
  memory.attach();

  SPDLOG_INFO("PID {} \n", memory.get_pid());
  auto entity_list = memory.find_pattern("client.dll", "48 8B 0D ? ? ? ? 48 89 7C 24 ? 8B FA C1 EB")->rip();
  auto local_pawn = memory.find_pattern("client.dll", "48 8D 05 ? ? ? ? C3 CC CC CC CC CC CC CC CC 48 83 EC ? 8B 0D")->rip().add(0x138);
  SPDLOG_INFO("LOCAL_PLAYER: {:#04x}", local_pawn.get_address());
  auto [address, size] = memory.get_module_info("client.dll");
  client = address.value();
  local_player = local_pawn.get_address();
  SPDLOG_INFO("MODULE_BASE: {}", address.value());

  WindowManager manager;

  if (!manager.create()) {
    manager.cleanup();
    MessageBox(0, "Failed while trying to initialize modules", "Error", MB_ICONERROR);
  }

  manager.load_font("ProggyClean.ttf", 24);

  int x, y = 0;


  SDL_Event event;
  while (!manager.should_close(&event)) {
    global_vars = memory.readv<GlobalVarsBase>(memory.readv<uintptr_t>(address.value() + 0x171CE70));

    manager.make_window_transparent(manager.m_window, RGB(0, 0, 0));

    if (GetAsyncKeyState(VK_XBUTTON2))
      manager.draw_rect((manager.m_width - 100) / 2, (manager.m_height - 100) / 2, 100, 100, settings::colors::red);
    else
      manager.draw_rect((manager.m_width - 100) / 2, (manager.m_height - 100) / 2, 100, 100, settings::colors::green);

    auto temp_c4 = memory.readv<uintptr_t>(address.value() + 0x191B508);
    auto plantedC4 = memory.readv<uintptr_t>(temp_c4);

    auto bombplanted = memory.readv<bool>(address.value() + 0x191B508 - 0x8);


    manager.draw_text(memory.read_str(global_vars.m_currentMapName), 300, 300, settings::colors::gray);
    if (!bombplanted)
      manager.draw_text("Wainting bomb", 36, 702,  settings::colors::gray);

    manager.draw_text(std::to_string(global_vars.m_currentMapName), 36, 800,  settings::colors::gray);

    if (bombplanted) {
      auto bomb_site = memory.readv<int>(plantedC4 + 0xedc); // m_nBombSite

      bool bomb_defused = memory.readv<bool>(plantedC4 + 0xf2c); // m_bBombDefused

      auto temp_bomb_time = memory.readv<float>(plantedC4 + 0xf08); // m_flC4Blow
      auto fl_bomb_time = temp_bomb_time - global_vars.m_flcurrentTime;

      bool being_defused = memory.readv<bool>(plantedC4 + 0xf14); // m_bBeingDefused

      float temp_defuse_time = memory.readv<float>(plantedC4 + 0xf28); // m_flDefuseCountDown
      auto fl_defuse_time = temp_defuse_time - global_vars.m_flcurrentTime;


      if (!bomb_defused) {
        std::string bomb_timer(fmt::format("Bomb planted on {}, Explodes in {:.2f} ", bomb_site == 0 ? "A" : "B", fl_bomb_time));
        manager.draw_text(bomb_timer, 36, 700,  settings::colors::gray);
      }

      if (being_defused && fl_defuse_time > 0) {
        std::string defuse_timer(fmt::format("Bomb being defused, time remaining {:.2f}", fl_defuse_time));
        manager.draw_text(defuse_timer, 36, 730,  settings::colors::red);
      }

    }

    manager.render();

    auto cursor = SDL_GetGlobalMouseState(&x, &y);

    // SPDLOG_INFO("MOUSE_X: {} MOUSE_Y {}", x, y);

    // if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) // TODO: change to SDL events
    //   manager.send_events(manager.m_hwnd, x, y);
  }

  manager.cleanup();

  return EXIT_SUCCESS;
}