#pragma once
#include "../features/math.h"
#include <algorithm>

constexpr int MAX_NUM_SEGMENTS = 10;
constexpr float PI = 3.14159265;

ImVec2 add(ImVec2 a, ImVec2 b) {
	return ImVec2(a.x + b.x, a.y + b.y);
}

ImVec2 subtract(ImVec2 a, ImVec2 b) {
	return ImVec2(a.x - b.x, a.y - b.y);
}

void draw_text(const char* text, ImVec2 pos, ImColor color)
{

	ImVec2 TextSize = ImGui::CalcTextSize(text);
	ImGui::GetForegroundDrawList()->AddText(ImVec2(pos.x - TextSize.x / 2, pos.y - TextSize.y / 2), color, text);
	ImGui::GetForegroundDrawList()->AddText(ImVec2(pos.x - TextSize.x / 2 + 1, pos.y - TextSize.y / 2 + 1), ImColor(0, 0, 0, 200), text);
}

void draw_distance(FVector3 local_position, float distance)
{
	std::string distance_str = std::to_string(static_cast<int32_t>(distance)) + "m";
	ImVec2 text_size = ImGui::CalcTextSize(distance_str.c_str());

	draw_text(distance_str.c_str(), ImVec2(local_position.x, local_position.y + 20 - text_size.y / 2), ImVec4(100, 50, 50, 150));

}

void draw_filled_rect(int x, int y, int w, int h, ImVec4 color)
{
	ImGui::GetForegroundDrawList()->AddRectFilled(ImVec2(x, y), ImVec2(x + w, y + h), ImGui::ColorConvertFloat4ToU32(color), 0, 0);
}


void draw_path(FVector3 initial_pos, FVector3 current_pos,bool spawned)
{
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



void draw_box(int x, int y, int w, int h, int border, ImVec4 color)
{
	draw_filled_rect(x + border, y, w, border, color); //top 
	draw_filled_rect(x + w - w + border, y, w, border, color); //top 
	draw_filled_rect(x, y, border, h, color); //left 
	draw_filled_rect(x, y + h - h + border * 2, border, h, color); //left 
	draw_filled_rect(x + border, y + h + border, w, border, color); //bottom 
	draw_filled_rect(x + w - w + border, y + h + border, w, border, color); //bottom 
	draw_filled_rect(x + w + border, y, border, h, color);//right 
	draw_filled_rect(x + w + border, y + h - h + border * 2, border, h, color);//right 
}

void draw_box(FVector3 screen_pos, float height, float width, ImColor color)
{
	ImGui::GetForegroundDrawList()->AddRect({ screen_pos.x - width / 2, screen_pos.y }, { screen_pos.x + width / 2, screen_pos.y + height }, color);
}

void draw_rect(int x, int y, int w, int h, ImColor color)
{
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

	float G = (255 * health / 100);
	float R = 255 - G;
	ImVec4 colore = { R, G, 0, 200 };
	std::string health_str = std::to_string(static_cast<int32_t>(health));

	ImVec2 text_size = ImGui::CalcTextSize(health_str.c_str());

	draw_filled_rect(x + (w / 2) - 25, y, thick, (h)*health / 100, color);
	if (health < 100)
		draw_text(health_str.c_str(), ImVec2(x + (w / 2) - 25, y + 5), ImVec4(255, 255, 255, 255));

}

void draw_timer_progress(bool tick_begin, const ImVec2& center, ImVec4 color, int idx) {
    static float timers[32] = {20.0f}; 

    if (!tick_begin)
        return;

    float radius = 20.0f;
    float thickness = 2.0f;

    ImGui::GetBackgroundDrawList()->AddCircleFilled(center, radius, IM_COL32(50, 50, 50, 100), MAX_NUM_SEGMENTS);

    if (tick_begin)
        timers[idx] -= ImGui::GetIO().DeltaTime;

    if (timers[idx] < 0.0f) {
        timers[idx] = 20.0f;
    }

    float progress = timers[idx] / 20.0f;
    ImVec2 start(cosf(-PI * 0.5f), sinf(-PI * 0.5f));
    ImVec2 end(cosf(PI * 2.0f * progress - PI * 0.5f), sinf(PI * 2.0f * progress - PI * 0.5f));
    ImGui::GetBackgroundDrawList()->PathArcTo(center, radius - thickness * 0.5f, PI * 0.5f, PI * 2.0f * progress + PI * 0.5f, MAX_NUM_SEGMENTS);
    ImGui::GetBackgroundDrawList()->PathStroke(IM_COL32(255, 0, 0, 255), false, thickness);

    char label[32];
    snprintf(label, sizeof(label), "%.1f", timers[idx]);
    ImVec2 textSize = ImGui::CalcTextSize(label);
    ImGui::GetBackgroundDrawList()->AddText(ImVec2(center.x - textSize.x * 0.5f, center.y - textSize.y * 0.5f), IM_COL32_WHITE, label);
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

