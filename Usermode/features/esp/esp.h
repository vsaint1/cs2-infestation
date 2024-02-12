#pragma once

//#include "../../memory/driver.h" // if you want to use the driver very easy to change
#include "../math.h"
#include "../../overlay/draw/drawing.h"
#include "../cheat.h"
#include "../aimbot/aimbot.h"



void draw_esp(FVector3 head_pos, FVector3 screen_pos, PlayerEntity entity, uintptr_t  bone_array, ViewMatrix view_matrix) {
	if (global_pawn) {

		if (settings::visuals::esp) {

			float height = abs(screen_pos.y - head_pos.y);
			float width = height / 2.0f;


			if (settings::visuals::bBox)
				draw_filled_box(screen_pos.x - (width / 2) - 5, head_pos.y - 1, width, height, 1,settings::colors::player_box);

			if (settings::visuals::bName)
				draw_text(entity.name.c_str(), ImVec2(head_pos.x, head_pos.y - 10), settings::colors::player_name, 14.5f);

			if (settings::visuals::distance)
				draw_distance_ex(screen_pos, entity.get_distance(),settings::colors::player_distance);

			if (settings::visuals::bSnaplines)
				draw_snaplines(screen_pos, settings::colors::player_snaplines);

			if (settings::visuals::bHealth)
				draw_progressbar(screen_pos.x + 25, head_pos.y, width, height, 2, entity.health);

			if (settings::visuals::bSkeleton)
				draw_skeleton(bone_array, view_matrix, entity.is_visible());

			if (settings::visuals::bWeapon)
				draw_icon_ex(ImGui::GetIO().Fonts->Fonts[1], entity.weapon_name.c_str(), {screen_pos.x - 10,screen_pos.y,screen_pos.z}, ImColor(255, 255, 255, 255), entity.get_distance() > 10 ? 8.0f : 13.0f);

			// flags
			//draw_text(entity.name.c_str(), ImVec2(screen_pos.x - width / 2 , head_pos.y - 10), ImVec4(255, 243, 247, 255));

		}


	}

	if (settings::misc::bWatermark)
		draw_text("[CODE] - https://github.com/vsaint1/cs2-infestation", ImVec2(200, 10), ImColor(255, 255, 255, 255), 13.0f);

}
