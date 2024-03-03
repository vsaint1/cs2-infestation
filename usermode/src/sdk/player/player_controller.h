/*
 *   Copyright (c) 2024 vsantos1
 *   All rights reserved.
 */

#ifndef SDK_PLAYER_CONTROLLER_HPP_
#define SDK_PLAYER_CONTROLLER_HPP_

#include "../base_entity.hpp"

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

public:


    static Vector3 get_bone_pos_2d(uintptr_t bonearray,EBone bone);

    static Vector3 get_bone_pos_2d(uintptr_t &bonearray,int &bone_id);

    static bool is_localplayer(uintptr_t &local_pawn, uintptr_t &entity_pawn);

    static bool is_dead(int &entity_health);

    static bool same_team(int &local_team, int &enemy_team);

};

#endif // SDK_PLAYER_CONTROLLER_HPP_
