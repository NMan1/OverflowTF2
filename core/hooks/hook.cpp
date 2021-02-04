#include "hook.hpp"
#include "..\interfaces\interfaces.hpp"
#include "../utils/netvars/netvars.hpp"
#include "../menu/menu.hpp"

namespace hooks {
	std::unique_ptr<memory::hook_t> m_client_mode = nullptr;
	std::unique_ptr<memory::hook_t> m_paint_traverse = nullptr;
	std::unique_ptr<memory::hook_t> m_paint = nullptr;
	std::unique_ptr<memory::hook_t> m_present = nullptr;
	std::unique_ptr<memory::hook_t> m_reset = nullptr;
	std::unique_ptr<memory::hook_t> m_lock_cursor = nullptr;
	WNDPROC d3d::wnd_proc::old_wnd_proc = nullptr;

	void hook() {
		const auto present = memory::find_pattern("gameoverlayrenderer.dll", "FF 15 ? ? ? ? 8B F8 85 DB") + 0x2;
		const auto reset = memory::find_pattern("gameoverlayrenderer.dll", "FF 15 ? ? ? ? 8B F8 85 FF 78 18") + 0x2;

		// Create netvar manager
		g_netvar = std::make_unique<netvar>();

		// Client mode hooks
		m_client_mode = std::make_unique<memory::hook_t>(interfaces::client_mode);
		m_client_mode->hook(client_mode::create_move::index, client_mode::create_move::fn);
		
		// Panel hooks
		m_paint_traverse = std::make_unique<memory::hook_t>(interfaces::panels);
		m_paint_traverse->hook(panel::paint_traverse::index, panel::paint_traverse::fn);

		// EngineVGui hooks
		m_paint = std::make_unique<memory::hook_t>(interfaces::engine_vgui);
		m_paint->hook(engine_vgui::paint::index, engine_vgui::paint::fn);

		// D3D hooks
		m_present = std::make_unique<memory::hook_t>(present);
		m_present->hook(d3d::present::index, d3d::present::fn);

		m_reset = std::make_unique<memory::hook_t>(reset);
		m_reset->hook(d3d::reset::index, d3d::reset::fn);

		m_lock_cursor = std::make_unique<memory::hook_t>(interfaces::surface);
		m_lock_cursor->hook(d3d::lock_cursor::index, d3d::lock_cursor::fn);

		d3d::wnd_proc::old_wnd_proc = reinterpret_cast<WNDPROC>(
			SetWindowLongPtr((HWND)utils::tf2_window, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(d3d::wnd_proc::wnd_proc)));

		utils::log("[-] Hooks Applied");
	}

	void unhook() {
		menu::open = false;

		m_client_mode->unhook();
		m_paint_traverse->unhook();
		m_paint->unhook();
		m_present->unhook();
		m_reset->unhook();
		m_lock_cursor->unhook();

		SetWindowLongPtr((HWND)utils::tf2_window, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(d3d::wnd_proc::old_wnd_proc));

		g_netvar.reset();
		utils::log("[-] Hooks unapplied");
	}
}