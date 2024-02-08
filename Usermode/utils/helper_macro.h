#pragma once
#include <iostream>

#define GAME_NAME "cs2.exe"
#define MODULE_NAME "client.dll"

#ifdef _DEBUG
#define LOG(fmt, ...) \
    do { \
        const auto filename = strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__; \
        std::cout << "[infestation:" << filename << ":" << __LINE__ << "] - " << fmt << "\n"; \
    } while (0)
#else
#define LOG(fmt, ...)                                                                                                                                                                                  \
  { printf("[infestation] - " fmt "\n", __VA_ARGS__); }
#endif