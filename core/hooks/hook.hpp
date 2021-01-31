#include <d3d9.h>
#include "../utils/game/misc.hpp"
#include "..\memory\memory.hpp"
#include "../source-sdk/EngineVGui.h"

namespace hooks {
	void hook();
	void unhook();

	namespace client_mode {
		namespace create_move {
			constexpr int index = 21u;
			using t = bool(__stdcall*)(float, CUserCmd*);
			bool __stdcall fn(float flInputSampleTime, CUserCmd* cmd);
		}
	}

	namespace panel {
		namespace paint_traverse {
			constexpr int index = 41u;
			using t = void(__thiscall*)(PVOID panels, unsigned int, bool, bool);
			void __fastcall fn(PVOID panels, int edx, unsigned int vgui_panel, bool force_repaint, bool allow_force);
		}
	}

	namespace engine_vgui {
		namespace paint {
			constexpr int index = 13;
			using t = void(__thiscall*)(IEngineVGui*, int);
			void __stdcall fn(int mode);
		}
	}

	extern std::unique_ptr<memory::hook_t> m_client_mode;
	extern std::unique_ptr<memory::hook_t> m_paint_traverse;
	extern std::unique_ptr<memory::hook_t> m_paint;
}