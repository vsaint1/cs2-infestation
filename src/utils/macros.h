//
// Created by vsantos1 on 2/17/2024.
//

#ifndef MUSTACHE_MACROS_H
#define MUSTACHE_MACROS_H

#include <algorithm>
#include <string>
#include <string_view>
#include <memory.h>


#ifdef _DEBUG
#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_DEBUG
#include <spdlog/spdlog.h>
#else
#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_OFF
#include <spdlog/spdlog.h>

#endif

bool compare(std::string_view str1, std::string_view str2);

#define EQUALS_IGNORE_CASE(str1, str2) compare(str1,str2)

#define WINDOW_NAME "Counter-Strike 2"

#define GAME_NAME "cs2.exe"

#define CLIENT_MODULE_NAME "client.dll"

#define ENGINE_MODULE_NAME "engine2.dll"

#endif //MUSTACHE_MACROS_H
