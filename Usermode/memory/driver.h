#pragma once
#include "defines.h"
#include <stdio.h>

class Driver {
	HANDLE handle = 0;

	int process_id = 0;
public:

	Driver() {
		handle = CreateFile("\\\\.\\infestation", GENERIC_WRITE | GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, NULL, NULL);
	}

	~Driver() {
		CloseHandle(handle);
	}

	int get_process_id(const char* process_name) {
		KPROCESSID_REQUEST request;
		request.process_name = process_name;

		DWORD bytes_returned;
		DeviceIoControl(handle, PROCESSID_REQUEST, &request, sizeof(request), NULL, NULL, &bytes_returned, NULL);
		process_id = (int)bytes_returned;
		return process_id;
	}



	uintptr_t get_module_base(int pid, UNICODE_STRING module_name, BOOL get_size) {
		_KERNEL_MODULE_REQUEST request = { 0 };
		request.pid = pid;
		request.module_name = module_name;
		request.get_size = get_size;

		DWORD bytes_returned;

		DeviceIoControl(handle, MODULEBASE_REQUEST, &request, sizeof(request), NULL, NULL, &bytes_returned, NULL);

		return (uintptr_t)bytes_returned;
	}



	template <typename T>
	T readv(uintptr_t address) {
		T buffer{ };
		_KERNEL_READ_REQUEST request;
		request.src_pid = process_id;
		request.src_address = address;
		request.p_buffer = &buffer;
		request.size = sizeof(T);

		if (DeviceIoControl(handle, READ_REQUEST, &request, sizeof(request), &request, sizeof(request), NULL, NULL))
			return buffer;
		return 0;
	}

	void move(long x, long y, unsigned char button_flags) {
		KMOUSE_REQUEST request;
		request.x = x;
		request.y = y;
		request.button_flags = button_flags;

		DeviceIoControl(handle, MOUSE_REQUEST, &request, sizeof(request), NULL, NULL, NULL, NULL);
	}

};

inline Driver driver;