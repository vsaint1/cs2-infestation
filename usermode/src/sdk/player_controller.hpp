/*
 *   Copyright (c) 2024 vsantos1
 *   All rights reserved.
 */

#ifndef SDK_PLAYER_JECA_HPP_
#define SDK_PLAYER_JECA_HPP_
#include "../memory/memory.hpp"

class PlayerController {

public:
  int get_health() { return memory.readv<int>(this + 0x334); }

  uintptr_t get_pawn() { return memory.readv<uintptr_t>(this + 0x7E4); }

  std::string get_name() {
    const auto sanitized_player_name = memory.readv<uintptr_t>(this + 0x748);
    if (!sanitized_player_name)
      return "invalid";

    auto player_name = memory.read_str(sanitized_player_name);
    if (player_name.empty())
      return "invalid";

    return player_name;
  }
};

#endif // SDK_PLAYER_JECA_HPP_