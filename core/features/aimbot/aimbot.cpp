#include "aimbot.h"
#include "..\..\utils\math\math.hpp"
#include "../../utils/settings/settings.h"

namespace aimbot {
	c_base_entity* get_closest_to_crosshair(c_base_entity* local_player, vector& aim_angle) {
		c_base_entity* best_entity = nullptr;
		float max_delta = FLT_MAX;
		float delta = NULL;

		vector view_angles = {};
		interfaces::engine->get_view_angles(view_angles);

		for (int i = 1; i <= interfaces::engine->get_max_clients(); i++) {
			auto entity = interfaces::entity_list->get_client_entity(i);

			if (!entity || entity == local_player || !entity->is_alive() || entity->is_dormant()) {
				continue;
			}

			if (entity->get_team_num() == local_player->get_team_num()) {
				continue;
			}

			if (!entity->is_visible(local_player, hitboxes::HEAD)) {
				continue;
			}

			vector angle = math::calc_angle(local_player->get_shoot_pos(), entity->get_hitbox_pos(hitboxes::HEAD));
			auto distance = local_player->get_eye_position().dist_to(entity->get_hitbox_pos(hitboxes::HEAD));
			delta = math::calc_fov(distance, view_angles, angle);

			if (delta < max_delta && delta < settings::aimbot_fov) {
				max_delta = delta;
				best_entity = entity;
				aim_angle = angle;
			}
		}
		return best_entity;
	}

	c_base_entity* get_closest_distance(c_base_entity* local_player) {
		return nullptr;
	}

	void run(c_user_cmd* cmd) {
		auto local_player = interfaces::entity_list->get_client_entity(interfaces::engine->get_local_player());
		if (!local_player || !local_player->is_alive()) {
			return;
		}

		if (local_player->is_bonked() || local_player->is_taunting()) {
			return;
		}

		vector aim_angle = {};
		auto target = get_closest_to_crosshair(local_player, aim_angle);
		if (!target) {
			return;
		}

		math::clamp_angles(aim_angle);
		vector delta = aim_angle - cmd->viewangles;
		math::clamp_angles(delta);
		vector result = delta - delta * (settings::aimbot_smoothness / 2);

		cmd->viewangles += result;
	}
}