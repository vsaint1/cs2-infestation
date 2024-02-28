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

  draw::text(distance_str.c_str(), ImVec2(pos.x - t_size.x * 0.5f, pos.y - t_size.y * 0.5f + 7), color);
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
  } else if (!strcmp(text, "molotov")) {
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

void draw::path(Vector3 pos) {
    static Vector3 last_trail_position; 
    static std::vector<Vector3> trail_positions;
    
    if (pos != last_trail_position) {
        trail_positions.push_back(pos);
        last_trail_position = pos; 
    }

    for (size_t i = 1; i < trail_positions.size(); ++i) {
        ImVec2 p1 = ImVec2(trail_positions[i - 1].x, trail_positions[i - 1].y);
        ImVec2 p2 = ImVec2(trail_positions[i].x, trail_positions[i].y);
        ImGui::GetForegroundDrawList()->AddLine(p1, p2, IM_COL32(255, 255, 255, 255), 2.0f);
    }

    if (trail_positions.size() > MAX_NUM_SEGMENTS)
        trail_positions.erase(trail_positions.begin());

}
