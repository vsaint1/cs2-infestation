#pragma once
#include <iostream>

#define GAME_NAME "cs2.exe"
#define MODULE_NAME "client.dll"

#ifdef _DEBUG
#define LOG(fmt, ...)\
{\
const auto filename = strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__;\
printf("[infestation-%s:%d] - " fmt "\n", filename, __LINE__, __VA_ARGS__);\
}
#else
#define LOG(fmt, ...)                                                                                                                                                                                  \
  { printf("[infestation] - " fmt "\n", __VA_ARGS__); }
#endif