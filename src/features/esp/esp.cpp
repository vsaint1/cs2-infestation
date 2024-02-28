/*
 *   Copyright (c) 2024 vsantos1
 *   All rights reserved.
 */
#include "esp.hpp"

void esp::render() {

  if (!local_player)
    return;

  const auto entity_list = EntityList::get();

  if (!entity_list)
    return;

  entity_list->update();
  
  for (const auto &entity : entities) {

    if (entity.type == EntityType::INVALID)
      continue;

    if (entity.type == EntityType::INFERNO && settings::world::grenade_inferno_esp)
      _inferno(entity);

    if (entity.type == EntityType::CHICKEN && settings::world::chicken_esp)
      _chicken(entity);

    uintptr_t entity_identity = memory.readv<uintptr_t>(entity.pawn + offsets::CEntityInstance::m_pEntity);

    if (!entity_identity)
      continue;

    uintptr_t designer_name = memory.readv<uintptr_t>(entity_identity + offsets::CEntityIdentity::m_designerName);

    if (!designer_name)
      continue;

    const auto node = memory.readv<uintptr_t>(entity.pawn + offsets::C_BaseEntity::m_pGameSceneNode);

    Vector3 abs_origin = memory.readv<Vector3>(node + offsets::CGameSceneNode::m_vecOrigin);

    if (abs_origin.is_zero())
      continue;

    Vector3 screen_pos = abs_origin.world_to_screen(local_viewmatrix);

    if (screen_pos.z < 0.001f)
      continue;

    float dist = memory.readv<Vector3>(local_player + offsets::C_BasePlayerPawn::m_vOldOrigin).distance(abs_origin) / 100;

    auto clazz_name = memory.read_str(designer_name);

    if (entity.type == EntityType::WEAPON) {

      if (settings::world::weapon_icon)
        draw::icon_esp(ImGui::GetIO().Fonts->Fonts[1], clazz_name.substr(7).c_str(), screen_pos, ImColor(255, 255, 255, 255));

      if (settings::world::weapon_name)
        draw::text(clazz_name.substr(7).c_str(), ImVec2(screen_pos.x, screen_pos.y - 10), settings::colors::weapon_dropped);

      if (settings::world::weapon_distance)
        draw::distance_a(ImVec2(screen_pos.x, screen_pos.y), dist, settings::colors::weapon_distance);
    }

    if (entity.type == EntityType::GRENADE) {

      const auto normalized_str = clazz_name.erase(clazz_name.find("_projectile"), 11).c_str();

      if (settings::world::grenade_warning)
        draw::grenade_esp(ImGui::GetIO().Fonts->Fonts[1], normalized_str, dist, ImVec2(screen_pos.x, screen_pos.y), ImColor(255, 255, 255, 255), 20.0f);


      //draw::path(screen_pos);
    
    }
  }
}

void esp::_inferno(const BaseEntity &ent) {

  auto burning = memory.readv<bool>(ent.pawn + offsets::C_Inferno::m_bFireIsBurning);

  if (!burning)
    return;

  const auto node = memory.readv<uintptr_t>(ent.pawn + offsets::C_BaseEntity::m_pGameSceneNode);

  Vector3 abs_origin = memory.readv<Vector3>(node + offsets::CGameSceneNode::m_vecOrigin);

  if (!abs_origin.is_zero()) {

    Vector3 screen_pos = abs_origin.world_to_screen(local_viewmatrix);

    if (screen_pos.z < 0.001f)
      return;

    float dist = memory.readv<Vector3>(local_player + offsets::C_BasePlayerPawn::m_vOldOrigin).distance(abs_origin) / 100;

    draw::grenade_esp(ImGui::GetIO().Fonts->Fonts[1], "molotov", dist, ImVec2(screen_pos.x, screen_pos.y), ImColor(255, 255, 255, 255), 20.0f);
  }
}

void esp::_chicken(const BaseEntity &ent) {
  const auto node = memory.readv<uintptr_t>(ent.pawn + offsets::C_BaseEntity::m_pGameSceneNode);

  Vector3 abs_origin = memory.readv<Vector3>(node + offsets::CGameSceneNode::m_vecOrigin);

  if (!abs_origin.is_zero()) {

    Vector3 screen_pos = abs_origin.world_to_screen(local_viewmatrix);

    if (screen_pos.z < 0.001f)
      return;

    float dist = memory.readv<Vector3>(local_player + offsets::C_BasePlayerPawn::m_vOldOrigin).distance(abs_origin) / 100;

    draw::text("Chicken_Little", ImVec2(screen_pos.x, screen_pos.y - 10), ImColor(255, 0, 0, 255));
  }
}
