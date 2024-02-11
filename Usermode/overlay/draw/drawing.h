#pragma once
#include "../../features/math.h"
#include "../../external/imgui/imgui_internal.h"
#include "../../utils/gun_icon.h"

constexpr int MAX_NUM_SEGMENTS = 20;
constexpr float PI = 3.14159265;



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



	if (settings::world::grenade_distance)
		draw_distance(center, distance);


	ImVec2 text_size = ImGui::CalcTextSize(text);
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

	draw_text(distance_str.c_str(), ImVec2(local_position.x, local_position.y + gambeta - text_size.y / 2 + 5), color, distance > 10 ? 18.0f: 14.5f   );

}


void draw_filled_rect(int x, int y, int w, int h, ImVec4 color) {

	ImGui::GetForegroundDrawList()->AddRectFilled(ImVec2(x, y), ImVec2(x + w, y + h), ImGui::ColorConvertFloat4ToU32(color), 0, 0);
}


void draw_path(FVector3 initial_pos, FVector3 current_pos, bool spawned) {

	static std::vector<FVector3> previous_positions;

	if (spawned)
		return;


	previous_positions.push_back(current_pos);

	float distance = std::hypot(current_pos.x - initial_pos.x, current_pos.y - initial_pos.y);

	int num_segments = static_cast<int>(distance / 10.0f);

	float alpha_decay_rate = 255.0f / static_cast<float>(num_segments);

	float alpha = 255.0f;

	for (int i = 0; i < num_segments; ++i) {
		float t = static_cast<float>(i) / num_segments;
		ImVec2 p1 = ImVec2(initial_pos.x * (1 - t) + current_pos.x * t, initial_pos.y * (1 - t) + current_pos.y * t);
		t = static_cast<float>(i + 1) / num_segments;
		ImVec2 p2 = ImVec2(initial_pos.x * (1 - t) + current_pos.x * t, initial_pos.y * (1 - t) + current_pos.y * t);

		alpha -= alpha_decay_rate;
		if (alpha < 0.0f) alpha = 0.0f;

		ImGui::GetForegroundDrawList()->AddLine(p1, p2, IM_COL32(255, 255, 255, static_cast<int>(alpha)), 2.0f);
	}

	if (previous_positions.size() > MAX_NUM_SEGMENTS)
		previous_positions.erase(previous_positions.begin(), previous_positions.end() - MAX_NUM_SEGMENTS);
}



void draw_filled_box(int x, int y, int w, int h, int border, ImVec4 border_color) {
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

void draw_timer_progress(ImFont* font, float font_size, const char* name, bool tick_begin, float distance, const ImVec2& center, ImVec4 color, int idx) {
	static float timers[32];
#ifdef _DEBUG
	ImGui::SetNextWindowSize(ImVec2(100.0f, 100.0f), ImGuiCond_Once);

	ImGui::Begin("Timers");
	ImGui::Text("Grenade idx %d", idx);
	ImGui::Text("Time %.1f", timers[idx]);
	ImGui::Text("TickBegin %s", tick_begin ? "Fade in" : "Fade out");
	ImGui::End();
#endif // _DEBUG

	if (!tick_begin)
		return;

	float radius = 20.0f;
	float thickness = 2.0f;


	if (timers[idx] < 0.0f)
		timers[idx] = 20.0f;

	timers[idx] -= ImGui::GetIO().DeltaTime;

	ImGui::GetBackgroundDrawList()->AddCircleFilled(center, radius, IM_COL32(50, 50, 50, 100), MAX_NUM_SEGMENTS);

	float progress = timers[idx] / 20.0f;
	ImVec2 start(cosf(-PI * 0.5f), sinf(-PI * 0.5f));
	ImVec2 end(cosf(PI * 2.0f * progress - PI * 0.5f), sinf(PI * 2.0f * progress - PI * 0.5f));
	ImGui::GetBackgroundDrawList()->PathArcTo(center, radius - thickness * 0.5f, PI * 0.5f, PI * 2.0f * progress + PI * 0.5f, MAX_NUM_SEGMENTS);
	ImGui::GetBackgroundDrawList()->PathStroke(IM_COL32(255, 0, 0, 255), false, thickness);


	if (settings::world::grenade_distance)
		draw_distance(center, distance);

	ImVec2 text_size = ImGui::CalcTextSize(name);

	ImGui::GetForegroundDrawList()->AddText(font, font_size, ImVec2(center.x - text_size.x / 2 + 1 + 30, center.y - text_size.y / 2 + 1 - 10), ImColor(0, 0, 0, 255), gun_icon(name));
	ImGui::GetForegroundDrawList()->AddText(font, font_size, ImVec2(center.x - text_size.x / 2 + 30, center.y - text_size.y / 2 - 10), ImColor(255, 255, 255, 255), gun_icon(name));



}

void draw_skeleton(uintptr_t bonearray, view_matrix_t view_matrix, bool visible) {

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

	FVector3 head = process.readv<FVector3>(bonearray + EBone::Head * 32).world_to_screen(view_matrix);
	FVector3 neck = process.readv<FVector3>(bonearray + EBone::Neck * 32).world_to_screen(view_matrix);
	FVector3 right_shoulder = process.readv<FVector3>(bonearray + EBone::RightShoulder * 32).world_to_screen(view_matrix);
	FVector3 left_shoulder = process.readv<FVector3>(bonearray + EBone::LeftShoulder * 32).world_to_screen(view_matrix);
	FVector3 right_arm = process.readv<FVector3>(bonearray + EBone::RightArm * 32).world_to_screen(view_matrix);
	FVector3 left_arm = process.readv<FVector3>(bonearray + EBone::LeftArm * 32).world_to_screen(view_matrix);
	FVector3 right_hand = process.readv<FVector3>(bonearray + EBone::RightHand * 32).world_to_screen(view_matrix);
	FVector3 left_hand = process.readv<FVector3>(bonearray + EBone::LeftHand * 32).world_to_screen(view_matrix);
	FVector3 root = process.readv<FVector3>(bonearray + EBone::Root * 32).world_to_screen(view_matrix);
	FVector3 right_knee = process.readv<FVector3>(bonearray + EBone::RightKnee * 32).world_to_screen(view_matrix);
	FVector3 left_knee = process.readv<FVector3>(bonearray + EBone::LeftKnee * 32).world_to_screen(view_matrix);
	FVector3 right_foot = process.readv<FVector3>(bonearray + EBone::RightFoot * 32).world_to_screen(view_matrix);
	FVector3 left_foot = process.readv<FVector3>(bonearray + EBone::LeftFoot * 32).world_to_screen(view_matrix);

	ImGui::GetBackgroundDrawList()->AddLine({ head.x, head.y }, { neck.x, neck.y }, visible ? visible_color : hidden_color);
	ImGui::GetBackgroundDrawList()->AddLine({ neck.x, neck.y }, { right_shoulder.x, right_shoulder.y }, visible ? visible_color : hidden_color);
	ImGui::GetBackgroundDrawList()->AddLine({ neck.x, neck.y }, { left_shoulder.x, left_shoulder.y }, visible ? visible_color : hidden_color);
	ImGui::GetBackgroundDrawList()->AddLine({ right_shoulder.x, right_shoulder.y }, { right_arm.x, right_arm.y }, visible ? visible_color : hidden_color);
	ImGui::GetBackgroundDrawList()->AddLine({ left_shoulder.x, left_shoulder.y }, { left_arm.x, left_arm.y }, visible ? visible_color : hidden_color);
	ImGui::GetBackgroundDrawList()->AddLine({ right_arm.x, right_arm.y }, { right_hand.x, right_hand.y }, visible ? visible_color : hidden_color);
	ImGui::GetBackgroundDrawList()->AddLine({ left_arm.x, left_arm.y }, { left_hand.x, left_hand.y }, visible ? visible_color : hidden_color);
	ImGui::GetBackgroundDrawList()->AddLine({ neck.x, neck.y }, { root.x, root.y }, visible ? visible_color : hidden_color);
	ImGui::GetBackgroundDrawList()->AddLine({ root.x, root.y }, { right_knee.x, right_knee.y }, visible ? visible_color : hidden_color);
	ImGui::GetBackgroundDrawList()->AddLine({ root.x, root.y }, { left_knee.x, left_knee.y }, visible ? visible_color : hidden_color);
	ImGui::GetBackgroundDrawList()->AddLine({ right_knee.x, right_knee.y }, { right_foot.x, right_foot.y }, visible ? visible_color : hidden_color);
	ImGui::GetBackgroundDrawList()->AddLine({ left_knee.x, left_knee.y }, { left_foot.x, left_foot.y }, visible ? visible_color : hidden_color);
#endif

};
