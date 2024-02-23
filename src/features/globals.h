/*
 *   Copyright (c) 2024 vsantos1
 *   All rights reserved.
 */

#ifndef FEATURES_GLOBALS_H_
#define FEATURES_GLOBALS_H_

#include <cstddef>
#include <SDL2/SDL_pixels.h>

inline uintptr_t local_player;

inline uintptr_t client;

namespace offsets {
namespace C_PlantedC4 {                               // CBaseAnimGraph
constexpr std::ptrdiff_t m_nBombSite = 0xEDC;         // int32_t
constexpr std::ptrdiff_t m_flC4Blow = 0xF08;          // GameTime_t
constexpr std::ptrdiff_t m_bBeingDefused = 0xF14;     // bool
constexpr std::ptrdiff_t m_flDefuseCountDown = 0xF28; // GameTime_t
constexpr std::ptrdiff_t m_bBombDefused = 0xF2C;      // bool

};                                                    // namespace C_PlantedC4

namespace C_BaseEntity {};
}; // namespace offsets
namespace settings {
namespace colors {

inline SDL_Color red = {255, 0, 0, 255};
inline SDL_Color green = {0, 255, 0, 255};
inline SDL_Color gray = {200, 200, 200};
} // namespace colors

} // namespace settings

#endif // FEATURES_GLOBALS_H_
