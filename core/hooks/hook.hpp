#include <d3d9.h>
#include "..\source-sdk\structs\structs.hpp"
#include "..\utils\memory\memory.hpp"
#include "..\source-sdk\interfaces\i_engine_vgui.hpp"

class i_surface;
class draw_model_state;
class model_render_info;
class c_model_render;

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

	namespace model_render {
		namespace dme {
			constexpr int index = 19u;
			using t = void(__thiscall*)(c_model_render*, draw_model_state&, model_render_info&, matrix3x4*);
			void __stdcall fn(draw_model_state& state, model_render_info& info, matrix3x4* bone_to_world);
		}
	}

	namespace d3d {
		namespace present {
			constexpr int index = 0u;
			using t = long(__stdcall*)(IDirect3DDevice9*, const RECT*, const RECT*, HWND, const RGNDATA*);
			long __stdcall fn(IDirect3DDevice9* device, const RECT* source_rect, const RECT* dest_rect, HWND dest_window_override, const RGNDATA* dirty_region);
		}		
		
		namespace reset {
			constexpr int index = 0u;
			using t = long(__stdcall*)(IDirect3DDevice9*, D3DPRESENT_PARAMETERS*);
			long __stdcall fn(IDirect3DDevice9* device, D3DPRESENT_PARAMETERS* present_parameters);
		}		
		
		namespace lock_cursor {
			constexpr int index = 62u;
			using t = void(__thiscall*)(i_surface*);
			void __stdcall fn();
		}

		namespace wnd_proc {
			LRESULT __stdcall wnd_proc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam);
			extern WNDPROC old_wnd_proc;
		}
	}

	extern std::unique_ptr<memory::hook_t> m_client_mode;
	extern std::unique_ptr<memory::hook_t> m_paint_traverse;
	extern std::unique_ptr<memory::hook_t> m_paint;
	extern std::unique_ptr<memory::hook_t> m_dme;
	extern std::unique_ptr<memory::hook_t> m_present;
	extern std::unique_ptr<memory::hook_t> m_reset;
	extern std::unique_ptr<memory::hook_t> m_lock_cursor;
}