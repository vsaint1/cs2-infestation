#pragma once
#include <string> 
#include <TlHelp32.h>

typedef NTSTATUS(WINAPI* pNtReadVirtualMemory)(HANDLE ProcessHandle, PVOID BaseAddress, PVOID Buffer, ULONG NumberOfBytesToRead, PULONG NumberOfBytesRead);
typedef NTSTATUS(WINAPI* pNtWriteVirtualMemory)(HANDLE Processhandle, PVOID BaseAddress, PVOID Buffer, ULONG NumberOfBytesToWrite, PULONG NumberOfBytesWritten);

class Memory
{
private:
	HANDLE handle = 0;
	DWORD process_id = 0;

	pNtReadVirtualMemory read_virtual;
	pNtWriteVirtualMemory write_virtual;

	uintptr_t get_process_id(std::string process_name)
	{
		PROCESSENTRY32 pe;

		HANDLE valid_ts = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, process_id);

		uintptr_t result = 0;

		if (valid_ts != INVALID_HANDLE_VALUE)
		{
			while (Process32Next(valid_ts, &pe))
			{
				if (!process_name.compare(pe.szExeFile))
				{
					result = pe.th32ProcessID;
					break;
				}
			}
		}

		if (valid_ts)
			CloseHandle(valid_ts);

		return result;
	}


	uintptr_t get_module(std::string module_name)
	{
		MODULEENTRY32 pe;

		HANDLE valid_ts = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, process_id);

		uintptr_t result = 0;

		if (valid_ts != INVALID_HANDLE_VALUE)
		{
			while (Module32Next(valid_ts, &pe))
			{
				if (!module_name.compare(pe.szModule))
				{

					result = reinterpret_cast<uintptr_t>(pe.modBaseAddr);
					break;
				}
			}
		}

		if (valid_ts)
			CloseHandle(valid_ts);

		if (result != 0)
			return result;

		return false;
	}
public:

	Memory(std::string proces_name)
	{
		read_virtual = (pNtReadVirtualMemory)GetProcAddress(GetModuleHandleA("ntdll.dll"), "NtReadVirtualMemory");
		write_virtual = (pNtWriteVirtualMemory)GetProcAddress(GetModuleHandleA("ntdll.dll"), "NtWriteVirtualMemory");

		process_id = get_process_id(proces_name);

		if (process_id)
		{
			PROCESSENTRY32 pe;

			HANDLE valid_ts = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, process_id);

			if (valid_ts != INVALID_HANDLE_VALUE)
			{
				while (Process32Next(valid_ts, &pe))
				{
					if (!proces_name.compare(pe.szExeFile))
					{
						handle = OpenProcess(PROCESS_VM_READ, FALSE, pe.th32ProcessID);
						break;


					}
				}
			}

			if (valid_ts)
				CloseHandle(valid_ts);
		}
	}


	~Memory()
	{

		if (handle)
			CloseHandle(handle);
	}

	uintptr_t get_modulebase(std::string module_name)
	{
		return get_module(module_name);
	}

	int get_procid()
	{
		return process_id;
	}

	template <typename T>
	T readv(uintptr_t address)
	{
		T buffer{ };
		read_virtual(handle, (void*)address, &buffer, sizeof(T), 0);
		return buffer;
	}

	template <typename T>
	T writev(uintptr_t address, T value)
	{
		write_virtual(handle, (void*)address, &value, sizeof(T), NULL);
		return value;
	}

	

	bool read_raw(uintptr_t address, void* buffer, size_t size)
	{
		SIZE_T bytes_read{};
		if (read_virtual(handle, (void*)address, &buffer, static_cast<ULONG>(size), (PULONG)&bytes_read))
			return bytes_read == size;

		return false;
	}

	std::string read_str(uintptr_t address)
	{
		char buffer[64];
		this->read_virtual(handle, (void*)address, &buffer, sizeof(buffer), 0);
		const auto& it = std::find(buffer, buffer + 64, '\0');

		if (it != buffer + 64)
			return std::string(buffer, it);
	}

	bool process_opened(std::string process_name)
	{
		if (get_process_id(process_name) != 0)
			return true;

		return false;
	}

	bool window_focused(std::string target)
	{

		HWND hwnd = GetForegroundWindow();

		char title[256];
		GetWindowText(hwnd, title, sizeof(title));

		if (strstr(title, target.c_str()) != nullptr)
			return true;

		return false;
	}

};

inline Memory process("cs2.exe");