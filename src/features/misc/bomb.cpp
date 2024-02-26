#include "bomb.hpp"

void misc::bomb_timer() {

  global_vars = memory.readv<GlobalVarsBase>(memory.readv<uintptr_t>(client + offsets::dwGlobalVars));

  auto temp_c4 = memory.readv<uintptr_t>(client + offsets::dwPlantedC4);
  auto plantedC4 = memory.readv<uintptr_t>(temp_c4);

  auto bombplanted = memory.readv<bool>(client + offsets::dwPlantedC4 - 0x8);

  if (!bombplanted)
    ImGui::GetBackgroundDrawList()->AddText(ImVec2(36, 700), settings::colors::bomb_timer, "Waiting bomb");

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
      ImGui::GetBackgroundDrawList()->AddText(ImVec2(30, 700), settings::colors::bomb_timer, bomb_timer.c_str());
    }

    if (being_defused && fl_defuse_time > 0) {
      std::string defuse_timer(fmt::format("Bomb being defused, time remaining {:.2f}", fl_defuse_time));
      ImGui::GetBackgroundDrawList()->AddText(ImVec2(30, 740), settings::colors::defuse_timer, defuse_timer.c_str());
    }
  }
}