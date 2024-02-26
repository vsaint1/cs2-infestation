/*
 *   Copyright (c) 2024 vsantos1
 *   All rights reserved.
 */
#include "esp.hpp"
#include "../../sdk/entity_list.hpp"
#include "../../window/draw/drawing.hpp"
#include "../globals.h"
#include "../math.h"

void esp::weapon() {

  if (!settings::world::weapon_esp)
    return;

  const auto entity_list = EntityList::get();

  if (!entity_list)
    return;

  for (auto i = 65; i < entity_list->max_entities(); i++) {

    const auto entity = entity_list->get<uintptr_t>(i);

    if (!entity)
      continue;

    uintptr_t entity_identity = memory.readv<uintptr_t>(entity + offsets::CEntityInstance::m_pEntity);

    if (!entity_identity)
      continue;

    uintptr_t designer_name = memory.readv<uintptr_t>(entity_identity + offsets::CEntityIdentity::m_designerName);

    if (!designer_name)
      continue;

    const auto clazz_name = memory.read_str(designer_name);

    if (clazz_name.empty())
      continue;

    if (clazz_name.find("weapon_") == std::string::npos)
      continue;

    const auto node = memory.readv<uintptr_t>(entity + offsets::C_BaseEntity::m_pGameSceneNode);

    Vector3 abs_origin = memory.readv<Vector3>(node + offsets::CGameSceneNode::m_vecOrigin);

    if (abs_origin.is_zero())
      continue;

    Vector3 screen_pos = abs_origin.world_to_screen(local_viewmatrix);

    if (screen_pos.z < 0.001f)
      continue;

    draw::text(clazz_name.substr(7).c_str(), ImVec2(screen_pos.x, screen_pos.y - 25), settings::colors::weapon_dropped);
  }
}

void esp::grenades() {

  if (!settings::world::grenade_esp)
    return;

  const auto entity_list = EntityList::get();

  if (!entity_list)
    return;

  for (auto i = 65; i < entity_list->max_entities(); i++) {

    const auto entity = entity_list->get<uintptr_t>(i);

    if (!entity)
      continue;

    uintptr_t entity_identity = memory.readv<uintptr_t>(entity + offsets::CEntityInstance::m_pEntity);

    if (!entity_identity)
      continue;

    uintptr_t designer_name = memory.readv<uintptr_t>(entity_identity + offsets::CEntityIdentity::m_designerName);

    if (!designer_name)
      continue;

    auto clazz_name = memory.read_str(designer_name);

    if (clazz_name.empty())
      continue;

    const char *nades[5] = {"smokegrenade_projectile", "hegrenade_projectile", "flashbang_projectile", "molotov_projectile", "flashbang_projectile"};

    if (std::find(std::begin(nades), std::end(nades), clazz_name) == std::end(nades))
      continue;

    auto normalized_str = clazz_name.erase(clazz_name.find("_projectile"), 11).c_str();

    const auto node = memory.readv<uintptr_t>(entity + offsets::C_BaseEntity::m_pGameSceneNode);

    Vector3 abs_origin = memory.readv<Vector3>(node + offsets::CGameSceneNode::m_vecOrigin);

    if (abs_origin.is_zero())
      continue;

    float dist = abs_origin.distance(memory.readv<Vector3>(local_player + offsets::C_BasePlayerPawn::m_vOldOrigin)) / 100;

    Vector3 screen_pos = abs_origin.world_to_screen(local_viewmatrix);

    if (screen_pos.z < 0.001f)
      continue;

    if (settings::world::grenade_warning)
      draw::grenade_esp(ImGui::GetIO().Fonts->Fonts[1], normalized_str, dist, ImVec2(screen_pos.x, screen_pos.y), ImColor(255, 255, 255, 255), 20.0f);
  }
};