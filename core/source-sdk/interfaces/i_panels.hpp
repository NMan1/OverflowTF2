#pragma once
#include <d3d9.h>
#include "../../utils/utils.hpp"

class i_panel
{
public:
	unsigned int get_panel(int type)
	{
		typedef unsigned int(__thiscall* fn)(void*, int type);
		return utils::get_vfunc<fn>(this, 1)(this, type);
	}

	void set_mouse_input_enabled(unsigned int panel, bool state)
	{
		utils::get_vfunc<void(__thiscall*)(void*, int, bool)>(this, 32)(this, panel, state);
	}

	void set_top_most_popup(unsigned int panel, bool state)
	{
		utils::get_vfunc<void(__thiscall*)(void*, int, bool)>(this, 59)(this, panel, state);
	}

	const char* get_name(unsigned int vguipanel)
	{
		typedef const char* (__thiscall* fn)(void*, unsigned int);
		return utils::get_vfunc<fn>(this, 36)(this, vguipanel);
	}
};