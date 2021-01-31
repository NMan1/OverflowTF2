#include "..\hook.hpp"
#include "..\..\interfaces\interfaces.hpp"
#include "../../utils/game/draw.hpp"

void __fastcall hooks::panel::paint_traverse::fn(PVOID panels, int edx, unsigned int vgui_panel, bool force_repaint, bool allow_force) {

	m_paint_traverse->get_original<t>(index)(panels, vgui_panel, force_repaint, allow_force);

	//static auto focus_overlay_panel_index = NULL;

	//if (!focus_overlay_panel_index) {
	//	if (!strcmp(interfaces::panels->get_name(vgui_panel), "FocusOverlayPanel")) {
	//		focus_overlay_panel_index = vgui_panel;
	//		utils::log((std::string("[-] Found Panel: ") + interfaces::panels->get_name(vgui_panel)).c_str());
	//		draw::init();
	//	}
	//}
	//else if (focus_overlay_panel_index == vgui_panel) {
	//	interfaces::panels->set_top_most_popup(focus_overlay_panel_index, true);

	//	draw::text("Overflow", vector2D(10, 10), color(255, 0, 0));

	// esp::run();
	//}
}
