/*
 *   Copyright (c) 2024 vsantos1
 *   All rights reserved.
 */
#ifndef SDK_ENTITY_LIST_H_
#define SDK_ENTITY_LIST_H_

#include "../features/globals.h"
#include "../memory/memory.hpp"
#include "base_entity.hpp"
#include "player/player_controller.h"

class EntityList {

public:
  static EntityList *get();

  void update();

  template <typename T> T get(const int i) {
    const auto list_entry = memory.readv<uintptr_t>(this + 8LL * ((i & 0x7FFF) >> 9) + 16);

    if (!list_entry)
      return 0;

    const auto controller = list_entry + 120LL * (i & 0x1FF);

    if (!controller)
      return 0;

    return memory.readv<T>(controller);
  }

  const int max_entities() { return memory.readv<int>(this + offsets::dwGameEntitySystem_getHighestEntityIndex); }

  const std::string get_schema_name(const uintptr_t &entity);
};

inline EntityList *g_entity_list{};

#endif // SDK_ENTITY_LIST_H_
