#include "chams.hpp"
#include "..\..\..\source-sdk\interfaces\c_key_values.hpp"

namespace chams {

	i_material* create_material(std::string type, std::string texture, std::string name, bool ignorez, bool nofog, bool model, bool nocull, bool halflambert);

	i_material* gold;

	i_material* normal;

	void run(model_render_info& info, const char* model_name) {
		if (!info.m_pModel) {
			return;
		}

		auto entity = interfaces::entity_list->get_client_entity(info.m_nEntIndex);
		if (!entity) {
			return;
		}

		auto class_id = entity->get_client_class()->class_id;

		if (class_id == class_ids::CTFPlayer) {
			if (entity->is_player() && entity->is_alive()) {
				interfaces::model_render->forced_material_override(gold);
			}
		}
		else if (class_id == class_ids::CTFViewModel) {
			interfaces::model_render->forced_material_override(gold);
		}	
	}

	void init_materials() {
		 gold = interfaces::material_system->find("models/player/shared/gold_player", "Model textures");
		 normal = create_material("VertexLitGeneric", "VGUI/white_additive", "0verflow_normal", false, true, true, true, true);
	}

	i_material* create_material(std::string type, std::string texture, std::string name, bool ignorez, bool nofog, bool model, bool nocull, bool halflambert) {
		std::stringstream material_data;
		material_data << "\"" + type + "\"\n"
						"{\n"
						"\t\"$basetexture\" \"" + texture + "\"\n"
						"\t\"$ignorez\" \"" + std::to_string(ignorez) + "\"\n"
						"\t\"$nofog\" \"" + std::to_string(nofog) + "\"\n"
						"\t\"$model\" \"" + std::to_string(model) + "\"\n"
						"\t\"$nocull\" \"" + std::to_string(nocull) + "\"\n"
						"\t\"$halflambert\" \"" + std::to_string(halflambert) + "\"\n"
						"}\n" << std::flush;

		key_values* keys = (key_values*)malloc(sizeof(key_values));
		key_values::init(keys, type.c_str());
		key_values::load_from_buffer(keys, name.c_str(), material_data.str().c_str());

		auto material = interfaces::material_system->create(name.c_str(), keys);
		//material->increment_reference_count();
		return material;
	}
}