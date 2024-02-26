#include "bomb.hpp"

void misc::bomb_timer() {
  if (!settings::misc::bomb_timer)
    return;

  global_vars = memory.readv<GlobalVarsBase>(memory.readv<uintptr_t>(client + offsets::dwGlobalVars));

  auto temp_c4 = memory.readv<uintptr_t>(client + offsets::dwPlantedC4);
  auto plantedC4 = memory.readv<uintptr_t>(temp_c4);

  auto bombplanted = memory.readv<bool>(client + offsets::dwPlantedC4 - 0x8);

  if (!bombplanted)
    draw::text("Waiting Bomb", ImVec2(40, 700), settings::colors::bomb_timer);

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
      draw::text(bomb_timer.c_str(), ImVec2(30, 700), settings::colors::bomb_timer);
    }

    if (being_defused && fl_defuse_time > 0) {
      std::string defuse_timer(fmt::format("Bomb being defused, time remaining {:.2f}", fl_defuse_time));
      draw::text(defuse_timer.c_str(), ImVec2(30, 740), settings::colors::bomb_timer);
    }

    const auto node = memory.readv<uintptr_t>(plantedC4 + offsets::C_BaseEntity::m_pGameSceneNode);

    Vector3 abs_origin = memory.readv<Vector3>(node + offsets::CGameSceneNode::m_vecOrigin);

    Vector3 screen_pos = abs_origin.world_to_screen(local_viewmatrix);

    if (screen_pos.z < 0.001f)
      return;

    draw::text(fmt::format("{:.2f}", fl_bomb_time).c_str(),ImVec2(screen_pos.x, screen_pos.y -25),settings::colors::defuse_timer);

  }
}