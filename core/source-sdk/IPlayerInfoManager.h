#pragma once

class IPlayerInfoManager
{
public:
	IGlobalVars* get_global_vars()
	{
		typedef IGlobalVars* (__thiscall* OriginalFn)(PVOID);
		return utils::get_vfunc<OriginalFn>(this, 1)(this);
	}
};