#include "hook.hpp"
#include "..\interfaces\interfaces.hpp"
#include "../utils/netvars/netvars.hpp"

namespace hooks {
	std::unique_ptr<memory::hook_t> m_client_mode = nullptr;
	std::unique_ptr<memory::hook_t> m_paint_traverse = nullptr;
	std::unique_ptr<memory::hook_t> m_paint = nullptr;

	void hook() {

		// Create netvar manager
		g_netvar = std::make_unique<netvar>();

		// Client mode hooks
		m_client_mode = std::make_unique<memory::hook_t>(interfaces::client_mode);
		m_client_mode->hook(client_mode::create_move::index, client_mode::create_move::fn);
		
		// Panel hooks
		m_paint_traverse = std::make_unique<memory::hook_t>(interfaces::panels);
		m_paint_traverse->hook(panel::paint_traverse::index, panel::paint_traverse::fn);

		// EngineVGui Hooks
		m_paint = std::make_unique<memory::hook_t>(interfaces::engine_vgui);
		m_paint->hook(engine_vgui::paint::index, engine_vgui::paint::fn);

		utils::log("[-] Hooks Applied");
	}

	void unhook() {
		m_client_mode->unhook();
		m_paint_traverse->unhook();
		m_paint->unhook();
		g_netvar.reset();
		utils::log("[-] Hooks unapplied");
	}
}
