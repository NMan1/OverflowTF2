#pragma once
#include <d3d9.h>

struct ImFont;

namespace menu {
	extern bool open;

	void __stdcall create_objects(IDirect3DDevice9* device);

	void __stdcall invalidate_objects();

	void __stdcall setup_resent(IDirect3DDevice9* device);

	void setup_fonts();

	void __stdcall end_present(IDirect3DDevice9* device);

	void __stdcall pre_render(IDirect3DDevice9* device);

	void __stdcall post_render();

	void render();
}
