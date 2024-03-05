/*
 *   Copyright (c) 2024 vsantos1
 *   All rights reserved.
 */
#include "player_controller.h"


bool PlayerController::same_team(int local_team, int enemy_team) {
    return local_team == enemy_team;
}

bool PlayerController::is_localplayer(uintptr_t local_pawn, uintptr_t entity_pawn) {
    return entity_pawn == local_pawn;

}

bool PlayerController::is_dead(int &entity_health) {
    return entity_health <= 0 || entity_health > 100;

}

Vector3 PlayerController::get_bone_pos_2d(uintptr_t &bonearray, int &bone_id) {
    return memory.readv<Vector3>(bonearray + bone_id * 32).world_to_screen(local_viewmatrix);
}

Vector3 PlayerController::get_bone_pos_2d(uintptr_t bonearray, EBone bone) {
    return memory.readv<Vector3>(bonearray + static_cast<int>(bone) * 32).world_to_screen(local_viewmatrix);

}

PlayerController::PlayerController(uintptr_t pawn, int idx, EntityType type, int mHealth, bool mVisible,
                                   bool mHasGunImmunity, const Vector3 &mCurrentPos, uintptr_t mBoneArray,
                                   int mCurrentTeam, std::string mPlayerName, std::string mWeaponName)
        : BaseEntity(pawn, idx, type), m_health(mHealth), m_visible(mVisible), m_hasGunImmunity(mHasGunImmunity),
          m_currentPos(mCurrentPos), m_boneArray(mBoneArray), m_currentTeam(mCurrentTeam), m_playerName(std::move(mPlayerName)),
          m_weaponName(std::move(mWeaponName)) {}


float PlayerController::get_distance() {
    return this->m_currentPos.distance(local_player + offsets::C_BasePlayerPawn::m_vOldOrigin) / 100;
}

int PlayerController::get_m_health() const {
    return m_health;
}

bool PlayerController::is_m_visible() const {
    return m_visible;
}

bool PlayerController::is_m_has_gun_immunity() const {
    return m_hasGunImmunity;
}

const Vector3 &PlayerController::get_m_current_pos() const {
    return m_currentPos;
}

uintptr_t PlayerController::get_m_bone_array() const {
    return m_boneArray;
}

int PlayerController::get_m_current_team() const {
    return m_currentTeam;
}

std::string PlayerController::get_m_player_name() const {
    if (this->m_playerName.empty())
        return "unknown_player";
    else
        return this->m_playerName;
}

std::string PlayerController::get_m_weapon_name() const {
    if (this->m_weaponName.find("weapon_") == std::string::npos)
        return "unknown_weapon";
    else
        return this->m_weaponName.substr(7);
}


