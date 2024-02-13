#pragma once
#include "../globals.h"
#include "../math.h"

EBone select_bone(int& hit_box, int health) {

    switch (hit_box) {
        case 0:
            return EBone::Head;
        case 1:
            return EBone::Neck;
        case 2:
            return EBone::Chest;
        default:
            if (health > 70)
                return EBone::Head;
            else if (health > 40 && health < 70)
                return EBone::Neck;
            else
                return EBone::Chest;
    }

}


std::pair<float, float> calc_bone(PlayerEntity& entity, int& hit_box) {


	auto dx = entity.get_bone_pos_2d(select_bone(hit_box,entity.health)).x - (width / 2);
	auto dy = entity.get_bone_pos_2d(select_bone(hit_box,entity.health)).y - (height / 2);

	return { dx,dy };
}


void aimbot(PlayerEntity entity) {

	float closest_pawn = FLT_MAX;


	if (settings::aimbot::aimbot) {

		if (settings::bMenu)
			return;

		if (settings::aimbot::visible_check && !entity.is_visible())
			return;

		if (GetAsyncKeyState(hotkeys::aimkey)) {

			auto [dx, dy] = calc_bone(entity, settings::aimbot::selectedhitbox);
			auto dist = sqrtf(dx * dx + dy * dy);


			if (dist < closest_pawn) {

				closest_pawn = dist;

				if (closest_pawn > settings::aimbot::aim_fov)
					return;


				if (entity.is_dead(entity.health))
					return;


				if (settings::aimbot::smooth > 0) {
					dx = dx / (rand() % settings::aimbot::smooth + 1);
					dy = dy / (rand() % settings::aimbot::smooth + 1);
				}


				mouse_event(MOUSEEVENTF_MOVE, dx, dy, NULL, NULL); // using default mouse_event
				//driver.move(dx, dy, MOUSEEVENTF_MOVE); // using driver mouse_event

			}
		}
	}
}