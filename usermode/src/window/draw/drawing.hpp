/*
 *   Copyright (c) 2024 vsantos1
 *   All rights reserved.
 */
#ifndef WINDOW_DRAW_DRAWING_HPP_
#define WINDOW_DRAW_DRAWING_HPP_

#include "../../features/globals.h"
#include "../../utils/gun_icons.hpp"
#include "../../sdk/player/player_controller.h"

constexpr int MAX_NUM_SEGMENTS = 20;

namespace draw {

    void text(const char *text, ImVec2 pos, ImColor color, float font_size = 13.0f);

    void distance(ImVec2 pos, float distance, ImColor color = ImColor(255, 255, 255, 255));

    void distance_a(ImVec2 pos, float distance, ImColor color = ImColor(255, 255, 255, 255));

    void
    grenade_esp(ImFont *font, const char *text, float distance, ImVec2 center, ImColor color, float font_size = 13.0f);

    void icon_esp(ImFont *font, const char *text, Vector3 pos, ImColor color, float font_size = 13.0f);

    void snaplines(Vector3 &screen_pos, ImColor color);

    void path(Vector3 &pos, int idx, bool tick_begin);

    void skeleton(uintptr_t bonearray, bool visible);

    void filled_rect(int x, int y, int w, int h, ImVec4 color);

    void healthbar(int x, int y, int w, int h, int thick, int health);

};     // namespace draw
#endif // WINDOW_DRAW_DRAWING_HPP_
