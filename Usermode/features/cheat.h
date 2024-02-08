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

		int local_index = 1;

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

			if (pcs_pawn == local_player) {
				local_index = i;
				continue;
			}

			FVector3 pcs_pos = process.readv<FVector3>(pcs_pawn + offsets::m_vecOrigin);

			int e_health = process.readv<int>(pcs_pawn + offsets::m_iHealth);


			if (e_health <= 0 || e_health > 100)
				continue;

			int e_team = process.readv<int>(pcs_pawn + offsets::m_iTeamNum);

			if (settings::misc::bTeamcheck && local_team == e_team)
				continue;

			std::string e_name = process.read_str(pcs_pawn + offsets::m_iszPlayerName);
			bool e_spotted = process.readv<bool>(pcs_pawn + offsets::bSpottedByMask);
			Entity entity;

			entity.pawn = pcs_pawn;
			entity.name = e_name.empty() ? "unknown" : e_name;
			entity.health = e_health;
			entity.visible = e_spotted & (1 << local_index - 1);
			entity.position = pcs_pos.distance(local_pos) / 100;
			temp.push_back(entity);

			std::this_thread::sleep_for(std::chrono::milliseconds(10));
		}

		entities.clear();
		entities = temp;


	}

}

// TODO: cache the world entities
void entities_loop()
{


	if (!settings::world::esp)
		return;

	uintptr_t entity_list = process.readv<uintptr_t>(client + offsets::dwEntityList);
	auto max_entities = process.readv<int>(entity_list + offsets::dwGameEntitySystem_getHighestEntityIndex);


	for (auto i = 65; i < max_entities; i++) {

		uintptr_t ent = process.readv<uintptr_t>(entity_list + 8LL * ((i & 0x7FFF) >> 9) + 16);
		if (!ent)
			continue;
		uintptr_t entbase = ent;

		ent = process.readv<uintptr_t>(ent + 120LL * (i & 0x1FF));
		if (!ent)
			continue;


		uintptr_t entitiy_identity = process.readv<uintptr_t>(ent + 0x10);
		if (!entitiy_identity)
			continue;

		uintptr_t designer_name = process.readv<uintptr_t>(entitiy_identity + 0x20);
		if (!designer_name)
			continue;

		std::string classname = process.read_str(designer_name);
#if _DEBUG

		LOG("CLASS_NAME: {}\n", classname.c_str());

#endif

		if (classname.find("_projectile") == std::string::npos && classname.find("weapon_") == std::string::npos)
			continue;


		auto node = process.readv<uintptr_t>(ent + 0x318);

		FVector3 abs_origin = process.readv<FVector3>(node + 0x80);

		if (abs_origin.isZero())
			continue;

		const char* nades[5] = { "smokegrenade_projectile","hegrenade_projectile","flashbang_projectile","molotov_projectile","flashbang_projectile" };


		float dist = abs_origin.distance(process.readv<FVector3>(global_pawn + offsets::m_vecOrigin)) / 100;

		view_matrix_t local_viewmatrix = process.readv<view_matrix_t>(client + offsets::dwViewMatrix);

		FVector3 screen_pos = abs_origin.world_to_screen(local_viewmatrix);

		if (screen_pos.z < 0.001f)
			continue;


		if (settings::world::weapon_esp && classname.find("weapon_") != std::string::npos) {


			if (settings::world::weapon_name)
				draw_text(classname.substr(7).c_str(), ImVec2(screen_pos.x, screen_pos.y), ImVec4(30, 0, 0, 60));

			if (settings::world::weapon_snaplines)
				draw_snaplines(screen_pos, ImVec4(255, 255, 255, 255));

			if (settings::world::weapon_distance)
				draw_distance(screen_pos, dist);
		}

		if (settings::world::grenade_esp && std::find(std::begin(nades), std::end(nades), classname) != std::end(nades)) {


			LOG("CLASS_NAME: {} ABS_ORIGIN: {} {} {}", classname.erase(classname.find("_projectile"), 11).c_str(), abs_origin.x, abs_origin.y, abs_origin.z);
			LOG("SMOKE_TICK: {}", process.readv<bool>(ent + 0x110C));

#ifdef _DEBUG
			ImGui::Begin(classname.c_str());

			ImGui::Text("X coordinate: %.2f", abs_origin.x);
			ImGui::Text("Y coordinate: %.2f", abs_origin.y);
			ImGui::Text("Z coordinate: %.2f", abs_origin.z);


			ImGui::End();
#endif // _DEBUG

			if (settings::world::grenade_name)
				draw_text(classname.erase(classname.find("_projectile"), 11).c_str(), ImVec2(screen_pos.x, screen_pos.y), ImVec4(137, 122, 0, 255));

			if (settings::world::grenade_snaplines)
				draw_snaplines(screen_pos, ImVec4(255, 255, 255, 255));

			if (settings::world::grenade_distance)
				draw_distance(screen_pos, dist);

			if (settings::world::grenade_trajectory) {
				FVector3 initial_pos = process.readv<FVector3>(ent + 0x10C0);
				draw_path(initial_pos.world_to_screen(local_viewmatrix), screen_pos);

			}


		}


	}
}


void entity_loop() {

	if (global_pawn) {

		entities_loop();

		view_matrix_t local_viewmatrix = process.readv<view_matrix_t>(client + offsets::dwViewMatrix);

		for (Entity& entity : entities) {
			FVector3 origin = process.readv<FVector3>(entity.pawn + offsets::m_vecOrigin);

			FVector3 head{ origin.x,origin.y,origin.z };

			FVector3 screen_pos = origin.world_to_screen(local_viewmatrix);

			if (screen_pos.z < 0.001f)
				continue;


			//CSkeletonInstance
			uintptr_t  p_gamescene = process.readv<uint64_t>(entity.pawn + 0x318);
			uintptr_t  p_bonearray = process.readv<uint64_t>(p_gamescene + 0x160 + 0x80); // m_modelState  + bArray

			FVector3 entity_pos = process.readv<FVector3>(entity.pawn + offsets::m_vecOrigin);

			FVector3 head_pos = FVector3(entity_pos.x, entity_pos.y, entity_pos.z + 63);

			FVector3 head_bone = process.readv<FVector3>(p_bonearray + EBone::Head * 32);


			if (!world_to_screen(head_bone, head_pos, local_viewmatrix))
				continue;

			if (screen_pos.z >= 0.01f)
				draw_esp(head_pos, screen_pos, entity, p_bonearray, local_viewmatrix);


			if (settings::aimbot::aim_fov > 0)
				ImGui::GetBackgroundDrawList()->AddCircle(ImVec2(width / 2, height / 2), settings::aimbot::aim_fov, ImColor(255, 255, 255, 255), 100);

			std::thread(aimbot, entity, head_pos).detach();

		}

	}

}