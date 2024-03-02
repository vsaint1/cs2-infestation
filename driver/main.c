#include "utils/main.h"

NTSTATUS driver_unload(PDRIVER_OBJECT driver_object) {
  UNREFERENCED_PARAMETER(driver_object);

  printf("Test driver unload");
  return STATUS_SUCCESS;
}

NTSTATUS driver_entry(PDRIVER_OBJECT driver_object, PUNICODE_STRING registry_path) {
  UNREFERENCED_PARAMETER(registry_path);

  driver_object->DriverUnload = driver_unload;

  if (DRIVER_RUNNING("FACEIT.sys") || DRIVER_RUNNING("gamersclub.sys") || DRIVER_RUNNING("bedaisy.sys") || DRIVER_RUNNING("vgk.sys") || ("EasyAntiCheat_EOS.sys")) {
    printf("Aborting AC driver found running ");
    return STATUS_ABANDONED;
  }

  printf("Test driver loaded");

  return STATUS_SUCCESS;
}