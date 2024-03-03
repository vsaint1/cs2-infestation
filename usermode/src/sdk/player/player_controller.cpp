/*
 *   Copyright (c) 2024 vsantos1
 *   All rights reserved.
 */
#include "player_controller.h"


bool PlayerController::same_team(int &local_team,int &enemy_team) {
    return local_team == enemy_team;
}

bool PlayerController::is_localplayer(uintptr_t &local_pawn, uintptr_t &entity_pawn) {
    return entity_pawn == local_pawn;

}

bool PlayerController::is_dead(int &entity_health) {
    return entity_health <= 0 || entity_health > 100;

}

Vector3 PlayerController::get_bone_pos_2d(uintptr_t &bonearray, int &bone_id) {
    return memory.readv<Vector3>(bonearray + bone_id * 32).world_to_screen(local_viewmatrix);
}

Vector3 PlayerController::get_bone_pos_2d(uintptr_t &bonearray, EBone bone) {
    return memory.readv<Vector3>(bonearray + static_cast<int>(bone) * 32).world_to_screen(local_viewmatrix);

}


