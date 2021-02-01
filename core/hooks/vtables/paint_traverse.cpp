#include "..\hook.hpp"
#include "..\..\interfaces\interfaces.hpp"

void __fastcall hooks::panel::paint_traverse::fn(void* panels, int edx, unsigned int vgui_panel, bool force_repaint, bool allow_force) {

	m_paint_traverse->get_original<t>(index)(panels, vgui_panel, force_repaint, allow_force);

	static auto focus_overlay_panel_index = NULL;

	if (!focus_overlay_panel_index) {
		if (!strcmp(interfaces::panels->get_name(vgui_panel), "FocusOverlayPanel")) {
			focus_overlay_panel_index = vgui_panel;
			utils::log((std::string("[-] Found Panel: ") + interfaces::panels->get_name(vgui_panel)).c_str());
		}
	}
	else if (focus_overlay_panel_index == vgui_panel) {\

	}
}
