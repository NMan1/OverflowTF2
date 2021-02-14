#include "..\hook.hpp"
#include "..\..\interfaces\interfaces.hpp"
#include "../../utils/draw/draw.hpp"
#include "../../utils/settings/settings.hpp"
#include "../../features/visuals/esp/esp.hpp"

void __fastcall hooks::panel::paint_traverse::fn(void* panels, int edx, unsigned int vgui_panel, bool force_repaint, bool allow_force) {

	m_paint_traverse->get_original<t>(index)(panels, vgui_panel, force_repaint, allow_force);

	static auto focus_overlay_panel_index = NULL;
	if (!focus_overlay_panel_index) {
		if (!strcmp(interfaces::panels->get_name(vgui_panel), "FocusOverlayPanel")) {
			focus_overlay_panel_index = vgui_panel;
			draw::init();
			utils::log((std::string("[-] Found Panel: ") + interfaces::panels->get_name(vgui_panel)).c_str());
		}
	}
	else if (focus_overlay_panel_index == vgui_panel) {
		draw::text(draw::watermark_font, "Overflow", vector(10, 10), color(255, 0, 0));
		if (interfaces::engine->is_in_game() && interfaces::engine->is_connected() &&
			!interfaces::engine->con_is_visible() && !interfaces::engine_vgui->is_game_ui_visible()) {
			if (settings::visuals) {
				esp::run();
			}
		}
	}
}
