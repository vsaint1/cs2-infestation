//
// Created by vsantos1 on 2/16/2024.
//
#include "memory/memory.hpp"
#include <iostream>

int main() {
  memory.attach();

  printf("PID %d\n", memory.get_pid());

  auto local_pawn = memory.find_pattern("client.dll", "48 8D 05 ? ? ? ? C3 CC CC CC CC CC CC CC CC 48 83 EC ? 8B 0D")->rip().add(0x138);
  auto [address, size] = memory.get_module_info("client.dll");
  printf("MODULE_BASE %p", address.value());
  printf("LOCAL_PAWN %p", local_pawn);

  while (true) {
    auto lp = memory.readv<uintptr_t>(local_pawn.get_address());
    if (!lp)
      continue;

    int health = memory.readv<int>(lp + 0x334);
    printf("HEALTH %d \n", health);
  }

  return EXIT_SUCCESS;
}