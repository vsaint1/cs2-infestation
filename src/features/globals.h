/*
 *   Copyright (c) 2024 vsantos1
 *   All rights reserved.
 */

#ifndef FEATURES_GLOBALS_H_
#define FEATURES_GLOBALS_H_



#include <SDL2/SDL_pixels.h>

inline uintptr_t local_player;

inline uintptr_t client;

namespace settings {
namespace colors {

inline SDL_Color red = {255, 0, 0, 255};
inline SDL_Color green = {0, 255, 0, 255};
inline SDL_Color gray = {200, 200, 200};
} // namespace colors

} // namespace settings

#endif // FEATURES_GLOBALS_H_
