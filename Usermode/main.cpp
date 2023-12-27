#include <iostream>
#include <thread>
#include "features/globals.h"
#include "memory/driver.h"
#include "memory/memory.h"
#include "overlay/render.h"
#include "features/cheat.h"

int main() {

	SetConsoleTitleA("CS2 - External");

	while (entry_hwnd == NULL) {
		printf("[+] Open the game\r");
		//processid = driver.get_process_id("cs2.exe");
		processid = process.get_procid();
		entry_hwnd = get_process_wnd(processid);
	}

	//UNICODE_STRING module_name;
	//RtlInitUnicodeString(&module_name, L"client.dll");
	//client = driver.get_module_base(processid, module_name, 0); // 0 - get base, 1 - get size
	client = process.get_modulebase("client.dll");


#if NDEBUG
	ShowWindow(GetConsoleWindow(), SW_HIDE);
#endif

	setup_window();
	init_wndparams(own_hwnd);
	std::thread(cache_entities).detach();
	main_loop();
	return 0;
}

