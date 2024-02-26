/*
 *   Copyright (c) 2024 vsantos1
 *   All rights reserved.
 */
#include "../../features/globals.h"

namespace draw {
void text(const char *text, ImVec2 pos, ImColor color, float font_size = 13.0f) {
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

}; // namespace draw
