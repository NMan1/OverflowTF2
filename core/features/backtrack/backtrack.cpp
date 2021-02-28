#define NOMINMAX 
#include "backtrack.hpp"
#include "..\aimbot\aimbot.hpp"
#include "..\..\interfaces\interfaces.hpp"
#include "..\..\utils\math\math.hpp"
#include "..\..\utils\game\helpers.hpp"
#include "../../utils/settings/settings.hpp"

namespace backtrack {
	std::vector<saved_ticks> player_ticks[64];

	void save_ticks(c_base_entity* local_player, c_user_cmd* cmd) {
		for (int i = 1; i <= interfaces::engine->get_max_clients(); i++) {
			auto entity = interfaces::entity_list->get_client_entity(i);
			if (!entity || !entity->get_health() || entity->get_team_num() == local_player->get_team_num()) {
				continue;
			}

			player_ticks[i].insert(player_ticks[i].begin(), { cmd->tick_count, entity->get_hitbox_pos(hitboxes::HEAD) });
			if (player_ticks[i].size() > 12) {
				player_ticks[i].pop_back();
			}
		}
	}

	void set_backtrack_tick(c_base_entity* local_player, c_user_cmd* cmd) {
		auto max_delta = FLT_MAX;
		auto best_index = -1;
		for (int i = 1; i <= interfaces::engine->get_max_clients(); i++) {
			auto entity = interfaces::entity_list->get_client_entity(i);
			if (!entity || !entity->get_health() || entity->get_team_num() == local_player->get_team_num()) {
				continue;
			}

			float delta = (math::calc_angle_projectile(local_player->get_eye_position(), entity->get_eye_position()) - cmd->viewangles).length();
			if (delta < max_delta) {
				best_index = i;
				max_delta = delta;
			}
		}

		if (best_index == -1) {
			return;
		}

		int best_tick = -1;
		max_delta = FLT_MAX;
		for (int i = 0; i < player_ticks[best_index].size(); i++) {
			float delta = (math::calc_angle_projectile(local_player->get_eye_position(), player_ticks[best_index].at(i).head_position) - cmd->viewangles).length();
			if (delta < max_delta) {
				max_delta = delta;
				best_tick = i;
			}
		}

		if (best_tick != -1 && cmd->buttons & IN_ATTACK) {
			cmd->tick_count = player_ticks[best_index].at(best_tick).tick_number;
		}
	}
}