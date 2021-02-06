#pragma once
#include "..\..\utils\utils.hpp"

typedef unsigned short MaterialHandle_t;
class i_material;
class key_values;

class c_material_system
{
public:
	i_material* find(char const* szMat, const char* szTextureGroup, bool bComplain = true, const char* szPrefix = NULL)
	{
		typedef i_material* (__thiscall* fn)(void*, const char*, const char*, bool, const char*);
		return utils::get_vfunc<fn>(this, 73)(this, szMat, szTextureGroup, bComplain, szPrefix);
	}

	i_material* create(char const* szName, key_values* pKV)
	{
		typedef i_material* (__thiscall* fn)(void*, const char*, key_values*);
		return utils::get_vfunc<fn>(this, 72)(this, szName, pKV);
	}

	i_material* get(MaterialHandle_t hMat)
	{
		typedef i_material* (__thiscall* fn)(void*, MaterialHandle_t);
		return utils::get_vfunc<fn>(this, 78)(this, hMat);
	}

	MaterialHandle_t first()
	{
		typedef MaterialHandle_t(__thiscall* fn)(void*);
		return utils::get_vfunc<fn>(this, 75)(this);
	}

	MaterialHandle_t invalid()
	{
		typedef MaterialHandle_t(__thiscall* fn)(void*);
		return utils::get_vfunc<fn>(this, 77)(this);
	}

	MaterialHandle_t next(MaterialHandle_t hMat)
	{
		typedef MaterialHandle_t(__thiscall* fn)(void*, MaterialHandle_t);
		return utils::get_vfunc<fn>(this, 76)(this, hMat);
	}
};
