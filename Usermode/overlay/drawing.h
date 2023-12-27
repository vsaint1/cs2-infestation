#pragma once
#include "../features/math.h"
#include <algorithm>


void draw_distance(FVector3 local_position, float distance)
{
	std::string distance_str = std::to_string(static_cast<int32_t>(distance)) + "m";
	ImVec2 TextSize = ImGui::CalcTextSize(distance_str.c_str());
	ImGui::GetForegroundDrawList()->AddText(ImVec2(local_position.x - TextSize.x / 2, local_position.y - TextSize.y / 2 + 10), ImColor(255, 255, 255, 255), distance_str.c_str());

}

void draw_box(FVector3 screen_pos, float height, float width, ImColor color)
{
	ImGui::GetForegroundDrawList()->AddRect({ screen_pos.x - width / 2, screen_pos.y }, { screen_pos.x + width / 2, screen_pos.y + height }, color);
}

void draw_rect(int x, int y, int w, int h, ImColor color, int thickness)
{
	ImGui::GetForegroundDrawList()->AddRect(ImVec2(x, y), ImVec2(x + w, y + h), color , 0.0f, 0, thickness);
}


void draw_text(const char* text, ImVec2 pos, ImColor color)
{
	ImVec2 TextSize = ImGui::CalcTextSize(text);
	ImGui::GetForegroundDrawList()->AddText(ImVec2(pos.x - TextSize.x / 2, pos.y - TextSize.y / 2), color, text);
}

void draw_snapline(FVector3 screen_pos, ImColor color) {
	ImGui::GetBackgroundDrawList()->AddLine({ screen_pos.x , screen_pos.y }, ImVec2(width / 2, height), color);

}

void draw_healthbar(FVector3 screen_pos, float health) {
	const auto color = ImColor(255 - (health * 2.55), health * 2.55, 0, 255);

	const auto clamped = std::clamp(health / 100.0f, 0.0f, 1.0f);
	ImGui::GetBackgroundDrawList()->AddRectFilled({ screen_pos.x - 5, screen_pos.y }, { screen_pos.x - 2, screen_pos.y + 2 }, ImColor(0, 0, 0, 255));
	ImGui::GetBackgroundDrawList()->AddRectFilled({ screen_pos.x - 5, screen_pos.y }, { screen_pos.x - 2 + (50 * clamped), screen_pos.y + 2 }, color);


}

void draw_skeleton(uintptr_t bonearray, view_matrix_t view_matrix) {

#if _DEBUG
	for (int i = 0; i < 32; i++) {
		FVector3 bone = process.readv<FVector3>(bonearray + i * 32).world_to_screen(view_matrix);
		FVector3 bone2 = process.readv<FVector3>(bonearray + (i + 1) * 32).world_to_screen(view_matrix);

		std::string number = std::to_string(i);
		ImVec2 TextSize = ImGui::CalcTextSize(number.c_str());
		ImGui::GetForegroundDrawList()->AddText(ImVec2(bone.x - TextSize.x / 2, bone.y - TextSize.y / 2), ImColor(255, 255, 255, 255), number.c_str());

	}
#else
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

	ImGui::GetBackgroundDrawList()->AddLine({ head.x, head.y }, { neck.x, neck.y }, ImColor(255, 0, 0, 255));
	ImGui::GetBackgroundDrawList()->AddLine({ neck.x, neck.y }, { right_shoulder.x, right_shoulder.y }, ImColor(255, 0, 0, 255));
	ImGui::GetBackgroundDrawList()->AddLine({ neck.x, neck.y }, { left_shoulder.x, left_shoulder.y }, ImColor(255, 0, 0, 255));
	ImGui::GetBackgroundDrawList()->AddLine({ right_shoulder.x, right_shoulder.y }, { right_arm.x, right_arm.y }, ImColor(255, 0, 0, 255));
	ImGui::GetBackgroundDrawList()->AddLine({ left_shoulder.x, left_shoulder.y }, { left_arm.x, left_arm.y }, ImColor(255, 0, 0, 255));
	ImGui::GetBackgroundDrawList()->AddLine({ right_arm.x, right_arm.y }, { right_hand.x, right_hand.y }, ImColor(255, 0, 0, 255));
	ImGui::GetBackgroundDrawList()->AddLine({ left_arm.x, left_arm.y }, { left_hand.x, left_hand.y }, ImColor(255, 0, 0, 255));
	ImGui::GetBackgroundDrawList()->AddLine({ neck.x, neck.y }, { root.x, root.y }, ImColor(255, 0, 0, 255));
	ImGui::GetBackgroundDrawList()->AddLine({ root.x, root.y }, { right_knee.x, right_knee.y }, ImColor(255, 0, 0, 255));
	ImGui::GetBackgroundDrawList()->AddLine({ root.x, root.y }, { left_knee.x, left_knee.y }, ImColor(255, 0, 0, 255));
	ImGui::GetBackgroundDrawList()->AddLine({ right_knee.x, right_knee.y }, { right_foot.x, right_foot.y }, ImColor(255, 0, 0, 255));
	ImGui::GetBackgroundDrawList()->AddLine({ left_knee.x, left_knee.y }, { left_foot.x, left_foot.y }, ImColor(255, 0, 0, 255));
#endif

};