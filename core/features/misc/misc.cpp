#include "misc.h"
#include "..\..\source-sdk\interfaces\c_base_combat_weapon.hpp"

namespace misc {
	void bunny_hop(c_base_entity* local_player, c_user_cmd* cmd) {
		static bool released = true;

		if (!local_player) {
			return;
		}

		if (cmd->buttons & IN_JUMP) {
			if (!released) {
				if (!(local_player->get_flags() & entity_flags::GROUND))
					cmd->buttons &= ~(1 << 1);
			}
			else {
				released = false;
			}
		}
		else if (!released) {
			released = true;
		}
	}

	void auto_backstab(c_base_entity* local_player, c_user_cmd* cmd) {
		if (local_player->get_active_weapon()->get_item_definition_index() != weapon_type::KNIFE) {
			return;
		}

		for (int i = 1; i < interfaces::engine->get_max_clients(); i++) {
			auto entity = interfaces::entity_list->get_client_entity(i);

			ray_t ray;
			trace_t trace;
			c_trace_filter filter;

			filter.skip = local_player;
			ray.init(local_player->get_eye_position(), entity->get_hitbox_pos(hitboxes::BODY));

			interfaces::trace->trace_ray(ray, MASK_SOLID, &filter, &trace);

			if (trace.entity == entity) {
				if (trace.hitbox == hitboxes::BODY) {
					if (trace.startpos.dist_to(trace.endpos) <= local_player->get_active_weapon()->get_weapon_data().range) {
						cmd->buttons |= IN_ATTACK;
					}
				}
			}
		}
	}
}