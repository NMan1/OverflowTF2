#include "others.hpp"
#include "..\..\interfaces\interfaces.hpp"
#include "..\..\source-sdk\interfaces\c_base_combat_weapon.hpp"
#include "..\..\utils\memory\memory.hpp"

namespace others {
	std::vector<std::string> get_spectators() {
		auto local_player = interfaces::entity_list->get_client_entity(interfaces::engine->get_local_player());
		if (!local_player || !local_player->is_alive()) {
			return {};
		}

		std::vector<std::string> list = {};
		for (int i = 1; i <= interfaces::engine->get_max_clients(); i++) {
			auto entity = interfaces::entity_list->get_client_entity(i);
			if (!entity || entity == local_player || entity->is_alive()) {
				continue;
			}

			auto handle = entity->get_observer_target();
			if (!handle) {
				continue;
			}

			if (local_player == reinterpret_cast<c_base_entity*>(interfaces::entity_list->get_client_entity_from_handle(handle))) {
				player_info info;
				if (interfaces::engine->get_player_info(entity, &info)) {
					auto mode = entity->get_observer_mode();
					auto type = mode == observer_modes::OBS_MODE_FIRSTPERSON ?
						"(1st) " : mode == observer_modes::OBS_MODE_THIRDPERSON ?
						"(3rd) " : mode == observer_modes::OBS_MODE_DEATHCAM ?
						"(death) " : mode == observer_modes::OBS_MODE_FREEZECAM ?
						"(freeze) " : mode == observer_modes::OBS_MODE_FIXED ?
						"(fixed) " : mode == observer_modes::OBS_MODE_ROAMING ?
						"(roaming) " : "";

					list.push_back(std::string(type) + info.name);
				}
			}
		}
		return list;
	}
}