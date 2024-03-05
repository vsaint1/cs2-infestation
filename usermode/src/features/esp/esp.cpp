/*
 *   Copyright (c) 2024 vsantos1
 *   All rights reserved.
 */
#include "esp.hpp"

void esp::render() {

  auto local_pos = memory.readv<Vector3>(local_player + offsets::C_BasePlayerPawn::m_vOldOrigin);
  int local_team = memory.readv<int>(local_player + offsets::C_BaseEntity::m_iTeamNum);

  for (const auto &entity : entities) {

    if (entity.type == EntityType::INVALID)
      continue;

    if (entity.type == EntityType::PLAYER && settings::visuals::player_esp) {
      const auto entity_list = EntityList::get();
      uintptr_t player = entity_list->get<uintptr_t>(entity.nIdx);

      if (!player)
        continue;

      std::uint32_t h_pawn = memory.readv<std::uint32_t>(player + offsets::CCSPlayerController::m_hPlayerPawn);

      uintptr_t list_entry2 = memory.readv<uintptr_t>(entity_list + 0x8 * ((h_pawn & 0x7FFF) >> 9) + 16);

      if (!list_entry2)
        continue;

      uintptr_t pcs_pawn = memory.readv<uintptr_t>(list_entry2 + 120 * (h_pawn & 0x1FF));

      if (pcs_pawn == local_player)
        continue;

      Vector3 e_position = memory.readv<Vector3>(pcs_pawn + offsets::C_BasePlayerPawn::m_vOldOrigin);

      int e_health = memory.readv<int>(pcs_pawn + offsets::C_BaseEntity::m_iHealth);

      if (e_health <= 0 || e_health > 100)
        continue;

      int e_team = memory.readv<int>(pcs_pawn + offsets::C_BaseEntity::m_iTeamNum);

      if (settings::misc::team_check && local_team == e_team)
        continue;

      auto m_pclippingweapon = memory.readv<uintptr_t>(pcs_pawn + offsets::C_CSPlayerPawnBase::m_pClippingWeapon);
      auto entity_identity = memory.readv<uintptr_t>(m_pclippingweapon + offsets::CEntityInstance::m_pEntity);
      auto des_name = memory.readv<uintptr_t>(entity_identity + offsets::CEntityIdentity::m_designerName);

      std::string weap_name = memory.read_str(des_name);
      if (weap_name.empty())
        continue;

      std::string e_name = memory.read_str(player + offsets::CBasePlayerController::m_iszPlayerName);
      if (e_name.empty())
        continue;
      bool e_spotted = memory.readv<bool>(pcs_pawn + offsets::C_CSPlayerPawn::m_entitySpottedState + offsets::EntitySpottedState_t::m_bSpottedByMask);
      bool local_spotted = memory.readv<bool>(local_player + offsets::C_CSPlayerPawn::m_entitySpottedState + offsets::EntitySpottedState_t::m_bSpottedByMask);
      bool visible = e_spotted & (1 << local_player);

      // CSkeletonInstance
      uintptr_t p_gamescene = memory.readv<uintptr_t>(pcs_pawn + offsets::C_BaseEntity::m_pGameSceneNode);
      uintptr_t p_bonearray = memory.readv<uintptr_t>(p_gamescene + offsets::CSkeletonInstance::m_modelState + offsets::CGameSceneNode::m_vecOrigin);

#if _DEBUG
      SPDLOG_INFO("NAME {} HEALTH {} WEAPON {} TEAM{}", e_name, e_health, weap_name, e_team);
#endif

      if (e_position.is_zero())
        continue;

      float distance = e_position.distance(local_pos) / 100;

      const auto weapon_str = weap_name.erase(weap_name.find("weapon_"), 7);

      Vector3 screen_pos = e_position.world_to_screen(local_viewmatrix);

      if (screen_pos.z < 0.001f)
        continue;

      Vector3 head_pos = PlayerController::get_bone_pos_2d(p_bonearray, EBone::Head);

      float h = abs(screen_pos.y - head_pos.y);
      float w = h / 2.0f;

      if (settings::visuals::player_weapon)
        draw::icon_esp(ImGui::GetIO().Fonts->Fonts[1], weapon_str.c_str(), screen_pos, settings::colors::player_weapon);

      if (settings::visuals::player_name)
        draw::text(e_name.c_str(), ImVec2(screen_pos.x, head_pos.y - 25), settings::colors::player_name);

      if (settings::visuals::player_distance)
        draw::distance_a(ImVec2(screen_pos.x, screen_pos.y), distance, settings::colors::player_distance);

      if (settings::visuals::player_snaplines)
        draw::snaplines(screen_pos, settings::colors::player_snaplines);

      if (settings::visuals::player_skeleton)
        draw::skeleton(p_bonearray, visible);

      if (settings::visuals::player_health)
        draw::healthbar(screen_pos.x + 25, head_pos.y - 25, w, h, 2, e_health);
    }

    if (entity.type == EntityType::INFERNO && settings::world::grenade_inferno_esp)
      _inferno(entity);

    if (entity.type == EntityType::CHICKEN && settings::world::chicken_esp)
      _chicken(entity);

    const auto entity_identity = memory.readv<uintptr_t>(entity.pawn + offsets::CEntityInstance::m_pEntity);

    if (!entity_identity)
      continue;

    const auto designer_name = memory.readv<uintptr_t>(entity_identity + offsets::CEntityIdentity::m_designerName);

    if (!designer_name)
      continue;

    const auto node = memory.readv<uintptr_t>(entity.pawn + offsets::C_BaseEntity::m_pGameSceneNode);

    auto abs_origin = memory.readv<Vector3>(node + offsets::CGameSceneNode::m_vecOrigin);

    if (abs_origin.is_zero())
      continue;

    Vector3 screen_pos = abs_origin.world_to_screen(local_viewmatrix);

    if (screen_pos.z < 0.001f)
      continue;

    float dist = abs_origin.distance(local_pos) / 100;

    auto clazz_name = memory.read_str(designer_name);

    if (clazz_name.empty())
      continue;

    if (entity.type == EntityType::WEAPON) {

      const auto weapon_str = clazz_name.substr(7);

      if (settings::world::weapon_icon)
        draw::icon_esp(ImGui::GetIO().Fonts->Fonts[1], weapon_str.c_str(), screen_pos, ImColor(255, 255, 255, 255));

      if (settings::world::weapon_name)
        draw::text(weapon_str.c_str(), ImVec2(screen_pos.x, screen_pos.y - 10), settings::colors::weapon_dropped);

      if (settings::world::weapon_distance)
        draw::distance_a(ImVec2(screen_pos.x, screen_pos.y), dist, settings::colors::weapon_distance);
    }

    if (entity.type == EntityType::GRENADE) {

      const auto grenade_str = clazz_name.erase(clazz_name.find("_projectile"), 11).c_str();

      if (!strcmp(grenade_str, "decoy"))
        continue;

      const auto tick_begin = strcmp("smokegrenade", grenade_str) == 0 ? memory.readv<bool>(entity.pawn + offsets::C_SmokeGrenadeProjectile::m_nSmokeEffectTickBegin)
                                                                       : memory.readv<bool>(entity.pawn + offsets::C_BaseCSGrenadeProjectile::m_bExplodeEffectBegan);

      if (settings::world::grenade_warning)
        draw::grenade_esp(ImGui::GetIO().Fonts->Fonts[1], grenade_str, dist, ImVec2(screen_pos.x, screen_pos.y), ImColor(255, 255, 255, 255), 20.0f);

      if (settings::world::grenade_trajectory)
        draw::path(screen_pos, entity.nIdx, tick_begin);
    }
  }
}

void esp::_inferno(const BaseEntity &ent) {

  auto burning = memory.readv<bool>(ent.pawn + offsets::C_Inferno::m_bFireIsBurning);

  if (!burning)
    return;

  const auto node = memory.readv<uintptr_t>(ent.pawn + offsets::C_BaseEntity::m_pGameSceneNode);

  auto abs_origin = memory.readv<Vector3>(node + offsets::CGameSceneNode::m_vecOrigin);

  if (abs_origin.is_zero())
    return;

  Vector3 screen_pos = abs_origin.world_to_screen(local_viewmatrix);

  if (screen_pos.z < 0.001f)
    return;

  float dist = memory.readv<Vector3>(local_player + offsets::C_BasePlayerPawn::m_vOldOrigin).distance(abs_origin) / 100;

  draw::grenade_esp(ImGui::GetIO().Fonts->Fonts[1], "molotov", dist, ImVec2(screen_pos.x, screen_pos.y), ImColor(255, 255, 255, 255), 20.0f);
}

void esp::_chicken(const BaseEntity &ent) {
  const auto node = memory.readv<uintptr_t>(ent.pawn + offsets::C_BaseEntity::m_pGameSceneNode);

  auto abs_origin = memory.readv<Vector3>(node + offsets::CGameSceneNode::m_vecOrigin);

  if (!abs_origin.is_zero()) {

    Vector3 screen_pos = abs_origin.world_to_screen(local_viewmatrix);

    if (screen_pos.z < 0.001f)
      return;

    draw::text("Chicken_Little", ImVec2(screen_pos.x, screen_pos.y - 10), ImColor(255, 0, 0, 255));
  }
}

void esp::_player(const PlayerController &player_controller) {

  // TODO : fix player esp random crashes
}