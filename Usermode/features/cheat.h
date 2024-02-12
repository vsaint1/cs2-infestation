#pragma once
#include "globals.h"
#include "../sdk/player/player_entity.h"
#include "../memory/memory.h"
#include <thread>
#include "esp/esp.h"

void cache_entities() {
	while (true) {
		std::vector<PlayerEntity> temp;
		uintptr_t local_player = process.readv<uintptr_t>(client + offsets::dwLocalPlayerPawn);

		if (!local_player)
			continue;

		global_pawn = local_player;

		FVector3 local_pos = process.readv<FVector3>(local_player + offsets::C_BasePlayerPawn::m_vOldOrigin);

		int local_index = 1;

		int local_team = process.readv<int>(local_player + offsets::C_BaseEntity::m_iTeamNum);


		uintptr_t entity_list = process.readv<uintptr_t>(client + offsets::dwEntityList);

		for (int i = 1; i < 32; i++) {
			uintptr_t list_entry = process.readv<uintptr_t>(entity_list + (8 * (i & 0x7FFF) >> 9) + 16);
			if (!list_entry)
				continue;

			uintptr_t player = process.readv<uintptr_t>(list_entry + 120 * (i & 0x1FF));

			if (!player)
				continue;

			std::uint32_t h_pawn = process.readv<std::uint32_t>(player + offsets::CCSPlayerController::m_hPlayerPawn);

			uintptr_t list_entry2 = process.readv<uintptr_t>(entity_list + 0x8 * ((h_pawn & 0x7FFF) >> 9) + 16);

			if (!list_entry2)
				continue;

			uintptr_t pcs_pawn = process.readv<uintptr_t>(list_entry2 + 120 * (h_pawn & 0x1FF));

			if (PlayerEntity::is_localplayer(pcs_pawn,local_player)) {
				local_index = i;
				continue;
			}

			FVector3 e_position = process.readv<FVector3>(pcs_pawn + offsets::C_BasePlayerPawn::m_vOldOrigin);

			int e_health = process.readv<int>(pcs_pawn + offsets::C_BaseEntity::m_iHealth);


			if (PlayerEntity::is_dead(e_health))
				continue;

			int e_team = process.readv<int>(pcs_pawn + offsets::C_BaseEntity::m_iTeamNum);

			if (settings::misc::bTeamcheck && PlayerEntity::is_team_mate(local_team,e_team))
				continue;

			auto m_pclippingweapon = process.readv<uintptr_t>(pcs_pawn + offsets::C_CSPlayerPawnBase::m_pClippingWeapon);
			auto entity_identity = process.readv<uintptr_t>(m_pclippingweapon + offsets::CEntityInstance::m_pEntity);
			auto des_name = process.readv<uintptr_t>(entity_identity + offsets::CEntityIdentity::m_designerName);
	
			std::string weap_name = process.read_str(des_name);

			std::string e_name = process.read_str(pcs_pawn + offsets::CBasePlayerController::m_iszPlayerName);
			bool e_spotted = process.readv<bool>(pcs_pawn + offsets::C_CSPlayerPawn::m_entitySpottedState + offsets::EntitySpottedState_t::m_bSpottedByMask);

			PlayerEntity entity;
			entity.set_pawn(pcs_pawn);
			entity.set_is_visible(e_spotted, local_index);
			entity.set_health(e_health);
			entity.set_weapon(weap_name);
			entity.set_player_name(e_name);
			entity.set_distance(local_pos,e_position);
			temp.push_back(entity);

			std::this_thread::sleep_for(std::chrono::milliseconds(settings::misc::sleep_for_ms));
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

		ent = process.readv<uintptr_t>(ent + 120LL * (i & 0x1FF));

		if (!ent)
			continue;

		uintptr_t entitiy_identity = process.readv<uintptr_t>(ent + offsets::CEntityInstance::m_pEntity);

		if (!entitiy_identity)
			continue;

		uintptr_t designer_name = process.readv<uintptr_t>(entitiy_identity + offsets::CEntityIdentity::m_designerName);
		if (!designer_name)
			continue;

		std::string classname = process.read_str(designer_name);

		if (classname.empty())
			continue;

#if _DEBUG

		LOG("CLASS_NAME: %s\n", classname.c_str());

#endif

		if (classname.find("_projectile") == std::string::npos && classname.find("weapon_") == std::string::npos)
			continue;


		auto node = process.readv<uintptr_t>(ent + offsets::C_BaseEntity::m_pGameSceneNode);

		FVector3 abs_origin = process.readv<FVector3>(node + offsets::CGameSceneNode::m_vecOrigin);

		if (abs_origin.isZero())
			continue;


		const char* nades[5] = { "smokegrenade_projectile","hegrenade_projectile","flashbang_projectile","molotov_projectile","flashbang_projectile" };


		float dist = abs_origin.distance(process.readv<FVector3>(global_pawn + offsets::C_BasePlayerPawn::m_vOldOrigin)) / 100;

		ViewMatrix local_viewmatrix = process.readv<ViewMatrix>(client + offsets::dwViewMatrix);

		FVector3 screen_pos = abs_origin.world_to_screen(local_viewmatrix);

		if (screen_pos.z < 0.001f)
			continue;


		if (settings::world::weapon_esp && classname.find("weapon_") != std::string::npos) {


			if (settings::world::weapon_name)
				draw_icon(ImGui::GetIO().Fonts->Fonts[1], classname.substr(7).c_str(), screen_pos, ImColor(255, 255, 255, 255), 14.0f);

			if (settings::world::weapon_snaplines)
				draw_snaplines(screen_pos, ImVec4(255, 255, 255, 255));

			if (settings::world::weapon_distance)
				draw_distance_a(screen_pos, dist, ImColor(195, 195, 195, 255));
		}

		if (settings::world::grenade_esp && std::find(std::begin(nades), std::end(nades), classname) != std::end(nades)) {

			auto normalized_str = classname.erase(classname.find("_projectile"), 11).c_str();
			LOG("CLASS_NAME: %s ABS_ORIGIN: %.2f %.2f %.2f", normalized_str, abs_origin.x, abs_origin.y, abs_origin.z);


#ifdef _DEBUG
			ImGui::SetNextWindowSize(ImVec2(200.0f, 100.0f));

			ImGui::Begin(classname.c_str());

			ImGui::Text("X coordinate: %.2f", abs_origin.x);
			ImGui::Text("Y coordinate: %.2f", abs_origin.y);
			ImGui::Text("Z coordinate: %.2f", abs_origin.z);

			ImGui::End();
#endif // _DEBUG

			auto smoke_tick_begin = process.readv<bool>(ent + offsets::C_SmokeGrenadeProjectile::m_nSmokeEffectTickBegin);

			if (settings::world::grenade_esp)
				draw_grenade_esp(ImGui::GetIO().Fonts->Fonts[1], normalized_str, dist, ImVec2(screen_pos.x, screen_pos.y), ImColor(255, 255, 255, 255), 20.0f);
				

			if (settings::world::grenade_snaplines)
				draw_snaplines(screen_pos, ImVec4(255, 255, 255, 255));


			if (settings::world::grenade_trajectory)
				draw_path(process.readv<FVector3>(ent + offsets::C_BaseCSGrenadeProjectile::m_vInitialPosition).world_to_screen(local_viewmatrix), screen_pos, smoke_tick_begin);


			if (settings::world::grenade_timer && classname.compare("smokegrenade") == 0)
				draw_timer_progress(ImGui::GetIO().Fonts->Fonts[1], 20.0f, "smokegrenade", smoke_tick_begin, dist, ImVec2(screen_pos.x, screen_pos.y), ImVec4(255, 0, 0, 255), i);



		}

	}


}


void entity_loop() {

	if (global_pawn) {

		entities_loop();

		ViewMatrix local_viewmatrix = process.readv<ViewMatrix>(client + offsets::dwViewMatrix);

		for (PlayerEntity& entity : entities) {
			FVector3 origin = process.readv<FVector3>(entity.pawn + offsets::C_BasePlayerPawn::m_vOldOrigin);

			FVector3 head{ origin.x,origin.y,origin.z };

			FVector3 screen_pos = origin.world_to_screen(local_viewmatrix);

			if (screen_pos.z < 0.001f)
				continue;


			//CSkeletonInstance
			uintptr_t  p_gamescene = process.readv<uint64_t>(entity.pawn + 0x318);
			uintptr_t  p_bonearray = process.readv<uint64_t>(p_gamescene + 0x160 + 0x80); // m_modelState  + bArray

			FVector3 entity_pos = process.readv<FVector3>(entity.pawn + offsets::C_BasePlayerPawn::m_vOldOrigin);

			FVector3 head_bone = process.readv<FVector3>(p_bonearray + EBone::Head * 32).world_to_screen(local_viewmatrix);

			if (screen_pos.z >= 0.01f)
				draw_esp(head_bone, screen_pos, entity, p_bonearray, local_viewmatrix);


			if (settings::aimbot::aim_fov > 0)
				ImGui::GetBackgroundDrawList()->AddCircle(ImVec2(width / 2, height / 2), settings::aimbot::aim_fov, ImColor(255, 255, 255, 255), 100);

			std::thread(aimbot, entity, head_bone).detach();
		}

	}

}