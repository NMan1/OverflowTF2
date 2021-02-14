#include "..\hook.hpp"
#include "..\..\interfaces\interfaces.hpp"
#include "..\..\utils\draw\draw.hpp"
#include "..\..\features\visuals\esp\esp.hpp"
#include "../../utils/settings/settings.hpp"

void __stdcall hooks::engine_vgui::paint::fn(int mode) {
	static auto start_drawing = reinterpret_cast<void(__thiscall*)(void*)>(memory::find_pattern("vguimatsurface.dll", "55 8B EC 64 A1 ? ? ? ? 6A FF 68 ? ? ? ? 50 64 89 25 ? ? ? ? 83 EC 14"));
	static auto finish_drawing = reinterpret_cast<void(__thiscall*)(void*)>(memory::find_pattern("vguimatsurface.dll", "55 8B EC 6A FF 68 ? ? ? ? 64 A1 ? ? ? ? 50 64 89 25 ? ? ? ? 51 56 6A 00"));
	
	static auto init = false;
	if (!init) {
		draw::init();
		init = true;
	}

	m_paint->get_original<t>(index)(interfaces::engine_vgui, mode);

	if (mode & paint_mode::UIPANELS) {
		//{
		//	c_viewsetup view_setup = {};
		//	if (interfaces::client_dll->get_player_view(view_setup)) {
		//		vmatrix WorldToView = {}, ViewToProjection = {}, WorldToPixels = {};
		//		interfaces::render_view->get_matrices_for_view(view_setup, &WorldToView, &ViewToProjection, &utils::world_to_projection, &WorldToPixels);
		//	}
		//}

		start_drawing(interfaces::surface);
		{
			draw::text(draw::watermark_font, L"Overflow", { 10, 10 }, { 255, 0, 0 });
			
			if (interfaces::engine->is_in_game() && interfaces::engine->is_connected() &&
				!interfaces::engine->con_is_visible() && !interfaces::engine_vgui->is_game_ui_visible()) {
				if (settings::visuals) {
					esp::run();
				}
			}
		}
		finish_drawing(interfaces::surface);
	}
}