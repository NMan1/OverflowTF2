#pragma once

#include "..\source-sdk\c_handle.hpp"
#include "..\source-sdk\i_client_networkable.hpp"
#include "..\source-sdk\i_base_client_dll.hpp"
#include "..\source-sdk\iv_engine_client.hpp"
#include "..\source-sdk\i_panels.hpp"
#include "..\source-sdk\i_surface.hpp"
#include "..\source-sdk\iv_debug_overlay.hpp"
#include "..\source-sdk\i_player_info_manager.hpp"
#include "..\source-sdk\i_engine_vgui.hpp"
#include "..\source-sdk\c_model_info.hpp"

namespace interfaces {
	extern i_base_client_dll*		client_dll;
	extern iv_engine_client*		engine;
	extern i_client_entityList*		entity_list;
	extern i_global_vars*			globals;
	extern i_client_mode_shared*	client_mode;
	extern i_panel*					panels;
	extern i_surface*				surface;
	extern i_engine_vgui*			engine_vgui;
	extern iv_debug_overlay*		debug_overlay;
	extern i_player_info_manager*	player_info;
	extern c_model_info_client*		model_info;
	extern i_engine_trace*			trace;

	void init_interfaces();
}