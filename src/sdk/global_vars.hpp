/*
 *   Copyright (c) 2024 vsantos1
 *   All rights reserved.
 */

#include <cstdint>

class GlobalVarsBase
{
public:
	float m_flRealTime; //0x0000
	char pad_0004[44]; //0x0004
	float m_flCurrentTime; //0x0030
	char pad_0034[4]; //0x0034
	float m_flIntervalPerTick; //0x0038
	char pad_003C[324]; //0x003C
	uint64_t m_currentMap; //0x0180
	uint64_t m_currentMapName; //0x0188
	char pad_0190[184]; //0x0190
}; //Size: 0x0248

inline GlobalVarsBase global_vars {};