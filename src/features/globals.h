/*
 *   Copyright (c) 2024 vsantos1
 *   All rights reserved.
 */

#ifndef FEATURES_GLOBALS_H_
#define FEATURES_GLOBALS_H_

#include "math.h"
#include <cstddef>

inline uintptr_t local_player;

inline uintptr_t client;

inline ViewMatrix local_viewmatrix;

inline int width = ww;
inline int height = wh;

namespace offsets {
constexpr std::ptrdiff_t dwEntityList = 0x18B3FA8;
constexpr std::ptrdiff_t dwGameEntitySystem_getHighestEntityIndex = 0x1510;
constexpr std::ptrdiff_t dwLocalPlayerPawn = 0x1729348;
constexpr std::ptrdiff_t dwPlantedC4 = 0x191B508;
constexpr std::ptrdiff_t dwGlobalVars = 0x171CE70;
constexpr std::ptrdiff_t dwViewMatrix = 0x19154C0;

namespace CBasePlayerController {                             // C_BaseEntity
constexpr std::ptrdiff_t m_nFinalPredictedTick = 0x558;       // int32_t
constexpr std::ptrdiff_t m_CommandContext = 0x560;            // C_CommandContext
constexpr std::ptrdiff_t m_nInButtonsWhichAreToggles = 0x5F8; // uint64_t
constexpr std::ptrdiff_t m_nTickBase = 0x600;                 // uint32_t
constexpr std::ptrdiff_t m_hPawn = 0x604;                     // CHandle<C_BasePlayerPawn>
constexpr std::ptrdiff_t m_hPredictedPawn = 0x608;            // CHandle<C_BasePlayerPawn>
constexpr std::ptrdiff_t m_nSplitScreenSlot = 0x60C;          // CSplitScreenSlot
constexpr std::ptrdiff_t m_hSplitOwner = 0x610;               // CHandle<CBasePlayerController>
constexpr std::ptrdiff_t m_hSplitScreenPlayers = 0x618;       // CUtlVector<CHandle<CBasePlayerController>>
constexpr std::ptrdiff_t m_bIsHLTV = 0x630;                   // bool
constexpr std::ptrdiff_t m_iConnected = 0x634;                // PlayerConnectedState
constexpr std::ptrdiff_t m_iszPlayerName = 0x638;             // char[128]
constexpr std::ptrdiff_t m_steamID = 0x6C0;                   // uint64_t
constexpr std::ptrdiff_t m_bIsLocalPlayerController = 0x6C8;  // bool
constexpr std::ptrdiff_t m_iDesiredFOV = 0x6CC;               // uint32_t
};                                                            // namespace CBasePlayerController

namespace CCSPlayerController {                     // CBasePlayerController
constexpr std::ptrdiff_t m_hPlayerPawn = 0x7E4;     // CHandle<C_CSPlayerPawn>
constexpr std::ptrdiff_t m_hObserverPawn = 0x7E8;   // CHandle<C_CSObserverPawn>
constexpr std::ptrdiff_t m_bPawnIsAlive = 0x7EC;    // bool
constexpr std::ptrdiff_t m_iPawnHealth = 0x7F0;     // uint32_t
constexpr std::ptrdiff_t m_iPawnArmor = 0x7F4;      // int32_t
constexpr std::ptrdiff_t m_bPawnHasDefuser = 0x7F8; // bool
constexpr std::ptrdiff_t m_bPawnHasHelmet = 0x7F9;  // bool
};                                                  // namespace CCSPlayerController

namespace C_CSPlayerPawnBase { // C_BasePlayerPawn

constexpr std::ptrdiff_t m_iIDEntIndex = 0x15A4;      // CEntityIndex
constexpr std::ptrdiff_t m_bGunGameImmunity = 0x141C; // bool
constexpr std::ptrdiff_t m_pClippingWeapon = 0x1308;  // C_CSWeaponBase*
};                                                    // namespace C_CSPlayerPawnBase

namespace C_CSPlayerPawn {
constexpr std::ptrdiff_t m_entitySpottedState = 0x1698; // EntitySpottedState_t

};

namespace EntitySpottedState_t {
constexpr std::ptrdiff_t m_bSpotted = 0x8;       // bool
constexpr std::ptrdiff_t m_bSpottedByMask = 0xC; // uint32_t[2]
};                                               // namespace EntitySpottedState_t

namespace C_BasePlayerPawn {
constexpr std::ptrdiff_t m_vOldOrigin = 0x127C; // Vector

};

namespace C_BaseEntity {
constexpr std::ptrdiff_t m_iTeamNum = 0x3CB;       // uint8_t
constexpr std::ptrdiff_t m_iHealth = 0x334;        // int32_t
constexpr std::ptrdiff_t m_pGameSceneNode = 0x318; // CGameSceneNode*
};                                                 // namespace C_BaseEntity

namespace CSkeletonInstance {
constexpr std::ptrdiff_t m_modelState = 0x160; // CModelState

};

namespace CGameSceneNode {

constexpr std::ptrdiff_t m_vecOrigin = 0x80; // CNetworkOriginCellCoordQuantizedVector

};

namespace CEntityInstance {
constexpr std::ptrdiff_t m_pEntity = 0x10; // CEntityIdentity*
};

namespace CEntityIdentity {
constexpr std::ptrdiff_t m_designerName = 0x20; // CUtlSymbolLarge
}

namespace C_BaseCSGrenadeProjectile {
constexpr std::ptrdiff_t m_bExplodeEffectBegan = 0x110C;      // bool
constexpr std::ptrdiff_t m_vInitialPosition = 0x10C0;         // Vector
constexpr std::ptrdiff_t m_vInitialVelocity = 0x10CC;         // Vector
constexpr std::ptrdiff_t m_nBounces = 0x10D8;                 // int32_t
constexpr std::ptrdiff_t m_arrTrajectoryTrailPoints = 0x1120; // CUtlVector<Vector>

}; // namespace C_BaseCSGrenadeProjectile

namespace C_SmokeGrenadeProjectile {
constexpr std::ptrdiff_t m_nSmokeEffectTickBegin = 0x1160;    // int32_t
constexpr std::ptrdiff_t m_bDidSmokeEffect = 0x1164;          // bool
constexpr std::ptrdiff_t m_nRandomSeed = 0x1168;              // int32_t
constexpr std::ptrdiff_t m_vSmokeColor = 0x116C;              // Vector
constexpr std::ptrdiff_t m_vSmokeDetonationPos = 0x1178;      // Vector
constexpr std::ptrdiff_t m_VoxelFrameData = 0x1188;           // CUtlVector<uint8_t>
constexpr std::ptrdiff_t m_bSmokeVolumeDataReceived = 0x11A0; // bool
constexpr std::ptrdiff_t m_bSmokeEffectSpawned = 0x11A1;      // bool
};                                                            // namespace C_SmokeGrenadeProjectile

namespace C_PlantedC4 {                               // CBaseAnimGraph
constexpr std::ptrdiff_t m_nBombSite = 0xEDC;         // int32_t
constexpr std::ptrdiff_t m_flC4Blow = 0xF08;          // GameTime_t
constexpr std::ptrdiff_t m_bBeingDefused = 0xF14;     // bool
constexpr std::ptrdiff_t m_flDefuseCountDown = 0xF28; // GameTime_t
constexpr std::ptrdiff_t m_bBombDefused = 0xF2C;      // bool

} // namespace C_PlantedC4

namespace C_BaseEntity {};
}; // namespace offsets
namespace settings {
inline bool show_menu = true;

namespace colors {
inline ImColor player_box = ImColor(44, 44, 44, 255);
inline ImColor player_name = ImColor(255, 255, 255, 255);
inline ImColor player_weapon = ImColor(255, 255, 255, 255);
inline ImColor player_snaplines = ImColor(255, 255, 255, 255);
inline ImColor player_distance = ImColor(255, 201, 14, 233);

inline ImColor skeleton_hidden_color = ImColor(255, 0, 0, 255);
inline ImColor skeleton_visible_color = ImColor(0, 255, 0, 255);

inline ImColor weapon_dropped = ImColor(195, 195, 195, 255);

inline ImColor bomb_timer = ImColor(195, 195, 195, 255);
inline ImColor defuse_timer = ImColor(255, 0, 0, 255);

inline ImColor grenade_trails = ImColor(255, 0, 0, 255);

}; // namespace colors

namespace aimbot {
	inline bool aimbot = false;
};

namespace visuals {
	inline bool player_esp = false;

};

namespace misc {
	inline bool experimental_features = false;
	inline bool bomb_timer = false;
	inline bool team_check = false;

};

namespace world {
inline bool esp = false;
inline bool grenade_esp = false;
inline bool grenade_warning = false;

inline bool grenade_distance = false;
inline bool grenade_trajectory = false;
inline bool grenade_name = false;
inline bool grenade_snaplines = false;
inline bool grenade_timer = false;

inline bool weapon_esp = false;
inline bool weapon_name = false;
inline bool weapon_distance = false;
inline bool weapon_snaplines = false;
}; // namespace world

} // namespace settings

#endif // FEATURES_GLOBALS_H_
