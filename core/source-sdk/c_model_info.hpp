#pragma once
#include "iv_engine_client.hpp"
#include "..\utils\utils.hpp"
#include "..\utils\game\structs.hpp"

class c_model_info_client
{
public:
	model_t* get_model(int index)
	{
		typedef model_t* (__thiscall* fn)(PVOID, int);
		return utils::get_vfunc<fn>(this, 1)(this, index);
	}

	int	get_model_index(const char* name)
	{
		typedef int(__thiscall* fn)(PVOID, const char*);
		return utils::get_vfunc<fn>(this, 2)(this, name);
	}

	const char* get_model_name(const model_t* model)
	{
		typedef const char* (__thiscall* fn)(PVOID, const model_t*);
		return utils::get_vfunc<fn>(this, 3)(this, model);
	}

	studiohdr_t* get_studio_model(const model_t* model)
	{
		typedef studiohdr_t* (__thiscall* fn)(PVOID, const model_t*);
		return utils::get_vfunc<fn>(this, 28)(this, model);
	}
};
