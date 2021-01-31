#include "esp.hpp"

namespace esp {
	void box_esp(c_base_entity* entity);

	void misc_esp(c_base_entity* entity);

	void run() {
		auto local_player = interfaces::entity_list->get_client_entity(interfaces::engine->get_local_player());

		if (!local_player) {
			return;
		}

		for (int i = 1; i <= interfaces::engine->get_max_clients(); i++) {
			auto entity = interfaces::entity_list->get_client_entity(i);
			if (!entity || entity == local_player || entity->is_dormant()) {
				continue;
			}

			if (entity->get_life_state() != LIFE_ALIVE) {
				continue;
			}

			if (entity->get_team_num() == local_player->get_team_num()) {
				continue;
			}

			box_esp(entity);
			misc_esp(entity);
		}
	}

	void box_esp(c_base_entity* entity) {
		vector	 vec_bottom;
		vector_2d vec_screen_bottom;
		vector_2d vec_screen_origin;
		auto vec_origin{ vec_bottom = entity->get_origin() };

		constexpr auto DUCK{ 54.f };
		constexpr auto STAND{ 72.f };
		constexpr auto EWIDTH{ 1.5f };

		if ((entity->get_flags() & FL_DUCKING)) {
			vec_bottom.z += DUCK;
		}
		else {
			vec_bottom.z += STAND;
		}

		if (!draw::w2s(vec_bottom, vec_screen_bottom) || !draw::w2s(vec_origin, vec_screen_origin)) {
			return;
		}

		const auto line_height = (vec_screen_origin.y - vec_screen_bottom.y);
		auto edge_width = line_height / 4;
		const auto line_width = edge_width;

		edge_width /= EWIDTH;

		auto top_left = vector_2d(vec_screen_origin.x - line_width - LINE_WIDTH, vec_screen_bottom.y);
		auto top_right = vector_2d(vec_screen_origin.x + line_width, vec_screen_bottom.y);
		auto bottom_left = vector_2d(vec_screen_origin.x - line_width, vec_screen_origin.y);
		auto bottom_right = vector_2d(vec_screen_origin.x + line_width, vec_screen_origin.y);

		draw::box(top_left, bottom_right, get_team_color(entity), 2);
	}

	void misc_esp(c_base_entity* entity) {
		int screen_x, screen_y;
		interfaces::engine->get_screen_size(screen_x, screen_y);

		vector_2d origin_screen;
		if (draw::w2s(entity->get_origin(), origin_screen)) {
			draw::line(screen_x / 2, screen_y, origin_screen.x, origin_screen.y, get_team_color(entity));
			draw::text(get_class_name_string(entity->get_class_name()), origin_screen, color(255, 255, 255), 17, true);
		}
	}
}