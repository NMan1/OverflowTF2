#pragma once
#include <d3d9.h>
#include "imgui/imgui.h"
#include "imgui/dx9/imgui_impl_dx9.h"

namespace menu {
	extern bool open;

	extern ImVec2 menu_size;

	extern IDirect3DStateBlock9* state_block;

	extern ImFont* font_title;
	extern ImFont* font_large_menu;
	extern ImFont* font_child_title;
	extern ImFont* font_menu;
	extern ImFont* font_bottom_info;
	extern ImFont* font_spectators;

	void __stdcall create_objects(IDirect3DDevice9* device);

	void __stdcall invalidate_objects();

	void __stdcall setup_resent(IDirect3DDevice9* device);

	void setup_fonts();

	float clip(float n, float lower, float upper);

	void __stdcall end_present(IDirect3DDevice9* device);

	void __stdcall pre_render(IDirect3DDevice9* device);

	void __stdcall post_render();

	void render();

	void change_log();

	void legit_tab();

	void rage_tab();

	void visuals_tab();

	void misc_tab();

	void skins_tab();

	void settings_tab();
}
