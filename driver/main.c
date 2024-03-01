#include "main.h"

NTSTATUS driver_unload(PDRIVER_OBJECT driver_object) {
  UNREFERENCED_PARAMETER(driver_object);

  printf("test driver unload");
}

NTSTATUS driver_entry(PDRIVER_OBJECT driver_object, PUNICODE_STRING registry_path) {
  UNREFERENCED_PARAMETER(registry_path);

  printf("Test driver loaded");

  driver_object->DriverUnload = driver_unload;
  return STATUS_SUCCESS;
}