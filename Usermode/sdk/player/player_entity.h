#pragma once
#include "../base_entity.h"


class PlayerEntity : public BaseEntity {

public:
	std::string name;
	std::string weapon_name;
	unsigned int health;
	int team;
	bool visible;
	float distance;

	void set_is_visible(bool& spotted_state, int& local_idx);

	bool is_visible();

	float get_distance();

	void set_health(int& health);

	void set_weapon(std::string& current_weapon);

	void set_distance(FVector3& local_position, FVector3& enemy_position);

	void set_player_name(std::string &name);

	void set_player_team(int& current_team);

	void set_player_health(int& current_health);

	static bool is_dead(int& health);

	static bool is_localplayer(uintptr_t &pawn, uintptr_t &local_pawn);

	static bool is_team_mate(int &local_team, int &entity_team);

};

inline std::vector<PlayerEntity> entities;