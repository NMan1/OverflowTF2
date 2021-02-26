#define NOMINMAX 
#include "aimbot.hpp"
#include "..\..\interfaces\interfaces.hpp"
#include "..\..\utils\math\math.hpp"
#include "..\..\utils\game\helpers.hpp"
#include "../../utils/settings/settings.hpp"
#include "..\..\source-sdk\interfaces\c_base_combat_weapon.hpp"

namespace aimbot {
	c_base_entity* get_closest_to_crosshair(c_base_entity* local_player, const vector view_angles, int settings_fov) {
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
			if (delta < max_delta && delta < settings_fov) {
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
			float delta = math::calc_angle(local_player->get_shoot_pos(), target->get_hitbox_pos(i), view_angles).length();
			if (delta < max_delta) {
				max_delta = delta;
				best_hitbox = i;
			}
		}
		return best_hitbox;
	}

	bool is_position_visible(c_base_entity* local_player ,const vector& source) {
		trace_t trace;
		ray_t ray;			 // the future of variable naming
		c_trace_filter filter;

		filter.skip = local_player;

		auto local_eye = local_player->get_eye_position();
		ray.init(local_eye, source);

		interfaces::trace->trace_ray(ray, MASK_SOLID, &filter, &trace);

		return !trace.did_hit();
	}

	vector predict_position(const vector& source, const vector& destination, const vector& target_velocity, const float projectile_speed, const float projectile_gravity) {
		const auto distance = source.dist_to(destination);
		const auto travel_time = distance / projectile_speed;
		auto pred_destination = destination + (target_velocity)*travel_time;

		pred_destination.y += 0.5f * std::fabsf(projectile_gravity) * travel_time * travel_time;

		return pred_destination;
	}

	void run(c_base_entity* local_player, c_user_cmd* cmd) {
		if (local_player->is_bonked() || local_player->is_taunting()) {
			return;
		}

		float projectile_speed = 0.0f, projectile_gravity = 0.0f;
		auto is_projectile_weapon = get_projectile_info(local_player, projectile_speed, projectile_gravity);

		auto target = get_closest_to_crosshair(local_player, cmd->viewangles, is_projectile_weapon ? settings::aimbot_proj_fov : settings::aimbot_fov);
		if (!target) {
			return;
		}

		const auto hitbox_id = settings::aimbot_bone == 0 ? get_closest_hibox(local_player, target, cmd->viewangles) : hitboxes::HEAD;

		if (settings::aimbot_proj && is_projectile_weapon) {
			// projectile

			auto target_position = target->get_hitbox_pos(hitbox_id);
			if (local_player->get_class_number() == tf_classes::CLASS_SOLDIER) {
				target_position = settings::aimbot_proj_launcher_bone == 1 ? target->get_abs_origin() + vector(0, 0, 15.0f) : target->get_abs_origin();
			}

			auto predicited_position = predict_position(local_player->get_eye_position(), target_position, target->get_velocity(), projectile_speed, projectile_gravity);
			if (!is_position_visible(local_player, predicited_position)) {
				return;
			}

			auto angle = math::calc_angle_projectile(local_player->get_eye_position(), predicited_position);
			math::clamp_angles(angle);

			if (settings::aimbot_proj_smoothness > 0) {
				angle /= (settings::aimbot_proj_smoothness * 5);
			}

			cmd->viewangles = angle;
		}
		else {
			// normal

			auto angle = math::calc_angle(local_player->get_eye_position(), target->get_hitbox_pos(hitbox_id), cmd->viewangles);
			math::clamp_angles(angle);

			if (settings::aimbot_smoothness > 0) {
				angle /= (settings::aimbot_smoothness * 5);
			}

			cmd->viewangles += angle;
		}
	}
}