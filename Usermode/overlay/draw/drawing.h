#pragma once
#include "../../features/math.h"
#include "../../external/imgui/imgui_internal.h"
#include "../../utils/gun_icon.h"
#include "../../sdk/grenade_entity.h"

constexpr int MAX_NUM_SEGMENTS = 20;
constexpr float PI = 3.14159265;
constexpr int MAX_NUM_TRAIL = 50;



ImVec2 add(ImVec2 a, ImVec2 b) {
	return ImVec2(a.x + b.x, a.y + b.y);
}

ImVec2 subtract(ImVec2 a, ImVec2 b) {
	return ImVec2(a.x - b.x, a.y - b.y);
}

void draw_distance(ImVec2 pos, float distance) {
	std::string distance_str = std::to_string(static_cast<int32_t>(distance)) + "m";
	ImVec2 t_size = ImGui::CalcTextSize(distance_str.c_str());
	ImGui::GetBackgroundDrawList()->AddText(ImVec2(pos.x - t_size.x * 0.5f, pos.y - t_size.y * 0.5f + 7), IM_COL32_WHITE, distance_str.c_str());
}

void draw_text(const char* text, ImVec2 pos, ImColor color, float font_size = 13.0f) {
	ImFont* font = ImGui::GetIO().Fonts->Fonts[0];
	font->FontSize = font_size;
	ImVec2 TextSize = ImGui::CalcTextSize(text);

	ImVec2 text_pos = ImVec2(pos.x - TextSize.x * 0.5f, pos.y - TextSize.y * 0.5f);
	ImVec2 shadow_offset = ImVec2(1.0f, 1.0f);
	ImColor shadow_color = ImColor(0, 0, 0, 255);
	ImVec2 shadow_pos = ImVec2(text_pos.x + shadow_offset.x, text_pos.y + shadow_offset.y);

	ImGui::GetForegroundDrawList()->AddText(shadow_pos, shadow_color, text);

	ImGui::GetForegroundDrawList()->AddText(text_pos, color, text);
}

void draw_icon(ImFont* font, const char* text, FVector3 pos, ImColor color, float font_size = 13.0f) {

	ImVec2 text_size = ImGui::CalcTextSize(text);

	ImGui::GetForegroundDrawList()->AddText(font, font_size, ImVec2(pos.x - text_size.x / 2 + 1, pos.y - text_size.y / 2 + 1 + 5), ImColor(0, 0, 0, 255), gun_icon(text));
	ImGui::GetForegroundDrawList()->AddText(font, font_size, ImVec2(pos.x - text_size.x / 2, pos.y - text_size.y / 2 + 5), color, gun_icon(text));

}

void draw_icon_ex(ImFont* font, const char* text, FVector3 pos, ImColor color, float font_size = 13.0f) {

	ImVec2 text_size = ImGui::CalcTextSize(text);

	ImGui::GetForegroundDrawList()->AddText(font, font_size, ImVec2(pos.x - text_size.x / 2 + 1 + 10, pos.y - text_size.y / 2 + 1 + 5), ImColor(0, 0, 0, 255), gun_icon(text));
	ImGui::GetForegroundDrawList()->AddText(font, font_size, ImVec2(pos.x - text_size.x / 2 + 10, pos.y - text_size.y / 2 + 5), color, gun_icon(text));

}

void draw_grenade_esp(ImFont* font, const char* text, float distance, ImVec2 center, ImColor color, float font_size = 13.0f) {



	ImVec2 text_size = ImGui::CalcTextSize(text);


	if (settings::world::grenade_distance)
		draw_distance(center, distance);

	if (settings::world::grenade_name) {
		draw_text(strcmp(text, "smokegrenade") == 0 ? "smoke" : text, ImVec2(center.x, center.y - 5), color);
		return;
	}

	// we only want to draw grenade warning on molotov and hegrenade 
	const std::string grenade_warnings[2] = { "molotov", "hegrenade" };


	if (std::find(std::begin(grenade_warnings), std::end(grenade_warnings), text) != std::end(grenade_warnings)) {
		if (distance > 5 && distance < 10) {

			ImGui::GetBackgroundDrawList()->AddCircleFilled(center, 20.0f, IM_COL32(255, 201, 14, 100), MAX_NUM_SEGMENTS);
			ImGui::GetBackgroundDrawList()->AddCircle(center, 20.0f + 2.0f, IM_COL32(255, 255, 255, 255), MAX_NUM_SEGMENTS, 1.5f);
		}
		else if (distance < 5) {
			ImGui::GetBackgroundDrawList()->AddCircleFilled(center, 20.0f, IM_COL32(136, 0, 21, 100), MAX_NUM_SEGMENTS);
			ImGui::GetBackgroundDrawList()->AddCircle(center, 20.0f + 2.0f, IM_COL32(255, 255, 255, 255), MAX_NUM_SEGMENTS, 1.5f);
		}
		else {
			ImGui::GetBackgroundDrawList()->AddCircleFilled(center, 20.0f, IM_COL32(50, 50, 50, 100), MAX_NUM_SEGMENTS);
			ImGui::GetBackgroundDrawList()->AddCircle(center, 20.0f + 2.0f, IM_COL32(255, 255, 255, 255), MAX_NUM_SEGMENTS, 1.5f);
		}
	}

	ImGui::GetBackgroundDrawList()->AddCircleFilled(center, 20.0f, IM_COL32(50, 50, 50, 100), MAX_NUM_SEGMENTS);
	ImGui::GetBackgroundDrawList()->AddCircle(center, 20.0f + 2.0f, IM_COL32(255, 255, 255, 255), MAX_NUM_SEGMENTS, 1.5f);

	if (!strcmp(text, "smokegrenade")) {

		ImGui::GetForegroundDrawList()->AddText(font, font_size, ImVec2(center.x - text_size.x / 2 + 1 + 30, center.y - text_size.y / 2 + 1 - 10), ImColor(0, 0, 0, 255), gun_icon(text));
		ImGui::GetForegroundDrawList()->AddText(font, font_size, ImVec2(center.x - text_size.x / 2 + 30, center.y - text_size.y / 2 - 10), ImColor(255, 255, 255, 255), gun_icon(text));
	}
	else if (!strcmp(text, "molotov")) {
		ImGui::GetForegroundDrawList()->AddText(font, font_size, ImVec2(center.x - text_size.x / 2 + 1 + 15, center.y - text_size.y / 2 + 1 - 13), ImColor(0, 0, 0, 255), gun_icon(text));
		ImGui::GetForegroundDrawList()->AddText(font, font_size, ImVec2(center.x - text_size.x / 2 + 15, center.y - text_size.y / 2 - 13), color, gun_icon(text));

	}
	else {
		ImGui::GetForegroundDrawList()->AddText(font, font_size, ImVec2(center.x - text_size.x / 2 + 1 + 20, center.y - text_size.y / 2 + 1 - 13), ImColor(0, 0, 0, 255), gun_icon(text));
		ImGui::GetForegroundDrawList()->AddText(font, font_size, ImVec2(center.x - text_size.x / 2 + 20, center.y - text_size.y / 2 - 13), color, gun_icon(text));

	}

}


void draw_distance_a(FVector3 local_position, float distance, ImColor color = ImColor(255, 201, 14, 233)) {
	std::string distance_str = std::to_string(static_cast<int32_t>(distance)) + "m";
	ImVec2 text_size = ImGui::CalcTextSize(distance_str.c_str());

	draw_text(distance_str.c_str(), ImVec2(local_position.x, local_position.y + 20 - text_size.y / 2 + 5), color);

}

void draw_distance_ex(FVector3 local_position, float distance, ImColor color = ImColor(255, 201, 14, 233)) {
	std::string distance_str = std::to_string(static_cast<int32_t>(distance)) + "m";
	ImVec2 text_size = ImGui::CalcTextSize(distance_str.c_str());
	int gambeta = distance > 10 ? 15 : 20;

	draw_text(distance_str.c_str(), ImVec2(local_position.x, local_position.y + gambeta - text_size.y / 2 + 5), color, distance > 10 ? 18.0f : 14.5f);

}


void draw_filled_rect(int x, int y, int w, int h, ImVec4 color) {

	ImGui::GetForegroundDrawList()->AddRectFilled(ImVec2(x, y), ImVec2(x + w, y + h), ImGui::ColorConvertFloat4ToU32(color), 0, 0);
}


void draw_path(FVector3 current_pos, bool smoke_tick_begin) {
	if (smoke_tick_begin)
		return;

	static std::vector<FVector3> trail_positions;
	trail_positions.push_back(current_pos);

	for (size_t i = 1; i < trail_positions.size(); ++i) {
		ImVec2 p1 = ImVec2(trail_positions[i - 1].x, trail_positions[i - 1].y);
		ImVec2 p2 = ImVec2(trail_positions[i].x, trail_positions[i].y);
		ImGui::GetForegroundDrawList()->AddLine(p1, p2, IM_COL32(255, 255, 255, 255), 2.0f);
	}

	if (trail_positions.size() > MAX_NUM_SEGMENTS)
		trail_positions.erase(trail_positions.begin());


}

void draw_path(GrenadeEntity& grenade) {

	if (grenade.exploded())
		return;

	if (grenade.tick_began())
		return;


	static std::map<int, std::vector<FVector3>> grenade_trails;


	if (grenade_trails.find(grenade.idx) == grenade_trails.end()) {
		grenade_trails[grenade.idx] = std::vector<FVector3>();
	}

	grenade_trails[grenade.idx].push_back(grenade.get_current_position());

	std::vector<FVector3>& trail_positions = grenade_trails[grenade.idx];
	for (size_t i = 1; i < trail_positions.size(); ++i) {
		ImVec2 p1 = ImVec2(trail_positions[i - 1].x, trail_positions[i - 1].y);
		ImVec2 p2 = ImVec2(trail_positions[i].x, trail_positions[i].y);
		ImGui::GetForegroundDrawList()->AddLine(p1, p2, IM_COL32(255, 255, 255, 255), 2.0f);
	}

	if (trail_positions.size() > MAX_NUM_TRAIL)
		trail_positions.erase(trail_positions.begin());
}

void draw_filled_box(int x, int y, int w, int h, int border, ImColor border_color) {
	int shadow_offset = 1;
	ImVec4 shadow_color = ImVec4(0.2f, 0.2f, 0.2f, 0.5f);
	draw_filled_rect(x + shadow_offset, y + shadow_offset, w, h, shadow_color);


	draw_filled_rect(x, y, w, border, border_color); //top 
	draw_filled_rect(x, y, border, h, border_color); //left 
	draw_filled_rect(x + w - border, y, border, h, border_color); //right 
	draw_filled_rect(x, y + h - border, w, border, border_color); //bottom 
}

void draw_box_ex(FVector3 screen_pos, float height, float width, ImColor color) {

	ImGui::GetForegroundDrawList()->AddRect({ screen_pos.x - width / 2, screen_pos.y }, { screen_pos.x + width / 2, screen_pos.y + height }, color);
}

void draw_box(int x, int y, int w, int h, ImColor color) {

	ImGui::GetForegroundDrawList()->AddRect(ImVec2(x, y), ImVec2(x + w, y + h), color, 0.0f, 0, 1);
}




void draw_snaplines(FVector3 screen_pos, ImColor color) {
	// bottom -> foot
	ImGui::GetBackgroundDrawList()->AddLine({ screen_pos.x , screen_pos.y }, ImVec2(width / 2, height), color);

}

void draw_healthbar(FVector3 screen_pos, float health) {
	const auto color = ImColor(255 - (health * 2.55), health * 2.55, 0, 255);

	const auto clamped = std::clamp(health / 100.0f, 0.0f, 1.0f);
	ImGui::GetBackgroundDrawList()->AddRectFilled({ screen_pos.x - 5, screen_pos.y }, { screen_pos.x - 2, screen_pos.y + 2 }, ImColor(0, 0, 0, 255));
	ImGui::GetBackgroundDrawList()->AddRectFilled({ screen_pos.x - 5, screen_pos.y }, { screen_pos.x - 2 + (50 * clamped), screen_pos.y + 2 }, color);


}

void draw_rect(int x, int y, int w, int h, ImVec4 color, int thickness)
{
	ImGui::GetForegroundDrawList()->AddRect(ImVec2(x, y), ImVec2(x + w, y + h), ImGui::ColorConvertFloat4ToU32(color), 0, 0, thickness);
}

void draw_progressbar(int x, int y, int w, int h, int thick, int health)
{
	float dt = health / 100.0f;

	ImVec4 color = ImVec4(ImLerp(255.0f, 0.f, dt), ImLerp(0.f, (health > 50 ? 165.0f : 0.0f), dt), 0.0f, 200);


	std::string health_str = std::to_string(static_cast<int32_t>(health));

	ImVec2 text_size = ImGui::CalcTextSize(health_str.c_str());

	int health_h = (h * health) / 100;
	int bar_y = y + h - health_h;

	draw_filled_rect(x + (w / 2) - 25, bar_y, thick, health_h, color);

	if (health < 100)
		draw_text(health_str.c_str(), ImVec2(x + (w / 2) - 22, bar_y + 5), ImVec4(255, 255, 255, 255));
}

void draw_timer_progress(ImFont* font, float font_size, GrenadeEntity& grenade, ImColor color, int idx) {
	static float timers[32];
#ifdef _DEBUG
	ImGui::SetNextWindowSize(ImVec2(100.0f, 100.0f), ImGuiCond_Once);

	ImGui::Begin("Timers");
	ImGui::Text("Grenade idx %d", idx);
	ImGui::Text("Time %.1f", timers[idx]);
	ImGui::Text("TickBegin %s", grenade.tick_began() ? "Fade in" : "Fade out");
	ImGui::End();
#endif // _DEBUG

	if (grenade.get_current_position().invalid())
		return;

	if (!grenade.tick_began())
		return;

	float radius = 20.0f;
	float thickness = 2.0f;


	if (timers[grenade.idx] < 0.0f && std::isnan(timers[grenade.idx]) && std::isinf(timers[grenade.idx]))
		timers[grenade.idx] = 20.0f;
	else
		timers[grenade.idx] -= ImGui::GetIO().DeltaTime;

	ImVec2 center = ImVec2(grenade.get_current_position().x, grenade.get_current_position().y);

	ImGui::GetBackgroundDrawList()->AddCircleFilled(center, radius, IM_COL32(50, 50, 50, 100), MAX_NUM_SEGMENTS);

	float progress = timers[grenade.idx] / 20.0f;
	ImVec2 start(cosf(-PI * 0.5f), sinf(-PI * 0.5f));
	ImVec2 end(cosf(PI * 2.0f * progress - PI * 0.5f), sinf(PI * 2.0f * progress - PI * 0.5f));
	ImGui::GetBackgroundDrawList()->PathArcTo(grenade.center(), radius - thickness * 0.5f, PI * 0.5f, PI * 2.0f * progress + PI * 0.5f, MAX_NUM_SEGMENTS);
	ImGui::GetBackgroundDrawList()->PathStroke(IM_COL32(255, 0, 0, 255), false, thickness);


	if (settings::world::grenade_distance)
		draw_distance(center, grenade.get_distance());

	if (!settings::world::grenade_name) {
		ImVec2 text_size = ImGui::CalcTextSize(grenade.class_name.c_str());

		ImGui::GetForegroundDrawList()->AddText(font, font_size, ImVec2(center.x - text_size.x / 2 + 1 + 30, center.y - text_size.y / 2 + 1 - 10), ImColor(0, 0, 0, 255), gun_icon(grenade.class_name));
		ImGui::GetForegroundDrawList()->AddText(font, font_size, ImVec2(center.x - text_size.x / 2 + 30, center.y - text_size.y / 2 - 10), ImColor(255, 255, 255, 255), gun_icon(grenade.class_name));
	}



}

void draw_skeleton(PlayerEntity &entity) {

#if _DEBUG
	for (int i = 0; i < 32; i++) {
		FVector3 bone = process.readv<FVector3>(bonearray + i * 32).world_to_screen(view_matrix);
		FVector3 bone2 = process.readv<FVector3>(bonearray + (i + 1) * 32).world_to_screen(view_matrix);

		std::string number = std::to_string(i);
		ImVec2 TextSize = ImGui::CalcTextSize(number.c_str());
		ImGui::GetForegroundDrawList()->AddText(ImVec2(bone.x - TextSize.x / 2, bone.y - TextSize.y / 2), ImColor(255, 255, 255, 255), number.c_str());

	}
#else
	ImColor hidden_color = ImColor(255, 0, 0, 255);
	ImColor visible_color = ImColor(0, 255, 0, 255);

	FVector3 head = entity.get_bone_pos_2d(EBone::Head);
	FVector3 neck =  entity.get_bone_pos_2d(EBone::Neck);
	FVector3 right_shoulder =  entity.get_bone_pos_2d(EBone::RightShoulder);
	FVector3 left_shoulder =  entity.get_bone_pos_2d(EBone::LeftShoulder);
	FVector3 right_arm =  entity.get_bone_pos_2d(EBone::RightArm);
	FVector3 left_arm =  entity.get_bone_pos_2d(EBone::LeftArm);
	FVector3 right_hand =  entity.get_bone_pos_2d(EBone::RightHand);
	FVector3 left_hand =  entity.get_bone_pos_2d(EBone::LeftHand);
	FVector3 root =  entity.get_bone_pos_2d(EBone::Root);
	FVector3 right_knee =  entity.get_bone_pos_2d(EBone::RightKnee);
	FVector3 left_knee =  entity.get_bone_pos_2d(EBone::LeftKnee);
	FVector3 right_foot =  entity.get_bone_pos_2d(EBone::RightFoot);
	FVector3 left_foot =  entity.get_bone_pos_2d(EBone::LeftFoot);
	
	ImGui::GetBackgroundDrawList()->AddLine({ head.x, head.y }, { neck.x, neck.y }, entity.is_visible() ? visible_color : hidden_color);
	ImGui::GetBackgroundDrawList()->AddLine({ neck.x, neck.y }, { right_shoulder.x, right_shoulder.y }, entity.is_visible() ? visible_color : hidden_color);
	ImGui::GetBackgroundDrawList()->AddLine({ neck.x, neck.y }, { left_shoulder.x, left_shoulder.y }, entity.is_visible() ? visible_color : hidden_color);
	ImGui::GetBackgroundDrawList()->AddLine({ right_shoulder.x, right_shoulder.y }, { right_arm.x, right_arm.y }, entity.is_visible() ? visible_color : hidden_color);
	ImGui::GetBackgroundDrawList()->AddLine({ left_shoulder.x, left_shoulder.y }, { left_arm.x, left_arm.y }, entity.is_visible() ? visible_color : hidden_color);
	ImGui::GetBackgroundDrawList()->AddLine({ right_arm.x, right_arm.y }, { right_hand.x, right_hand.y }, entity.is_visible() ? visible_color : hidden_color);
	ImGui::GetBackgroundDrawList()->AddLine({ left_arm.x, left_arm.y }, { left_hand.x, left_hand.y }, entity.is_visible() ? visible_color : hidden_color);
	ImGui::GetBackgroundDrawList()->AddLine({ neck.x, neck.y }, { root.x, root.y }, entity.is_visible() ? visible_color : hidden_color);
	ImGui::GetBackgroundDrawList()->AddLine({ root.x, root.y }, { right_knee.x, right_knee.y }, entity.is_visible() ? visible_color : hidden_color);
	ImGui::GetBackgroundDrawList()->AddLine({ root.x, root.y }, { left_knee.x, left_knee.y }, entity.is_visible() ? visible_color : hidden_color);
	ImGui::GetBackgroundDrawList()->AddLine({ right_knee.x, right_knee.y }, { right_foot.x, right_foot.y }, entity.is_visible() ? visible_color : hidden_color);
	ImGui::GetBackgroundDrawList()->AddLine({ left_knee.x, left_knee.y }, { left_foot.x, left_foot.y }, entity.is_visible() ? visible_color : hidden_color);
#endif

};

