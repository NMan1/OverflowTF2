#pragma once
#include <d3d9.h>
#include "../utils/utils.hpp"

class Panel
{
public:
	unsigned int get_panel(int type)
	{
		typedef unsigned int(__thiscall* tGetPanel)(void*, int type);
		return utils::get_vfunc<tGetPanel>(this, 1)(this, type);
	}
	void SetMouseInputEnabled(unsigned int panel, bool state)
	{
		utils::get_vfunc<void(__thiscall*)(void*, int, bool)>(this, 32)(this, panel, state);
	}
	void set_top_most_popup(unsigned int panel, bool state)
	{
		utils::get_vfunc<void(__thiscall*)(void*, int, bool)>(this, 59)(this, panel, state);
	}
	const char* get_name(unsigned int vguiPanel)
	{
		typedef const char* (__thiscall* OriginalFn)(PVOID, unsigned int);
		return utils::get_vfunc<OriginalFn>(this, 36)(this, vguiPanel);
	}
};