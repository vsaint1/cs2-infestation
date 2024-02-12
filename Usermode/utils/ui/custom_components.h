#pragma once
#include "../../external/imgui/imgui_internal.h"
#include "../../external/imgui/imgui.h"
#include <algorithm>
#include <string>

namespace component {
	void color_picker(ImColor& original_color);

	void set_helper(const char* text, ImColor color = ImColor(105, 105, 105), char symbol = '?');

	void create_style();
}