/*
 *   Copyright (c) 2024 vsantos1
 *   All rights reserved.
 */
#include "drawing.hpp"

void draw::text(const char *text, ImVec2 pos, ImColor color, float font_size) {
  ImFont *font = ImGui::GetIO().Fonts->Fonts[0];
  font->FontSize = font_size;
  ImVec2 TextSize = ImGui::CalcTextSize(text);

  ImVec2 text_pos = ImVec2(pos.x - TextSize.x * 0.5f, pos.y - TextSize.y * 0.5f);
  ImVec2 shadow_offset = ImVec2(1.0f, 1.0f);
  ImColor shadow_color = ImColor(0, 0, 0, 255);
  ImVec2 shadow_pos = ImVec2(text_pos.x + shadow_offset.x, text_pos.y + shadow_offset.y);

  ImGui::GetForegroundDrawList()->AddText(shadow_pos, shadow_color, text);

  ImGui::GetForegroundDrawList()->AddText(text_pos, color, text);
}

void draw::distance(ImVec2 pos, float distance, ImColor color) {
  std::string distance_str = std::to_string(static_cast<int32_t>(distance)) + "m";
  ImVec2 t_size = ImGui::CalcTextSize(distance_str.c_str());
  ImGui::GetBackgroundDrawList()->AddText(ImVec2(pos.x - t_size.x * 0.5f, pos.y - t_size.y * 0.5f + 7), color, distance_str.c_str());
}

void draw::distance_a(ImVec2 pos, float distance, ImColor color) {
  std::string distance_str = std::to_string(static_cast<int32_t>(distance)) + "m";
  ImVec2 t_size = ImGui::CalcTextSize(distance_str.c_str());

  draw::text(distance_str.c_str(), ImVec2(pos.x - t_size.x * 0.5f + 5, pos.y - t_size.y * 0.5f + 10), color);
}

void draw::grenade_esp(ImFont *font, const char *text, float distance, ImVec2 center, ImColor color, float font_size) {

  ImVec2 text_size = ImGui::CalcTextSize(text);

  if (settings::world::grenade_distance)
    draw::distance(center, distance);

  if (settings::world::grenade_name) {
    draw::text(strcmp(text, "smokegrenade") == 0 ? "smoke" : text, ImVec2(center.x, center.y - 5), color);
    return;
  }

  const std::string grenade_warnings[2] = {"molotov", "hegrenade"};

  if (std::find(std::begin(grenade_warnings), std::end(grenade_warnings), text) != std::end(grenade_warnings)) {
    if (distance > 5 && distance < 10) {

      ImGui::GetBackgroundDrawList()->AddCircleFilled(center, 20.0f, IM_COL32(255, 201, 14, 100), MAX_NUM_SEGMENTS);
      ImGui::GetBackgroundDrawList()->AddCircle(center, 20.0f + 2.0f, IM_COL32(255, 255, 255, 255), MAX_NUM_SEGMENTS, 1.5f);
    } else if (distance < 5) {
      ImGui::GetBackgroundDrawList()->AddCircleFilled(center, 20.0f, IM_COL32(136, 0, 21, 100), MAX_NUM_SEGMENTS);
      ImGui::GetBackgroundDrawList()->AddCircle(center, 20.0f + 2.0f, IM_COL32(255, 255, 255, 255), MAX_NUM_SEGMENTS, 1.5f);
    } else {
      ImGui::GetBackgroundDrawList()->AddCircleFilled(center, 20.0f, IM_COL32(50, 50, 50, 100), MAX_NUM_SEGMENTS);
      ImGui::GetBackgroundDrawList()->AddCircle(center, 20.0f + 2.0f, IM_COL32(255, 255, 255, 255), MAX_NUM_SEGMENTS, 1.5f);
    }
  }

  ImGui::GetBackgroundDrawList()->AddCircleFilled(center, 20.0f, IM_COL32(50, 50, 50, 100), MAX_NUM_SEGMENTS);
  ImGui::GetBackgroundDrawList()->AddCircle(center, 20.0f + 2.0f, IM_COL32(255, 255, 255, 255), MAX_NUM_SEGMENTS, 1.5f);

  if (!strcmp(text, "smokegrenade")) {

    ImGui::GetForegroundDrawList()->AddText(font, font_size, ImVec2(center.x - text_size.x / 2 + 1 + 30, center.y - text_size.y / 2 + 1 - 10), ImColor(0, 0, 0, 255), gun_icon(text));
    ImGui::GetForegroundDrawList()->AddText(font, font_size, ImVec2(center.x - text_size.x / 2 + 30, center.y - text_size.y / 2 - 10), ImColor(255, 255, 255, 255), gun_icon(text));
  }  else if (!strcmp(text, "molotov")) {
    ImGui::GetForegroundDrawList()->AddText(font, font_size, ImVec2(center.x - text_size.x / 2 + 1 + 15, center.y - text_size.y / 2 + 1 - 13), ImColor(0, 0, 0, 255), gun_icon(text));
    ImGui::GetForegroundDrawList()->AddText(font, font_size, ImVec2(center.x - text_size.x / 2 + 15, center.y - text_size.y / 2 - 13), color, gun_icon(text));

  } else {
    ImGui::GetForegroundDrawList()->AddText(font, font_size, ImVec2(center.x - text_size.x / 2 + 1 + 20, center.y - text_size.y / 2 + 1 - 13), ImColor(0, 0, 0, 255), gun_icon(text));
    ImGui::GetForegroundDrawList()->AddText(font, font_size, ImVec2(center.x - text_size.x / 2 + 20, center.y - text_size.y / 2 - 13), color, gun_icon(text));
  }
}

void draw::icon_esp(ImFont *font, const char *text, Vector3 pos, ImColor color, float font_size) {

  ImVec2 text_size = ImGui::CalcTextSize(text);

  ImGui::GetForegroundDrawList()->AddText(font, font_size, ImVec2(pos.x - text_size.x / 2 + 1, pos.y - text_size.y / 2 + 1 - 15), ImColor(0, 0, 0, 255), gun_icon(text));
  ImGui::GetForegroundDrawList()->AddText(font, font_size, ImVec2(pos.x - text_size.x / 2, pos.y - text_size.y / 2 - 15), color, gun_icon(text));
}

void draw::snaplines(Vector3 &screen_pos, ImColor color) { ImGui::GetBackgroundDrawList()->AddLine({screen_pos.x, screen_pos.y}, ImVec2(width / 2, height), color); }

void draw::path(Vector3 &pos, int idx, bool tick_begin) {
  if (tick_begin)
    return;

  static std::map<int, std::vector<Vector3>> trail_positions;

  trail_positions[idx].push_back(pos);

  for (size_t i = 0; i < trail_positions[idx].size() - 1; ++i) {
    ImVec2 p1 = ImVec2(trail_positions[idx][i].x, trail_positions[idx][i].y);
    ImVec2 p2 = ImVec2(trail_positions[idx][i + 1].x, trail_positions[idx][i + 1].y);
    ImGui::GetForegroundDrawList()->AddLine(p1, p2, IM_COL32(255, 255, 255, 255), 2.0f);
  }

  if (trail_positions[idx].size() > MAX_NUM_SEGMENTS) {
    trail_positions[idx].erase(trail_positions[idx].begin());
  }
}

void draw::skeleton(uintptr_t bonearray,bool visible){

#if _DEBUG
    for (int i = 0; i < 32; i++) {
       auto bone = PlayerController::get_bone_pos_2d(bonearray,i);

        std::string number = std::to_string(i);
        ImVec2 TextSize = ImGui::CalcTextSize(number.c_str());
        ImGui::GetForegroundDrawList()->AddText(ImVec2(bone.x - TextSize.x / 2, bone.y - TextSize.y / 2), ImColor(255, 255, 255, 255), number.c_str());

    }
#else

   Vector3 head = PlayerController::get_bone_pos_2d(bonearray,EBone::Head);
	Vector3 neck = PlayerController::get_bone_pos_2d(bonearray,EBone::Neck);
	Vector3 right_shoulder = PlayerController::get_bone_pos_2d(bonearray,EBone::RightShoulder);
	Vector3 left_shoulder = PlayerController::get_bone_pos_2d(bonearray,EBone::LeftShoulder);
	Vector3 right_arm = PlayerController::get_bone_pos_2d(bonearray,EBone::RightArm);
	Vector3 left_arm = PlayerController::get_bone_pos_2d(bonearray,EBone::LeftArm);
	Vector3 right_hand = PlayerController::get_bone_pos_2d(bonearray,EBone::RightHand);
	Vector3 left_hand = PlayerController::get_bone_pos_2d(bonearray,EBone::LeftHand);
	Vector3 root = PlayerController::get_bone_pos_2d(bonearray,EBone::Root);
	Vector3 right_knee = PlayerController::get_bone_pos_2d(bonearray,EBone::RightKnee);
	Vector3 left_knee = PlayerController::get_bone_pos_2d(bonearray,EBone::LeftKnee);
	Vector3 right_foot = PlayerController::get_bone_pos_2d(bonearray,EBone::RightFoot);
	Vector3 left_foot = PlayerController::get_bone_pos_2d(bonearray,EBone::LeftFoot);

    const constexpr int workaround = 25;

	ImGui::GetBackgroundDrawList()->AddLine({ head.x, head.y - workaround }, { neck.x, neck.y - workaround }, visible ? settings::colors::skeleton_visible_color : settings::colors::skeleton_hidden_color);
	ImGui::GetBackgroundDrawList()->AddLine({ neck.x, neck.y - workaround }, { right_shoulder.x, right_shoulder.y - workaround }, visible ? settings::colors::skeleton_visible_color : settings::colors::skeleton_hidden_color);
	ImGui::GetBackgroundDrawList()->AddLine({ neck.x, neck.y - workaround }, { left_shoulder.x, left_shoulder.y - workaround }, visible ? settings::colors::skeleton_visible_color : settings::colors::skeleton_hidden_color);
	ImGui::GetBackgroundDrawList()->AddLine({ right_shoulder.x, right_shoulder.y - workaround }, { right_arm.x, right_arm.y - workaround }, visible ? settings::colors::skeleton_visible_color : settings::colors::skeleton_hidden_color);
	ImGui::GetBackgroundDrawList()->AddLine({ left_shoulder.x, left_shoulder.y - workaround }, { left_arm.x, left_arm.y - workaround }, visible ? settings::colors::skeleton_visible_color : settings::colors::skeleton_hidden_color);
	ImGui::GetBackgroundDrawList()->AddLine({ right_arm.x, right_arm.y - workaround }, { right_hand.x, right_hand.y - workaround }, visible ? settings::colors::skeleton_visible_color : settings::colors::skeleton_hidden_color);
	ImGui::GetBackgroundDrawList()->AddLine({ left_arm.x, left_arm.y - workaround }, { left_hand.x, left_hand.y - workaround }, visible ? settings::colors::skeleton_visible_color : settings::colors::skeleton_hidden_color);
	ImGui::GetBackgroundDrawList()->AddLine({ neck.x, neck.y - workaround }, { root.x, root.y - workaround }, visible ? settings::colors::skeleton_visible_color : settings::colors::skeleton_hidden_color);
	ImGui::GetBackgroundDrawList()->AddLine({ root.x, root.y - workaround }, { right_knee.x, right_knee.y - workaround }, visible ? settings::colors::skeleton_visible_color : settings::colors::skeleton_hidden_color);
	ImGui::GetBackgroundDrawList()->AddLine({ root.x, root.y - workaround }, { left_knee.x, left_knee.y - workaround }, visible ? settings::colors::skeleton_visible_color : settings::colors::skeleton_hidden_color);
	ImGui::GetBackgroundDrawList()->AddLine({ right_knee.x, right_knee.y - workaround }, { right_foot.x, right_foot.y - workaround }, visible ? settings::colors::skeleton_visible_color : settings::colors::skeleton_hidden_color);
	ImGui::GetBackgroundDrawList()->AddLine({ left_knee.x, left_knee.y - workaround }, { left_foot.x, left_foot.y - workaround }, visible ? settings::colors::skeleton_visible_color : settings::colors::skeleton_hidden_color);
#endif

}

void draw::filled_rect(int x, int y, int w, int h, ImVec4 color) {

    ImGui::GetForegroundDrawList()->AddRectFilled(ImVec2(x, y), ImVec2(x + w, y + h), ImGui::ColorConvertFloat4ToU32(color), 0, 0);
}

void draw::healthbar(int x, int y, int w, int h, int thick, int health) {

    float dt = health / 100.0f;

    ImVec4 color = ImVec4(ImLerp(255.0f, 0.f, dt), ImLerp(0.f, (health > 50 ? 165.0f : 0.0f), dt), 0.0f, 200);


    std::string health_str = std::to_string(static_cast<int32_t>(health));

    int health_h = (h * health) / 100;
    int bar_y = y + h - health_h;

    draw::filled_rect(x + (w / 2) - 25, y, thick, h, ImColor(0,0,0,255));
    draw::filled_rect(x + (w / 2) - 25, bar_y, thick, health_h, color);

    if (health < 100)
        draw::text(health_str.c_str(), ImVec2(x + (w / 2) - 22, bar_y + 5), ImVec4(255, 255, 255, 255));

};
