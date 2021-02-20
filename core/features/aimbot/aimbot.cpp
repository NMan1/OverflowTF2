#include "aimbot.hpp"
#include "..\..\interfaces\interfaces.hpp"
#include "..\..\utils\math\math.hpp"
#include "../../utils/settings/settings.hpp"

namespace aimbot {
	c_base_entity* get_closest_to_crosshair(c_base_entity* local_player, const vector view_angles) {
		c_base_entity* best_entity = nullptr;
		float max_delta = FLT_MAX;

		for (int i = 1; i <= interfaces::engine->get_max_clients(); i++) {
			auto entity = interfaces::entity_list->get_client_entity(i);

			if (!entity || entity == local_player || !entity->is_alive() || entity->is_dormant()) {
				continue;
			}

			if (entity->get_team_num() == local_player->get_team_num()) {
				continue;
			}

			if (!entity->is_visible(local_player)) { 
				continue;
			}

			float delta = math::calc_angle(local_player->get_eye_position(), entity->get_eye_position(), view_angles).length();
			if (delta < max_delta && delta < settings::aimbot_fov) {
				max_delta = delta;
				best_entity = entity;
			}
		}
		return best_entity;
	}

	c_base_entity* get_closest_distance(c_base_entity* local_player) {
		return nullptr;
	}

	int get_closest_hibox(c_base_entity* local_player, c_base_entity* target, const vector view_angles) {
		float max_delta = FLT_MAX;
		int best_hitbox = NULL;

		for (int i = hitboxes::HEAD; i != hitboxes::RIGHT_FOREARM; i++) {
			float delta = math::calc_angle(local_player->get_eye_position(), target->get_hitbox_pos(i), view_angles).length();
			if (delta < max_delta) {
				max_delta = delta;
				best_hitbox = i;
			}
		}
		return best_hitbox;
	}

	void run(c_base_entity* local_player, c_user_cmd* cmd) {
		if (local_player->is_bonked() || local_player->is_taunting()) {
			return;
		}

		auto target = get_closest_to_crosshair(local_player, cmd->viewangles);
		if (!target) {
			return;
		}

		auto hitbox_id = settings::aimbot_bone == 0 ? get_closest_hibox(local_player, target, cmd->viewangles) : hitboxes::HEAD;
		auto angle = math::calc_angle(local_player->get_eye_position(), target->get_hitbox_pos(hitbox_id), cmd->viewangles);

		math::clamp_angles(angle);

		if (settings::aimbot_smoothness > 0) {
			angle /= (settings::aimbot_smoothness * 5);
		}

		math::normalize_angle(angle);

		cmd->viewangles += angle;
	}
}