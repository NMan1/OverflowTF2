#include "interfaces.hpp"

namespace interfaces {
	i_base_client_dll*			client_dll = nullptr;
	iv_engine_client*			engine = nullptr;
	i_client_entity_list*		entity_list = nullptr;
	i_global_vars*				globals = nullptr;
	i_client_mode_shared*		client_mode = nullptr;
	i_panel*					panels = nullptr;
	i_surface*					surface = nullptr;
	i_engine_vgui*				engine_vgui = nullptr;
	iv_debug_overlay*			debug_overlay = nullptr;
	i_player_info_manager*		player_info = nullptr;
	c_model_info_client*		model_info = nullptr;
	i_engine_trace*				trace = nullptr;
	iv_render_view*				render_view = nullptr;
	c_game_movement*			game_movement = nullptr;
	c_model_render*				model_render = nullptr;

	template <typename t = void*>
	t get_interface(const char* module_name, const char* interface_name) {
		using fn = void* (*)(const char*, int*);
		void* (*create_interface)(const char*, int*) = reinterpret_cast<fn>(GetProcAddress(GetModuleHandleA(module_name), "CreateInterface"));
		return reinterpret_cast<t>(create_interface(interface_name, nullptr));
	}

	void init_interfaces() {
		client_dll		= get_interface<i_base_client_dll*>("client.dll", "VClient017");
		engine			= get_interface<iv_engine_client*>("engine.dll", "VEngineClient013");
		entity_list		= get_interface<i_client_entity_list*>("client.dll", "VClientEntityList003");
		panels			= get_interface<i_panel*>("vgui2.dll", "VGUI_Panel009");
		surface			= get_interface<i_surface*>("vguimatsurface.dll", "VGUI_Surface030");
		engine_vgui		= get_interface<i_engine_vgui*>("engine.dll", "VEngineVGui001");
		debug_overlay	= get_interface<iv_debug_overlay*>("engine.dll", "VDebugOverlay003");
		player_info		= get_interface<i_player_info_manager*>("server.dll", "PlayerInfoManager002");
		model_info		= get_interface<c_model_info_client*>("engine.dll", "VModelInfoClient006");
		trace			= get_interface<i_engine_trace*>("engine.dll", "EngineTraceClient003");
		render_view		= get_interface<iv_render_view*>("engine.dll", "VEngineRenderView014");
		game_movement	= get_interface<c_game_movement*>("client.dll", "GameMovement001");
		model_render	= get_interface<c_model_render*>("engine.dll", "VEngineModel016");

		const auto dw_chl_client_table = reinterpret_cast<DWORD*>(*reinterpret_cast<DWORD*>(client_dll));
		client_mode = **reinterpret_cast<i_client_mode_shared***>(static_cast<DWORD>(dw_chl_client_table[10]) + 0x05);
		globals = player_info->get_global_vars();

		utils::log("[-] Grabbed Interfaces");
	}
}

