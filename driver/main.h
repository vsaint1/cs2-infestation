/*
 *   Copyright (c) 2024 vsantos1
 *   All rights reserved.
 */
#pragma once
#include <ntdef.h>
#include <ntifs.h>
#include "macros.h"

NTSTATUS driver_entry(PDRIVER_OBJECT driver_object,PUNICODE_STRING registry_path);

NTSTATUS driver_unload(PDRIVER_OBJECT driver_object);
