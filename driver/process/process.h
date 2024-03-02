/*
 *   Copyright (c) 2024 vsantos1
 *   All rights reserved.
 */
#include "../utils/defs.h"
#include "../utils/macros.h"

#define DRIVER_RUNNING(str) get_kernel_module(str) != 0 ? TRUE : FALSE

ULONG64 get_kernel_module(const char *module_name);

