/*
 *   Copyright (c) 2024 vsantos1
 *   All rights reserved.
 */
#ifndef SDK_BASE_ENTITY_HPP_
#define SDK_BASE_ENTITY_HPP_
#include "../memory/memory.hpp"
#include "../features/globals.h"


enum EntityType : uint8_t {

  INVALID = 0,
  PLAYER,
  GRENADE,
  INFERNO,
  WEAPON,
  C4,
  CHICKEN,
  FISH

};

class BaseEntity {

public:
  uintptr_t pawn;
  int nIdx = 0;
  EntityType type = EntityType::INVALID;

  BaseEntity(uintptr_t _pawn, int _idx, EntityType _type) : pawn(_pawn), nIdx(_idx), type(_type){};
};

inline std::vector<BaseEntity> entities;

#endif // SDK_BASE_ENTITY_HPP_
