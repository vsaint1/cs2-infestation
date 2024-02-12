#include "player_entity.h"

void PlayerEntity::set_is_visible(bool& spotted_state, int& local_idx) {

	this->visible = spotted_state & (1 << local_idx - 1);
}


bool PlayerEntity::is_visible() {
	return this->visible;
}

float PlayerEntity::get_distance() {
	return this->distance / 100;
}

void PlayerEntity::set_health(int& health) {

	this->health = health;
}

void PlayerEntity::set_weapon(std::string& current_weapon) {

	if (current_weapon.empty())
		this->weapon_name = "unknown_weapon";
	else
		this->weapon_name = current_weapon.substr(7);

}

void PlayerEntity::set_distance(FVector3& local_position, FVector3& enemy_position) {

	this->distance = enemy_position.distance(local_position);
}

void PlayerEntity::set_player_name(std::string& name) {

	if (name.empty())
		this->name = "unknown";
	else
		this->name = name;

}

void PlayerEntity::set_player_team(int& current_team) {

	this->team = current_team;
}

void PlayerEntity::set_player_health(int& current_health) {

	this->health = current_health;
}

bool PlayerEntity::is_dead(int& health) {

	return health <= 0 || health > 100;
}

bool PlayerEntity::is_localplayer(uintptr_t& pawn, uintptr_t& local_pawn) {
	return pawn == local_pawn;
}

bool PlayerEntity::is_team_mate(int& local_team, int& entity_team) {

	return local_team == entity_team;
}