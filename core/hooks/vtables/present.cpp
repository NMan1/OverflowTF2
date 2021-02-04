#include "..\hook.hpp"
#include "../../interfaces/interfaces.hpp"
#include "../../menu/menu.hpp"

extern LRESULT ImGui_ImplDX9_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
bool menu_key_pressed = true;

long __stdcall hooks::d3d::present::fn(IDirect3DDevice9* device, const RECT* source_rect, const RECT* dest_rect, HWND dest_window_override, const RGNDATA* dirty_region) {
	static auto init = false;
	if (!init) {
		menu::setup_fonts();
		menu::setup_resent(device);
		init = true;
	}

	menu::pre_render(device);
	menu::post_render();

	if (GetAsyncKeyState(VK_INSERT) & 1) {
		menu::open = !menu::open;
		interfaces::surface->set_cursor_always_visible(menu::open);
	}

	if (menu::open) {
		menu::render();
	}

	menu::end_present(device);

	return m_present->get_original<t>(index)(device, source_rect, dest_rect, dest_window_override, dirty_region);
}

long __stdcall hooks::d3d::reset::fn(IDirect3DDevice9* device, D3DPRESENT_PARAMETERS* present_parameters) {
	menu::invalidate_objects();
	const auto hr = m_reset->get_original<t>(index)(device, present_parameters);
	menu::create_objects(device);
	return hr;
}

void __stdcall hooks::d3d::lock_cursor::fn() {
	menu::open ? interfaces::surface->unlock_cursor() : m_lock_cursor->get_original<t>(index)(interfaces::surface);
}

LRESULT __stdcall hooks::d3d::wnd_proc::wnd_proc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam) {
	if (menu::open && ImGui_ImplDX9_WndProcHandler(hwnd, message, wparam, lparam))
		return true;

	return CallWindowProcA(old_wnd_proc, hwnd, message, wparam, lparam);
}