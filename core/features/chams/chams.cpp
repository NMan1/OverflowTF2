#include "chams.hpp"

namespace chams {
	void run(model_render_info& info, const char* model_name) {
		if (!info.m_pModel) {
			return;
		}

		auto entity = interfaces::entity_list->get_client_entity(info.m_nEntIndex);
		if (!entity) {
			return;
		}

		static auto material = interfaces::material_system->find("models/player/shared/gold_player", "Model textures");
		if (!material) {
			return;
		}

		auto class_id = entity->get_client_class()->class_id;

		if (class_id == class_ids::CTFPlayer) {
			if (entity->is_player() && entity->is_alive()) {
				float clr[3] = { 89 / 255.0f, 200 / 255.0f, 10 / 255.0f };

				material->set_material_var_flag(MATERIAL_VAR_IGNOREZ, false);
				material->color_modulate(clr[0], clr[1], clr[2]);
				material->increment_reference_count();

				interfaces::render_view->set_blend(255);
				interfaces::render_view->set_color_modulation(clr);
				interfaces::model_render->forced_material_override(material);
			}
		}
		else if (class_id == class_ids::CTFViewModel) {
			interfaces::model_render->forced_material_override(material);
		}	
	}
}