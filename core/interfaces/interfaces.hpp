#pragma once

#include "..\source-sdk\interfaces\c_handle.hpp"
#include "..\source-sdk\interfaces\i_client_networkable.hpp"
#include "..\source-sdk\interfaces\i_base_client_dll.hpp"
#include "..\source-sdk\interfaces\iv_engine_client.hpp"
#include "..\source-sdk\interfaces\i_panels.hpp"
#include "..\source-sdk\interfaces\i_surface.hpp"
#include "..\source-sdk\interfaces\iv_debug_overlay.hpp"
#include "..\source-sdk\interfaces\i_player_info_manager.hpp"
#include "..\source-sdk\interfaces\i_engine_vgui.hpp"
#include "..\source-sdk\interfaces\c_model_info.hpp"
#include "../source-sdk/interfaces/iv_render_view.hpp"
#include "../source-sdk/interfaces/c_game_movement.hpp"
#include "../source-sdk/interfaces/i_entity_list.hpp"
#include "../source-sdk/interfaces/c_model_render.hpp"

namespace interfaces {
	extern i_base_client_dll*		client_dll;
	extern iv_engine_client*		engine;
	extern i_client_entity_list*	entity_list;
	extern i_global_vars*			globals;
	extern i_client_mode_shared*	client_mode;
	extern i_panel*					panels;
	extern i_surface*				surface;
	extern i_engine_vgui*			engine_vgui;
	extern iv_debug_overlay*		debug_overlay;
	extern i_player_info_manager*	player_info;
	extern c_model_info_client*		model_info;
	extern i_engine_trace*			trace;
	extern iv_render_view*			render_view;
	extern c_game_movement*			game_movement;
	extern c_model_render*			model_render;

	void init_interfaces();
}