#pragma once
#include <Windows.h>
#include "imgui/imgui.h"

HWND entry_hwnd = NULL;
int processid = 0;
RECT Rect;

ULONG64 client = 0;
uintptr_t global_pawn = 0;

static ULONG width = GetSystemMetrics(SM_CXSCREEN);
static ULONG height = GetSystemMetrics(SM_CYSCREEN);

namespace hotkeys {
	int aimkey;
} // namespace hotkeys

static int keystatus = 0;

namespace offsets {
	std::ptrdiff_t dwEntityList = 0x18B1FE8;
	std::ptrdiff_t dwLocalPlayerPawn = 0x17272E8;
	std::ptrdiff_t dwGameEntitySystem_getHighestEntityIndex = 0x1510;
	std::ptrdiff_t dwViewMatrix = 0x19112D0;

	namespace CBasePlayerController { // C_BaseEntity
		std::ptrdiff_t m_nFinalPredictedTick = 0x558; // int32_t
		std::ptrdiff_t m_CommandContext = 0x560; // C_CommandContext
		std::ptrdiff_t m_nInButtonsWhichAreToggles = 0x5F8; // uint64_t
		std::ptrdiff_t m_nTickBase = 0x600; // uint32_t
		std::ptrdiff_t m_hPawn = 0x604; // CHandle<C_BasePlayerPawn>
		std::ptrdiff_t m_hPredictedPawn = 0x608; // CHandle<C_BasePlayerPawn>
		std::ptrdiff_t m_nSplitScreenSlot = 0x60C; // CSplitScreenSlot
		std::ptrdiff_t m_hSplitOwner = 0x610; // CHandle<CBasePlayerController>
		std::ptrdiff_t m_hSplitScreenPlayers = 0x618; // CUtlVector<CHandle<CBasePlayerController>>
		std::ptrdiff_t m_bIsHLTV = 0x630; // bool
		std::ptrdiff_t m_iConnected = 0x634; // PlayerConnectedState
		std::ptrdiff_t m_iszPlayerName = 0x638; // char[128]
		std::ptrdiff_t m_steamID = 0x6C0; // uint64_t
		std::ptrdiff_t m_bIsLocalPlayerController = 0x6C8; // bool
		std::ptrdiff_t m_iDesiredFOV = 0x6CC; // uint32_t
	};

	namespace CCSPlayerController { // CBasePlayerController
		std::ptrdiff_t m_hPlayerPawn = 0x7E4; // CHandle<C_CSPlayerPawn>
		std::ptrdiff_t m_hObserverPawn = 0x7E8; // CHandle<C_CSObserverPawn>
		std::ptrdiff_t m_bPawnIsAlive = 0x7EC; // bool
		std::ptrdiff_t m_iPawnHealth = 0x7F0; // uint32_t
		std::ptrdiff_t m_iPawnArmor = 0x7F4; // int32_t
		std::ptrdiff_t m_bPawnHasDefuser = 0x7F8; // bool
		std::ptrdiff_t m_bPawnHasHelmet = 0x7F9; // bool
	};

	namespace C_CSPlayerPawnBase { // C_BasePlayerPawn

		std::ptrdiff_t m_iIDEntIndex = 0x15A4; // CEntityIndex
		std::ptrdiff_t m_bGunGameImmunity = 0x141C; // bool
		std::ptrdiff_t m_pClippingWeapon = 0x1308; // C_CSWeaponBase*
	};

	namespace C_CSPlayerPawn {
		std::ptrdiff_t m_entitySpottedState = 0x1698; // EntitySpottedState_t

	};

	namespace EntitySpottedState_t {
		std::ptrdiff_t m_bSpotted = 0x8; // bool
		std::ptrdiff_t m_bSpottedByMask = 0xC; // uint32_t[2]
	};

	namespace C_BasePlayerPawn {
		std::ptrdiff_t m_vOldOrigin = 0x127C; // Vector

	};

	namespace C_BaseEntity {
		std::ptrdiff_t m_iTeamNum = 0x3CB; // uint8_t
		std::ptrdiff_t m_iHealth = 0x334; // int32_t
		std::ptrdiff_t m_pGameSceneNode = 0x318; // CGameSceneNode*
	};

	namespace CSkeletonInstance {
		std::ptrdiff_t m_modelState = 0x160; // CModelState

	};


	namespace CGameSceneNode {

		std::ptrdiff_t m_vecOrigin = 0x80; // CNetworkOriginCellCoordQuantizedVector

	};

	namespace CEntityInstance {
		std::ptrdiff_t m_pEntity = 0x10; // CEntityIdentity*
	};

	namespace CEntityIdentity {
		std::ptrdiff_t m_designerName = 0x20; // CUtlSymbolLarge
	}

	namespace C_BaseCSGrenadeProjectile {
		std::ptrdiff_t m_bExplodeEffectBegan = 0x110C; // bool
		std::ptrdiff_t m_vInitialPosition = 0x10C0; // Vector
		std::ptrdiff_t m_vInitialVelocity = 0x10CC; // Vector
		std::ptrdiff_t m_nBounces = 0x10D8; // int32_t
		std::ptrdiff_t m_arrTrajectoryTrailPoints = 0x1120; // CUtlVector<Vector>

	};

	namespace C_SmokeGrenadeProjectile {
		std::ptrdiff_t m_nSmokeEffectTickBegin = 0x1160; // int32_t
		std::ptrdiff_t m_bDidSmokeEffect = 0x1164; // bool
		std::ptrdiff_t m_nRandomSeed = 0x1168; // int32_t
		std::ptrdiff_t m_vSmokeColor = 0x116C; // Vector
		std::ptrdiff_t m_vSmokeDetonationPos = 0x1178; // Vector
		std::ptrdiff_t m_VoxelFrameData = 0x1188; // CUtlVector<uint8_t>
		std::ptrdiff_t m_bSmokeVolumeDataReceived = 0x11A0; // bool
		std::ptrdiff_t m_bSmokeEffectSpawned = 0x11A1; // bool
	};

} // namespace offsets

namespace settings {

	inline bool bMenu = true;
	namespace aimbot {
		bool aimbot = true;
		bool visible_check = false;
		inline float aim_fov = 0.0f;
		inline int smooth = 0;
		bool fov_circle = false;
		inline int selectedhitbox = 0;
		inline const char* hitbox[] = { ("Head"), ("Neck"),("Chest"),("Pelvis"),("Automatic")};

	}; // namespace aimbot


	namespace visuals {
		bool esp = false;
		bool bSkeleton = false;
		bool bHealth = false;
		bool  bName = false;
		bool bSnaplines = false;
		bool bDistance = false;
		bool bBox = false;
		bool distance = false;
		bool bWeapon = false;


	}; // namespace visuals

	namespace world {
		bool esp = false;
		bool grenade_esp = false;
		bool grenade_distance = false;
		bool grenade_trajectory = false;
		bool grenade_name = false;
		bool grenade_snaplines = false;
		bool grenade_timer = false;

		bool weapon_esp = false;
		bool weapon_name = false;
		bool weapon_distance = false;
		bool weapon_snaplines = false;
	};// namespace world

	namespace misc {
		bool bTeamcheck = true;
		bool bWatermark = true;
		bool bAntiScreencapture = true;
		bool bExperimentalFeatures = false;
		int sleep_for_ms = 0;


	}
	namespace colors {
		ImColor player_box = ImColor(44, 44, 44, 255);
		ImColor player_name = ImColor(255, 255, 255, 255);
		ImColor player_weapon = ImColor(255, 255, 255, 255);
		ImColor player_snaplines = ImColor(255, 255, 255, 255);
		ImColor player_distance = ImColor(255, 201, 14, 233);

		ImColor skeleton_hidden_color = ImColor(255, 0, 0, 255);
		ImColor skeleton_visible_color = ImColor(0, 255, 0, 255);
		ImColor grenade_trail_color = ImColor(255, 255, 255, 255);

		

	};
} // namespace settings


static const char* key_names[] = {
	"Press any key..",
	"Left Mouse",
	"Right Mouse",
	"Cancel",
	"Middle Mouse",
	"Mouse 5",
	"Mouse 4",
	"",
	"Backspace",
	"Tab",
	"",
	"",
	"Clear",
	"Enter",
	"",
	"",
	"Shift",
	"Control",
	"Alt",
	"Pause",
	"Caps",
	"",
	"",
	"",
	"",
	"",
	"",
	"Escape",
	"",
	"",
	"",
	"",
	"Space",
	"Page Up",
	"Page Down",
	"End",
	"Home",
	"Left",
	"Up",
	"Right",
	"Down",
	"",
	"",
	"",
	"Print",
	"Insert",
	"Delete",
	"",
	"0",
	"1",
	"2",
	"3",
	"4",
	"5",
	"6",
	"7",
	"8",
	"9",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"A",
	"B",
	"C",
	"D",
	"E",
	"F",
	"G",
	"H",
	"I",
	"J",
	"K",
	"L",
	"M",
	"N",
	"O",
	"P",
	"Q",
	"R",
	"S",
	"T",
	"U",
	"V",
	"W",
	"X",
	"Y",
	"Z",
	"",
	"",
	"",
	"",
	"",
	"Numpad 0",
	"Numpad 1",
	"Numpad 2",
	"Numpad 3",
	"Numpad 4",
	"Numpad 5",
	"Numpad 6",
	"Numpad 7",
	"Numpad 8",
	"Numpad 9",
	"Multiply",
	"Add",
	"",
	"Subtract",
	"Decimal",
	"Divide",
	"F1",
	"F2",
	"F3",
	"F4",
	"F5",
	"F6",
	"F7",
	"F8",
	"F9",
	"F10",
	"F11",
	"F12",
};
