#pragma once
#include <Windows.h>

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
	std::ptrdiff_t dwEntityList = 0x17C1950;
	std::ptrdiff_t dwLocalPlayerPawn = 0x16C8F38;
	std::ptrdiff_t dwGameEntitySystem_getHighestEntityIndex = 0x1510;
	std::ptrdiff_t dwViewMatrix = 0x1820150;
	std::ptrdiff_t dwPawnHealth = 0x7F8;    // m_iPawnHealth = 0x7F8; // uint32_t
	std::ptrdiff_t dwPlayerPawn = 0x7EC;    // m_hPlayerPawn client.dll.rs
	std::ptrdiff_t dwSanitizedName = 0x640; //  m_iszPlayerName = 0x640; // char[128]
	std::ptrdiff_t m_bDormant = 0xE7;
	std::ptrdiff_t m_iTeamNum = 0x3bf;
	std::ptrdiff_t m_vecOrigin = 0x1224;          // m_vOldOrigin client.dll.rs
	std::ptrdiff_t m_iHealth = 0x32C;             // m_iHealth client.dll.rs
	std::ptrdiff_t bSpottedByMask = 0x1630 + 0xC; // entitySpottedState + bSpottedByMask
	std::ptrdiff_t m_iszPlayerName = 0x640;       // char[128]
	std::ptrdiff_t iIDEntIndex = 0x153C;          // m_iIDEntIndex = 0x153C;
} // namespace offsets

namespace settings {

	inline bool bMenu = true;
	namespace aimbot {
		bool aimbot = true;
		bool visible_check = false;
		inline float aim_fov = 0.0f;
		inline float smooth = 0.0f;
		bool fov_circle = false;
		inline int selectedhitbox = 0;
		inline const char* hitbox[] = { ("Head"), ("Chest") };

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


	}; // namespace Visuals

	namespace misc {
		bool bTeamcheck = true;
		bool bWatermark = true;

	}

} // namespace settings

enum EBone : int {

	Head = 6,
	Neck = 5,
	RightShoulder = 8,
	LeftShoulder = 13,
	RightArm = 9,
	LeftArm = 14,
	RightHand = 11,
	LeftHand = 16,
	Root = 0,
	RightKnee = 23,
	LeftKnee = 26,
	RightFoot = 24,
	LeftFoot = 27,
};



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
