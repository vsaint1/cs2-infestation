//
// Created by vsantos1 on 2/16/2024.
//
#include "memory/memory.hpp"
#include <iostream>

int main() {
  memory.attach();

  SPDLOG_INFO("PID {} \n", memory.get_pid());

  auto local_pawn = memory.find_pattern("client.dll", "48 8D 05 ? ? ? ? C3 CC CC CC CC CC CC CC CC 48 83 EC ? 8B 0D")->rip().add(0x138);
  auto [address, size] = memory.get_module_info("client.dll");
  SPDLOG_INFO("MODULE_BASE: {}", address.value());

  while (true) {
    auto lp = memory.readv<uintptr_t>(local_pawn.get_address());
    if (!lp)
      continue;

    int health = memory.readv<int>(lp + 0x334);
    SPDLOG_INFO("HEALTH: {} \n", health);
  }

  return EXIT_SUCCESS;
}