#include "bomb.hpp"

void misc::bomb_timer(WindowManager &manager) {

  global_vars = memory.readv<GlobalVarsBase>(memory.readv<uintptr_t>(client + offsets::dwGlobalVars));

  auto temp_c4 = memory.readv<uintptr_t>(client + offsets::dwPlantedC4);
  auto plantedC4 = memory.readv<uintptr_t>(temp_c4);

  auto bombplanted = memory.readv<bool>(client + offsets::dwPlantedC4 - 0x8);

  if (!bombplanted)
    manager.draw_text("Waiting bomb", 36, 702, settings::colors::gray);

  if (bombplanted) {
    auto bomb_site = memory.readv<int>(plantedC4 + offsets::C_PlantedC4::m_nBombSite); 

    bool bomb_defused = memory.readv<bool>(plantedC4 + offsets::C_PlantedC4::m_bBombDefused); 

    auto temp_bomb_time = memory.readv<float>(plantedC4 + offsets::C_PlantedC4::m_flC4Blow); 
    auto fl_bomb_time = temp_bomb_time - global_vars.m_flcurrentTime;

    bool being_defused = memory.readv<bool>(plantedC4 + offsets::C_PlantedC4::m_bBeingDefused); 

    float temp_defuse_time = memory.readv<float>(plantedC4 + offsets::C_PlantedC4::m_flDefuseCountDown);
    auto fl_defuse_time = temp_defuse_time - global_vars.m_flcurrentTime;

    if (!bomb_defused && fl_bomb_time > 0) {
      std::string bomb_timer(fmt::format("Bomb planted on {}, Explodes in {:.2f} ", bomb_site == 0 ? "A" : "B", fl_bomb_time));
      manager.draw_text(bomb_timer, 36, 700, settings::colors::gray);
    }

    if (being_defused && fl_defuse_time > 0) {
      std::string defuse_timer(fmt::format("Bomb being defused, time remaining {:.2f}", fl_defuse_time));
      manager.draw_text(defuse_timer, 36, 730, settings::colors::red);
    }

  }
}