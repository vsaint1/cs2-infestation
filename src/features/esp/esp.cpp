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

    draw::text(clazz_name.substr(7).c_str(), ImVec2(screen_pos.x, screen_pos.y - 25), settings::colors::weapon_dropped);
  }
}

void esp::grenades() { return; };