#include "..\hook.hpp"
#include "..\..\interfaces\interfaces.hpp"
#include "../../features/visuals/chams/chams.hpp"
#include "../../utils/settings/settings.hpp"

constexpr float default_color[3] = { 1, 1, 1 };

void __stdcall hooks::model_render::dme::fn(draw_model_state& state, model_render_info& info, matrix3x4* bone_to_world) {
	static auto init = false;
	if (!init) {
		chams::init_materials();
		init = true;
	}

	const char* model_name = interfaces::model_info->get_model_name(info.m_pModel);
	if (!model_name) {
		return;
	}

	if (settings::chams) {
		chams::run(info, model_name);
	}

	m_dme->get_original<t>(index)(interfaces::model_render, state, info, bone_to_world);

	interfaces::render_view->set_blend(1);
	interfaces::render_view->set_color_modulation(default_color);
	interfaces::model_render->forced_material_override(nullptr);
}