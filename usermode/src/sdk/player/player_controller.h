/*
 *   Copyright (c) 2024 vsantos1
 *   All rights reserved.
 */

#ifndef SDK_PLAYER_CONTROLLER_HPP_
#define SDK_PLAYER_CONTROLLER_HPP_

#include "../base_entity.hpp"
#include <utility>

enum EBone : uint8_t {

  Head = 6,
  Neck = 5,
  Chest = 4,
  RightShoulder = 8,
  LeftShoulder = 13,
  RightArm = 9,
  LeftArm = 14,
  RightHand = 11,
  LeftHand = 16,
  Root = 0,
  RightKnee = 23,
  LeftKnee = 26,
  RightFoot = 24,
  LeftFoot = 27

};

class PlayerController : public BaseEntity {

  int m_health;
  bool m_visible;
  bool m_hasGunImmunity;
  Vector3 m_currentPos;
  uintptr_t m_boneArray;
  int m_currentTeam;
  std::string m_playerName;
  std::string m_weaponName;

public:
  static bool same_team(int local_team, int enemy_team);

  static bool is_localplayer(uintptr_t local_pawn, uintptr_t entity_pawn);
  static bool is_dead(int &entity_health);

  static Vector3 get_bone_pos_2d(uintptr_t &bonearray, int &bone_id);

  static Vector3 get_bone_pos_2d(uintptr_t bonearray, EBone bone);

  PlayerController(uintptr_t pawn, int idx, EntityType type, int mHealth, bool mVisible, bool mHasGunImmunity, const Vector3 &mCurrentPos, uintptr_t mBoneArray, int mCurrentTeam,
                   std::string mPlayerName, std::string mWeaponName);

  float get_distance();

  int get_m_health() const;

  bool is_m_visible() const;

  bool is_m_has_gun_immunity() const;

  const Vector3 &get_m_current_pos() const;

  uintptr_t get_m_bone_array() const;

  int get_m_current_team() const;

  std::string get_m_player_name() const;

  std::string get_m_weapon_name() const;
};

#endif // SDK_PLAYER_CONTROLLER_HPP_
