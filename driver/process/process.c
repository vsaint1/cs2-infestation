#include "process.h"

ULONG64 get_kernel_module(const char* module_name) {
	ULONG64 module_base = 0;
	ULONG module_size = 0;
	PRTL_PROCESS_MODULES modules = NULL;
	NTSTATUS status = ZwQuerySystemInformation(system_module_information, 0, 0, &module_size);

	if (status != STATUS_INFO_LENGTH_MISMATCH)
		return 0;


	modules = (PRTL_PROCESS_MODULES)ExAllocatePool2(POOL_FLAG_NON_PAGED, module_size, KM_POOL_TAG);
	if (!modules)
		return 0;

	status = ZwQuerySystemInformation(system_module_information, modules, module_size, &module_size);
	if (!NT_SUCCESS(status)) {
		ExFreePoolWithTag(modules, KM_POOL_TAG);
		return 0;
	}

	PRTL_PROCESS_MODULE_INFORMATION module = modules->Modules;
	for (ULONG i = 0; i < modules->NumberOfModules; i++) {
		printf("Module Name: %s\n", module[i].FullPathName + module[i].OffsetToFileName);
		printf("Module Base: %p\n", module[i].ImageBase);
		printf("Module Size: %d\n", module[i].ImageSize);

		if (strcmp((char*)module[i].FullPathName + module[i].OffsetToFileName, module_name) == 0) {
			module_base = (ULONG64)module[i].ImageBase;
			break;
		}
	}

	ExFreePoolWithTag(modules, KM_POOL_TAG);
	return module_base;
}
