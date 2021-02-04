#include <windows.h>
#include <processthreadsapi.h>
#include <thread>
#include "hooks/hook.hpp"
#include "interfaces/interfaces.hpp"

DWORD WINAPI init(void* dll_instance) {
#ifdef _DEBUG      
	AllocConsole();                                
	freopen_s((FILE**)stdin, "CONIN$", "r", stdin);  
	freopen_s((FILE**)stdout, "CONOUT$", "w", stdout); 
														
	SetConsoleTitleA("Debug console");   
#endif

	while (!(utils::tf2_window = FindWindowA("Valve001", nullptr))) {
		std::this_thread::sleep_for(std::chrono::milliseconds(200));
	}

	interfaces::init_interfaces();
	hooks::hook();

	while (!GetAsyncKeyState(VK_END)) {
		std::this_thread::sleep_for(std::chrono::milliseconds(200));
	}

	FreeLibraryAndExitThread(reinterpret_cast<HMODULE>(dll_instance), 0);
}

VOID WINAPI detach()
{
#ifdef _DEBUG
	fclose((FILE*)stdin);
	fclose((FILE*)stdout);

	HWND hwnd = GetConsoleWindow();    
	FreeConsole();                              
	PostMessageW(hwnd, WM_CLOSE, 0, 0); 
#endif
}

BOOL APIENTRY DllMain(HMODULE  dll_instance, unsigned long reason_to_call, void* reserved)
{
	if (reason_to_call == DLL_PROCESS_ATTACH) {
		DisableThreadLibraryCalls(dll_instance);
		if (!CreateThread(nullptr, NULL, init, dll_instance, NULL, nullptr))
			throw std::exception("Error while creating thread.");
	}
	else if (reason_to_call == DLL_PROCESS_DETACH) {
		if (!reserved) {
			hooks::unhook();

			using namespace std::literals::chrono_literals;
			std::this_thread::sleep_for(1s);

			detach();
		}
	}
    return TRUE;
}

