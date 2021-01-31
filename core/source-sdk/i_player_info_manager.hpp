#pragma once
#include "i_base_client_dll.hpp"

class i_player_info_manager
{
public:
	i_global_vars* get_global_vars()
	{
		typedef i_global_vars* (__thiscall* fn)(void*);
		return utils::get_vfunc<fn>(this, 1)(this);
	}
};