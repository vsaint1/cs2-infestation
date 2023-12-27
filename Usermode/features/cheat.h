#pragma once
#include "globals.h"
#include "math.h"
#include "../memory/memory.h"
#include <thread>
#include "esp/esp.h"

void cache_entities() {
	while (true) {
		std::vector<Entity> temp;
		uintptr_t local_player = process.readv<uintptr_t>(client + offsets::dwLocalPlayerPawn);

		if (!local_player)
			continue;

		global_pawn = local_player;

		FVector3 local_pos = process.readv<FVector3>(local_player + offsets::m_vecOrigin);
		static int local_index = 1;

		int local_team = process.readv<int>(local_player + offsets::m_iTeamNum);


		uintptr_t entity_list = process.readv<uintptr_t>(client + offsets::dwEntityList);

		for (int i = 1; i < 32; i++) {
			uintptr_t list_entry = process.readv<uintptr_t>(entity_list + (8 * (i & 0x7FFF) >> 9) + 16);
			if (!list_entry)
				continue;

			uintptr_t player = process.readv<uintptr_t>(list_entry + 120 * (i & 0x1FF));

			if (!player)
				continue;

			std::uint32_t h_pawn = process.readv<std::uint32_t>(player + offsets::dwPlayerPawn);

			uintptr_t list_entry2 = process.readv<uintptr_t>(entity_list + 0x8 * ((h_pawn & 0x7FFF) >> 9) + 16);

			if (!list_entry2)
				continue;

			uintptr_t pcs_pawn = process.readv<uintptr_t>(list_entry2 + 120 * (h_pawn & 0x1FF));

			if (pcs_pawn == local_player)
				continue;

			FVector3 pcs_pos = process.readv<FVector3>(pcs_pawn + offsets::m_vecOrigin);

			int e_health = process.readv<int>(pcs_pawn + offsets::m_iHealth);


			if (e_health <= 0 || e_health > 100)
				continue;

			int e_team = process.readv<int>(pcs_pawn + offsets::m_iTeamNum);

			if (settings::misc::bTeamcheck && local_team == e_team)
				continue;
			uintptr_t  p_gamescene = process.readv<uint64_t>(pcs_pawn + 0x310);
			uintptr_t  p_bonearray = process.readv<uint64_t>(p_gamescene + 0x1E0);


			Entity entity;

			entity.pawn = pcs_pawn;
			entity.name = "Unknown";
			entity.health = e_health;
			entity.visible = false; // TODO: add visible check
			entity.position = pcs_pos.Distance(local_pos) / 100;

			temp.push_back(entity);

			std::this_thread::sleep_for(std::chrono::milliseconds(10));
		}

		entities.clear();
		entities = temp;


	}

}



void entity_loop() {

	if (global_pawn) {

		view_matrix_t local_viewmatrix = process.readv<view_matrix_t>(client + offsets::dwViewMatrix);

		for (Entity entity : entities) {
			FVector3 origin = process.readv<FVector3>(entity.pawn + offsets::m_vecOrigin);

			FVector3 head;
			head.x = origin.x;
			head.y = origin.y;
			head.z = origin.z + 90.0f;

			FVector3 screen_pos = origin.world_to_screen(local_viewmatrix);

			if (screen_pos.z < 0.001f)
				continue;

			FVector3 project_head = head.world_to_screen(local_viewmatrix);

			uintptr_t  p_gamescene = process.readv<uint64_t>(entity.pawn + 0x310);
			uintptr_t  p_bonearray = process.readv<uint64_t>(p_gamescene + 0x1E0);

			FVector3 entity_pos = process.readv<FVector3>(entity.pawn + offsets::m_vecOrigin);

			FVector3 head_pos = FVector3(entity_pos.x, entity_pos.y, entity_pos.z + 63);

			FVector3 aim_pos = FVector3(entity_pos.x, entity_pos.y, entity_pos.z + 45);

			FVector3 head_bone = process.readv<FVector3>(p_bonearray + EBone::Head * 32);


			if (!world_to_screen(head_bone, head_pos, local_viewmatrix))
				continue;

			if (screen_pos.z >= 0.01f)
				draw_esp(head_pos, screen_pos, entity, p_bonearray, local_viewmatrix);



			std::thread(aimbot, entity, head_pos).detach();

		}

	}

}