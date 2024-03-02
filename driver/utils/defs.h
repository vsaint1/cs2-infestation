/*
 *   Copyright (c) 2024 vsantos1
 *   All rights reserved.
 */
#pragma once
#include <ntdef.h>
#include <ntifs.h>

#define KeMRaiseIrql(a, b) *(b) = KfRaiseIrql(a)
#define KM_POOL_TAG 'kdd'

typedef int BOOL;
typedef unsigned int DWORD;
typedef ULONG_PTR QWORD;

#pragma warning(disable : 4201)

typedef struct _PEB_LDR_DATA {
  ULONG Length;
  UCHAR Initialized;
  PVOID SsHandle;
  LIST_ENTRY InLoadOrderModuleList;
  LIST_ENTRY InMemoryOrderModuleList;
  LIST_ENTRY InInitializationOrderModuleList;
} PEB_LDR_DATA, *PPEB_LDR_DATA;

typedef enum _SYSTEM_INFORMATION_CLASS {
  system_basic_information,
  system_processor_information,
  system_performance_information,
  system_time_of_day_information,
  system_path_information,
  system_process_information,
  system_call_count_information,
  system_device_information,
  system_processor_performance_information,
  system_flags_information,
  system_call_time_information,
  system_module_information,
  system_locks_information,
  system_stack_trace_information,
  system_paged_pool_information,
  system_non_paged_pool_information,
  system_handle_information,
  system_object_information,
  system_page_file_information,
  system_vdm_instemul_information,
  system_vdm_bop_information,
  system_file_cache_information,
  system_pool_tag_information,
  system_interrupt_information,
  system_dpc_behavior_information,
  system_full_memory_information,
  system_load_gdi_driver_information,
  system_unload_gdi_driver_information,
  system_time_adjustment_information,
  system_summary_memory_information,
  system_next_event_id_information,
  system_event_ids_information,
  system_crash_dump_information,
  system_exception_information,
  system_crash_dump_state_information,
  system_kernel_debugger_information,
  system_context_switch_information,
  system_registry_quota_information,
  system_extend_service_table_information,
  system_priority_seperation,
  system_plug_play_bus_information,
  system_dock_information,
  system_processor_speed_information,
  system_current_time_zone_information,
  system_lookaside_information,
  system_bigpool_information = 0x42
} SYSTEM_INFORMATION_CLASS,
    *PSYSTEM_INFORMATION_CLASS;

typedef struct _PEB {
  UCHAR InheritedAddressSpace;
  UCHAR ReadImageFileExecOptions;
  UCHAR BeingDebugged;
  UCHAR BitField;
  PVOID Mutant;
  PVOID ImageBaseAddress;
  PPEB_LDR_DATA Ldr;
  PVOID ProcessParameters;
  PVOID SubSystemData;
  PVOID ProcessHeap;
  PVOID FastPebLock;
  PVOID AtlThunkSListPtr;
  PVOID IFEOKey;
  PVOID CrossProcessFlags;
  PVOID KernelCallbackTable;
  ULONG SystemReserved;
  ULONG AtlThunkSListPtr32;
  PVOID ApiSetMap;
} PEB, *PPEB;

typedef struct _LDR_DATA_TABLE_ENTRY {
  LIST_ENTRY InLoadOrderLinks;
  LIST_ENTRY InMemoryOrderLinks;
  LIST_ENTRY InInitializationOrderLinks;
  PVOID DllBase;
  PVOID EntryPoint;
  ULONG SizeOfImage;
  UNICODE_STRING FullDllName;
  UNICODE_STRING BaseDllName;
  ULONG Flags;
  USHORT LoadCount;
  USHORT TlsIndex;
  LIST_ENTRY HashLinks;
  ULONG TimeDateStamp;
} LDR_DATA_TABLE_ENTRY, *PLDR_DATA_TABLE_ENTRY;

typedef struct _RTL_PROCESS_MODULE_INFORMATION {
  HANDLE Section;
  PVOID MappedBase;
  PVOID ImageBase;
  ULONG ImageSize;
  ULONG Flags;
  USHORT LoadOrderIndex;
  USHORT InitOrderIndex;
  USHORT LoadCount;
  USHORT OffsetToFileName;
  UCHAR FullPathName[256];
} RTL_PROCESS_MODULE_INFORMATION, *PRTL_PROCESS_MODULE_INFORMATION;

typedef enum _EPROCESS_OFFSETS {

  ActiveProcessLinks = 0x448,
  UniqueProcessId = 0x2e8,
  ImageFileName = 0x5a8
} EPROCESS_OFFSETS;

typedef struct _RTL_PROCESS_MODULES {
  ULONG NumberOfModules;
  RTL_PROCESS_MODULE_INFORMATION Modules[1];
} RTL_PROCESS_MODULES, *PRTL_PROCESS_MODULES;

NTSYSCALLAPI
POBJECT_TYPE *IoDriverObjectType;

NTSYSCALLAPI
NTSTATUS
ObReferenceObjectByName(__in PUNICODE_STRING ObjectName, __in ULONG Attributes, __in_opt PACCESS_STATE AccessState, __in_opt ACCESS_MASK DesiredAccess, __in POBJECT_TYPE ObjectType,
                        __in KPROCESSOR_MODE AccessMode, __inout_opt PVOID ParseContext, __out PVOID *Object);

NTSYSCALLAPI PPEB PsGetProcessPeb(PEPROCESS);

NTSTATUS ZwQuerySystemInformation(ULONG InfoClass, PVOID Buffer, ULONG Length, PULONG ReturnLength);

NTKERNELAPI PVOID PsGetProcessSectionBaseAddress(__in PEPROCESS Process);

NTSTATUS NTAPI MmCopyVirtualMemory(PEPROCESS SourceProcess, PVOID SourceAddress, PEPROCESS TargetProcess, PVOID TargetAddress, SIZE_T BufferSize, KPROCESSOR_MODE PreviousMode, PSIZE_T ReturnSize);

NTKERNELAPI
NTSTATUS
IoCreateDriver(IN PUNICODE_STRING DriverName, OPTIONAL IN PDRIVER_INITIALIZE InitializationFunction);

NTKERNELAPI
VOID IoDeleteDriver(IN PDRIVER_OBJECT DriverObject);
