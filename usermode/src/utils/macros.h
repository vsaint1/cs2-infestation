//
// Created by vsantos1 on 2/17/2024.
//

#ifndef MUSTACHE_MACROS_H
#define MUSTACHE_MACROS_H

#include <algorithm>
#include <memory.h>
#include <string>
#include <string_view>

#ifdef _DEBUG
#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_DEBUG
#include <spdlog/spdlog.h>
#else
#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_OFF
#include <spdlog/spdlog.h>

#endif

#if _DEBUG
#define BUILD_TYPE "[DEBUG] - Metrics, build " ## __TIMESTAMP__
#else
#define BUILD_TYPE "[RELEASE] - Metrics, build " ## __TIMESTAMP__
#endif

bool compare(std::string_view str1, std::string_view str2);

template <typename _T> unsigned int constexpr hash_const(_T const *input) { return *input ? static_cast<unsigned int>(*input) + 33 * hash_const(input + 1) : 5381; }

template <typename _T> unsigned int constexpr hash_const_enhanced(_T const *input, const char *has_this = "C_Weapon") {
  std::string_view str_view(input);
  if (str_view.starts_with(has_this))
    return 0x1234ABCD;
  else
    return hash_const(input);
}

#define EQUALS_IGNORE_CASE(str1, str2) compare(str1, str2)

#define WINDOW_NAME "Counter-Strike 2"

#define GLSL_VERSION "#version 130"

#define GAME_NAME "cs2.exe"

#define CLIENT_MODULE_NAME "client.dll"

#define ENGINE_MODULE_NAME "engine2.dll"

#endif // MUSTACHE_MACROS_H
