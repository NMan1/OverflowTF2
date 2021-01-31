#include "..\hook.hpp"
#include "..\..\interfaces\interfaces.hpp"
#include "..\..\utils\game\draw.hpp"
#include "..\..\features\visuals\esp.hpp"

void __stdcall hooks::engine_vgui::paint::fn(int mode) {
	static auto start_drawing = reinterpret_cast<void(__thiscall*)(void*)>(memory::find_pattern("vguimatsurface.dll", "55 8B EC 64 A1 ? ? ? ? 6A FF 68 ? ? ? ? 50 64 89 25 ? ? ? ? 83 EC 14"));
	static auto finish_drawing = reinterpret_cast<void(__thiscall*)(void*)>(memory::find_pattern("vguimatsurface.dll", "55 8B EC 6A FF 68 ? ? ? ? 64 A1 ? ? ? ? 50 64 89 25 ? ? ? ? 51 56 6A 00"));
	static auto init = false;

	if (!init) {
		draw::init();
		init = true;
	}

	m_paint->get_original<t>(index)(interfaces::engine_vgui, mode);

	if (mode & PAINT_UIPANELS) {
		start_drawing(interfaces::surface);

		draw::text("Overflow", vector_2d(10, 10), color(255, 0, 0));
		if (interfaces::engine->is_in_game() && interfaces::engine->is_connected()) {
			esp::run();
		}

		finish_drawing(interfaces::surface);
	}
}