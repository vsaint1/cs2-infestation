#pragma once

//#include "../../memory/driver.h" // if you want to use the driver very easy to change
#include "../math.h"
#include "../../overlay/drawing.h"
#include "../cheat.h"
#include "../aimbot/aimbot.h"



void draw_esp(FVector3 head_pos, FVector3 screen_pos, Entity entity, uintptr_t  bone_array, view_matrix_t view_matrix) {
	if (global_pawn) {

		if (settings::visuals::esp) {

			float height = abs(screen_pos.y - head_pos.y);
			float width = height / 2.0f;

			if (settings::visuals::bBox)
				draw_box(head_pos.x - 30, head_pos.y, width, height,1, ImVec4(255, 255, 255, 255));

			if (settings::visuals::distance)
				draw_distance(screen_pos, entity.position);

			if (settings::visuals::bSnaplines)
				draw_snaplines(screen_pos, ImColor(255, 255, 255, 255));

			if (settings::visuals::bHealth)
				draw_progressbar(screen_pos.x + 30, head_pos.y, width, height, 2, entity.health);

			if (settings::visuals::bSkeleton)
				draw_skeleton(bone_array, view_matrix, entity.visible);
		}


	}

	if (settings::misc::bWatermark)
		draw_text("[CODE] - https://github.com/vsaint1/cs2-infestation", ImVec2(200, 10), ImColor(255, 255, 255, 255));

}
