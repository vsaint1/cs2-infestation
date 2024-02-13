#pragma once


class GrenadeEntity : public BaseEntity {
	bool tick_begin;
	float distance;
	FVector3 initial_position;
	FVector3 current_position;
	bool explode_effect;

public:


	float get_distance() {
		return this->distance;
	}

	void set_distance(float& dist) {
		this->distance = dist;
	}

	void set_initial_position(FVector3& initial_position) {
		this->initial_position = initial_position;
	}

	void set_current_position(FVector3 nade_position) {
		this->current_position = nade_position;
	}

	FVector3 get_initial_position() {
		return this->initial_position;
	}

	FVector3 get_current_position() {
		return this->current_position;
	}

	bool is_desired_name(std::string& clazz_name) {
		return strcmp(class_name.c_str(), clazz_name.c_str()) == 0;
	}

	bool tick_began() {
		return this->tick_begin;
	}

	void set_tick_begin(bool& tick) {
		this->tick_begin = tick;
	}

	bool exploded() {
		return this->explode_effect;
	}

	void set_exploded(bool& exploded) {
		this->explode_effect = exploded;
	}

	ImVec2 center() {
		return ImVec2(this->current_position.x, this->current_position.y);
	}
};