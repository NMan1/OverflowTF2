#include <d3d9.h>
#include "..\source-sdk\structs\structs.hpp"
#include "..\utils\memory\memory.hpp"
#include "..\source-sdk\interfaces\i_engine_vgui.hpp"

namespace hooks {
	void hook();
	void unhook();

	namespace client_mode {
		namespace create_move {
			constexpr int index = 21u;
			using t = bool(__stdcall*)(float, c_user_cmd*);
			bool __stdcall fn(float flInputSampleTime, c_user_cmd* cmd);
		}
	}

	namespace panel {
		namespace paint_traverse {
			constexpr int index = 41u;
			using t = void(__thiscall*)(void* panels, unsigned int, bool, bool);
			void __fastcall fn(void* panels, int edx, unsigned int vgui_panel, bool force_repaint, bool allow_force);
		}
	}

	namespace engine_vgui {
		namespace paint {
			constexpr int index = 13;
			using t = void(__thiscall*)(i_engine_vgui*, int);
			void __stdcall fn(int mode);
		}
	}

	extern std::unique_ptr<memory::hook_t> m_client_mode;
	extern std::unique_ptr<memory::hook_t> m_paint_traverse;
	extern std::unique_ptr<memory::hook_t> m_paint;
}