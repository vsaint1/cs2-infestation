/*
 *   Copyright (c) 2024 vsantos1
 *   All rights reserved.
 */

#ifndef SDK_GLOBAL_VARS_HPP_
#define SDK_GLOBAL_VARS_HPP_
#include <cstdint>

class GlobalVarsInstance
{
public:
	class GlobalVarsBase *g_vars; //0x0000
	char pad_0008[120]; //0x0008
}; //Size: 0x0080
static_assert(sizeof(GlobalVarsInstance) == 0x80);

class N00000512
{
public:
	char pad_0000[8]; //0x0000
}; //Size: 0x0008
static_assert(sizeof(N00000512) == 0x8);

class GlobalVarsBase
{
public:
	float m_flRealTime; //0x0000
	char pad_0004[44]; //0x0004
	float m_flcurrentTime; //0x0030
	float m_flIntervalPerTick; //0x0034
	float m_flIntervalPerTick2; //0x0038
	char pad_003C[324]; //0x003C
	uint64_t m_currentMap; //0x0180
	uint64_t m_currentMapName; //0x0188
	char pad_0190[8]; //0x0190
	uint64_t m_maxClients; //0x0198
	char pad_01A0[304]; //0x01A0
}; //Size: 0x02D0
static_assert(sizeof(GlobalVarsBase) == 0x2D0);

inline GlobalVarsBase global_vars{};

#endif // SDK_GLOBAL_VARS_HPP_
