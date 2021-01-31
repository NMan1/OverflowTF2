#include "interfaces.hpp"

namespace interfaces {
	IBaseClientDLL*			client_dll = nullptr;
	IVEngineClient*			engine = nullptr;
	IClientEntityList*		entity_list = nullptr;
	IGlobalVars*			globals = nullptr;
	IClientModeShared*		client_mode = nullptr;
	Panel*					panels = nullptr;
	ISurface*				surface = nullptr;
	IEngineVGui*			engine_vgui = nullptr;
	IVDebugOverlay*			debug_overlay = nullptr;
	IPlayerInfoManager*		player_info = nullptr;

	using original_fn = void* (*)(const char*, int*);

	template <typename t = void*>
	t get_interface(const char* module_name, const char* interface_name) {
		void* (*create_interface)(const char*, int*) = reinterpret_cast<original_fn>(GetProcAddress(
			GetModuleHandleA(module_name), "CreateInterface"));
		return reinterpret_cast<t>(create_interface(interface_name, nullptr));
	}

	void* brute_iface(const char* name, const char* interfacen, const char* ptr_name, const char* pinterface)
	{
		std::string strininterface = "";
		std::string interface_version = "0";

		for (int i = 0; i <= 99; i++)
		{
			strininterface = interfacen;
			strininterface += interface_version;
			strininterface += std::to_string(i);

			original_fn create_interface = (original_fn)GetProcAddress(GetModuleHandleA(pinterface), "CreateInterface");

			void* func_ptr{ create_interface(strininterface.c_str(), NULL) };

			if ((DWORD)func_ptr != 0x0)
				return func_ptr;

			if (i >= 99 && interface_version == "0")
			{
				interface_version = "00";
				i = 0;
			}
			else if (i >= 99 && interface_version == "00") { printf("error"); }
		}
		return FALSE;
	}

	void init_interfaces()
	{
		client_dll = get_interface<IBaseClientDLL*>("client.dll", "VClient017");
		engine = static_cast<IVEngineClient*>(brute_iface("EngineClient", "VEngineClient", "pEngine", "engine.dll"));
		entity_list = get_interface<IClientEntityList*>("client.dll", "VClientEntityList003");
		panels = get_interface<Panel*>("vgui2.dll", "VGUI_Panel009");
		surface = get_interface<ISurface*>("vguimatsurface.dll", "VGUI_Surface030");
		engine_vgui = get_interface<IEngineVGui*>("engine.dll", "VEngineVGui001");
		debug_overlay = get_interface<IVDebugOverlay*>("engine.dll", "VDebugOverlay003");
		player_info = get_interface<IPlayerInfoManager*>("server.dll", "PlayerInfoManager002");

		const auto dw_chl_client_table = reinterpret_cast<DWORD*>(*reinterpret_cast<DWORD*>(client_dll));
		client_mode = **reinterpret_cast<IClientModeShared***>(static_cast<DWORD>(dw_chl_client_table[10]) + 0x05);
		globals = player_info->get_global_vars();

		utils::log("[-] Grabbed Interfaces");
	}
}

