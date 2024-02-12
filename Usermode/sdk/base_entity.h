#pragma once
#include "../features/math.h"

class BaseEntity {
public:
	unsigned int idx;
	const char* class_name;
	uintptr_t pawn;
	FVector3 origin;

	void set_pawn(uintptr_t& entity_pawn) {
		this->pawn = entity_pawn;
	}

	void set_idx(unsigned int& idx) {
		this->idx = idx;
	}

	void set_class_name(std::string clazz_name) {
		this->class_name = clazz_name.c_str();
	}

	void set_pawn_origin(FVector3& pawn_origin) {
		this->origin = pawn_origin;
	}

};