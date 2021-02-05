#pragma once
#include "..\..\utils\utils.hpp"
#include "../structs/enums.hpp"

class i_material;
class draw_model_state;
class model_render_info;
typedef float matrix3x4[3][4];

class c_model_render
{
public:
	void forced_material_override(i_material* mat, override_type type = override_type::OVERRIDE_NORMAL)
	{
		typedef void(__thiscall* fn)(void*, i_material*, override_type);
		return utils::get_vfunc<fn>(this, 1)(this, mat, type);
	}

	void draw_model_execute(const draw_model_state* pState, const model_render_info& pInfo, matrix3x4* pBoneToWorld)
	{
		typedef void(__thiscall* fn)(void*, const draw_model_state*, const model_render_info&, matrix3x4*);
		return utils::get_vfunc<fn>(this, 19)(this, pState, pInfo, pBoneToWorld);
	}
};

