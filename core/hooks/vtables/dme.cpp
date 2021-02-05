#include "..\hook.hpp"
#include "..\..\interfaces\interfaces.hpp"

constexpr float default_color[3] = { 1, 1, 1 };

void __stdcall hooks::model_render::dme::fn(draw_model_state& state, model_render_info& info, matrix3x4* bone_to_world) {
	const char* model_name = interfaces::model_info->get_model_name(info.m_pModel);
	if (!model_name) {
		return;
	}

	m_dme->get_original<t>(index)(interfaces::model_render, state, info, bone_to_world);

	interfaces::render_view->set_blend(0);
	interfaces::render_view->set_color_modulation(default_color);
	interfaces::model_render->forced_material_override(nullptr);
}