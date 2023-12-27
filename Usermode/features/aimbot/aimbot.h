#pragma once
#include "../globals.h"
#include "../math.h"




void aimbot(Entity entity, FVector3 head_bone) {

	float closest_pawn = FLT_MAX;

	auto dx = head_bone.x - (width / 2);
	auto dy = head_bone.y - (height / 2);
	auto dist = sqrtf(dx * dx + dy * dy);


	if (settings::aimbot::aimbot) {

		if (settings::bMenu)
			return;

		if (settings::aimbot::visible_check && !entity.visible)
			return;

		if (GetAsyncKeyState(hotkeys::aimkey)) {

			if (settings::aimbot::smooth > 0) {
				dx = dx / (rand() % settings::aimbot::smooth + 1);
				dy = dy / (rand() % settings::aimbot::smooth + 1);
			}

			if (dist < closest_pawn) {

				closest_pawn = dist;

				if (closest_pawn > settings::aimbot::aim_fov)
					return;


				if (entity.health <= 0)
					return;

				// todo: calculate with bone to be more accurate
				if (settings::aimbot::selectedhitbox == 0)
					dx, dy;

				if (settings::aimbot::selectedhitbox == 1)
					dy = dy + 20;



				mouse_event(MOUSEEVENTF_MOVE, dx, dy, NULL, NULL); // using default mouse_event
				//driver.move(dx, dy, MOUSEEVENTF_MOVE); // using driver mouse_event

			}
		}
	}
}

