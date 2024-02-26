/*
 *   Copyright (c) 2024 vsantos1
 *   All rights reserved.
 */
#ifndef SDK_ENTITY_LIST_H_
#define SDK_ENTITY_LIST_H_

#include "../memory/memory.hpp"

class EntityList {

public:
  static EntityList *get();

  template <typename T> T get(const int i) {
    const auto list_entry = memory.readv<uintptr_t>(this + 8LL * ((i & 0x7FFF) >> 9) + 16);

    if (!list_entry)
      return 0;

    const auto controller = list_entry + 120LL * (i & 0x1FF);

    if (!controller)
      return 0;

    return memory.readv<T>(controller);
  }

  const int max_entities(){
    return memory.readv<int>(this + 0x1510);
  }

};

inline EntityList *g_entity_list{};

#endif // SDK_ENTITY_LIST_H_
