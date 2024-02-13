#pragma once
#include <cstdint>
#include <map>
#include "../base_entity.h"
#include "../../memory/memory.h"

enum EBone : uint8_t {

	Head = 6,
	Neck = 5,
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

class PlayerEntity : public BaseEntity {

	uintptr_t bone_array;
	ViewMatrix local_viewmatrix;
	float distance;
	int team;
	bool visible;

public:

	std::string name;
	std::string weapon_name;
	unsigned int health;


	FVector3 get_bone_pos_2d(EBone bone) {
		return process.readv<FVector3>(bone_array + static_cast<int>(bone) * 32).world_to_screen(local_viewmatrix);
	}

	void set_is_visible(bool& spotted_state, int& local_idx);

	bool is_visible();

	float get_distance();

	void set_health(int& health);

	void set_weapon(std::string& current_weapon);

	void set_distance(FVector3& local_position, FVector3& enemy_position);

	void set_player_name(std::string& name);

	void set_player_team(int& current_team);

	void set_player_health(int& current_health);

	void set_player_bonearray(uintptr_t& bonearray);

	void set_local_viewmatrix(ViewMatrix& viewmatrix);

	static bool is_dead(int health);

	static bool is_localplayer(uintptr_t& pawn, uintptr_t& local_pawn);

	static bool is_team_mate(int& local_team, int& entity_team);

};

inline std::vector<PlayerEntity> entities;