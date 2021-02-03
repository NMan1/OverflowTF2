#include "esp.hpp"
#include "../../utils/helpers.hpp"
#include "..\..\utils\math\math.hpp"
#include "../../utils/settings/settings.h"

namespace esp {
	void box(c_base_entity* entity);

	void class_name(c_base_entity* entity);

	void snap_lines(c_base_entity* entity);

	void fov_circle(c_base_entity* local_player);

	void object_esp(c_base_entity* entity);

	bool get_item_bounds(c_base_entity* entity, int& x, int& y, int& w, int& h);

	void run() {
		auto local_player = interfaces::entity_list->get_client_entity(interfaces::engine->get_local_player());

		if (!local_player) {
			return;
		}

		fov_circle(local_player);

		for (int i = 1; i <= interfaces::engine->get_max_clients(); i++) {
			auto entity = interfaces::entity_list->get_client_entity(i);

			if (!entity || entity == local_player || entity->is_dormant() || !entity->is_alive()) {
				continue;
			}

			if (entity->get_team_num() == local_player->get_team_num()) {
				continue;
			}

			box(entity);
			snap_lines(entity);
			class_name(entity);
		}

		for (int i = 1; i <= interfaces::entity_list->get_max_entitys(); i++) {
			auto entity = interfaces::entity_list->get_client_entity(i);
			if (!entity || entity->is_player() || !entity->is_alive() || entity->is_dormant()) {
				continue;
			}

			object_esp(entity);
		}
	}

	void box(c_base_entity* entity) {
		/*vector	 vec_bottom;
		vector_2d vec_screen_bottom;
		vector_2d vec_screen_origin;
		auto vec_origin{ vec_bottom = entity->get_origin() };

		constexpr auto DUCK{ 54.f };
		constexpr auto STAND{ 72.f };
		constexpr auto EWIDTH{ 1.5f };

		if ((entity->get_flags() & entity_flags::DUCKING)) {
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
		draw::box(top_left.x - 1, top_left.y - 1, (top_right.x - top_left.x) + 2, (bottom_right.y - top_left.y) + 2, color(0, 0, 0), 2);*/

		int x, y, w, h;
		if (get_item_bounds(entity, x, y, w, h)) {
			draw::box(x, y, w, h, get_team_color(entity));
			draw::box(x - 1, y - 1, w + 2, h + 2, get_team_color(entity));

			draw::box(x - 4 - 2, y, 2, (h / entity->get_max_health()) * entity->get_health(), color(0, 255, 0));
			draw::box(x - 4 - 2, y, 2, h, color(0, 0, 0));
		}
	}

	void snap_lines(c_base_entity* entity) {
		vector_2d origin_screen;
		if (draw::w2s(entity->get_origin(), origin_screen)) {
			draw::line(utils::screen_x / 2, utils::screen_y, origin_screen.x, origin_screen.y, get_team_color(entity));
		}
	}
	
	void class_name(c_base_entity* entity) {
		vector_2d origin_screen;
		if (draw::w2s(entity->get_origin(), origin_screen)) {
			draw::text(get_class_name_string(entity->get_class_name()), origin_screen, color(255, 255, 255), 17, true);
		}
	}

	void fov_circle(c_base_entity* local_player) {
		const float scale = tan(settings::aimbot_fov / 180 * M_PI) / tan((local_player->get_fov() / 2) / 180 * M_PI);
		auto radius = scale * utils::screen_x / 2;
		draw::circle(vector_2d(utils::screen_x / 2, utils::screen_y / 2), radius, color(255, 0, 0));
	}

	void object_esp(c_base_entity* entity) {
		auto class_id = entity->get_client_class()->class_id;

		if (entity->is_health_pack()) {
			int x, y, w, h;
			if (get_item_bounds(entity, x, y, w, h)) {
				draw::box(x, y, w, h, color(144, 238, 144));
				draw::text("Health", vector_2d(x + (w / 2), y - draw::get_text_size_height("Health", 15) * .75), color(255, 0, 0), 15, true);
			}
		}
		else if (entity->is_ammo_pack()) {
			int x, y, w, h;
			if (get_item_bounds(entity, x, y, w, h)) {
				draw::box(x, y, w, h, color(144, 238, 144));
				draw::text("Ammo", vector_2d(x + (w / 2), y - draw::get_text_size_height("Ammo", 15) * .75), color(255, 0, 0), 15, true);
			}
		}
		else if (class_id == class_ids::CObjectTeleporter) {
			int x, y, w, h;
			if (get_item_bounds(entity, x, y, w, h)) {
				draw::box(x, y, w, h, color(144, 238, 144));
				draw::text("Teleporter", vector_2d(x + (w / 2), y - draw::get_text_size_height("Teleporter", 15) * .75), color(255, 0, 0), 15, true);
			}
		}
		else if (class_id == class_ids::CObjectSentrygun) {
			int x, y, w, h;
			if (get_item_bounds(entity, x, y, w, h)) {
				draw::box(x, y, w, h, color(144, 238, 144));
				draw::text("Sentry", vector_2d(x + (w / 2), y - draw::get_text_size_height("Sentry", 15) * .75), color(255, 0, 0), 15, true);
			}
		}
		else if (class_id == class_ids::CObjectDispenser) {
			int x, y, w, h;
			if (get_item_bounds(entity, x, y, w, h)) {
				draw::box(x, y, w, h, color(144, 238, 144));
				draw::text("Dispenser", vector_2d(x + (w / 2), y - draw::get_text_size_height("Dispenser", 15) * .75), color(255, 0, 0), 15, true);
			}
		}
	}

	bool get_item_bounds(c_base_entity* entity, int& x, int& y, int& w, int& h)
	{
		if (!entity) {
			return false;
		}

		const matrix3x4& transform = entity->get_rgfl_coordinate_frame();

		vector mins = {};
		vector maxs = {};

		if (entity->is_player()) {
			mins = interfaces::game_movement->get_player_mins(entity->is_ducking());
			maxs = interfaces::game_movement->get_player_maxs(entity->is_ducking());
		}
		else {
			mins = entity->get_collideable_mins();
			maxs = entity->get_collideable_max();
		}

		vector points[] = {
			vector(mins.x, mins.y, mins.z),
			vector(mins.x, maxs.y, mins.z),
			vector(maxs.x, maxs.y, mins.z),
			vector(maxs.x, mins.y, mins.z),
			vector(maxs.x, maxs.y, maxs.z),
			vector(mins.x, maxs.y, maxs.z),
			vector(mins.x, mins.y, maxs.z),
			vector(maxs.x, mins.y, maxs.z)
		};

		vector transformed_points[8];

		for (int i = 0; i < 8; i++)
			math::vector_transform(points[i], transform, transformed_points[i]);

		vector_2d flb, brt, blb, frt, frb, brb, blt, flt;

		if (draw::w2s(transformed_points[3], flb) && draw::w2s(transformed_points[5], brt)
			&& draw::w2s(transformed_points[0], blb) && draw::w2s(transformed_points[4], frt)
			&& draw::w2s(transformed_points[2], frb) && draw::w2s(transformed_points[1], brb)
			&& draw::w2s(transformed_points[6], blt) && draw::w2s(transformed_points[7], flt)
			&& draw::w2s(transformed_points[6], blt) && draw::w2s(transformed_points[7], flt))
		{
			vector_2d arr[] = { flb, brt, blb, frt, frb, brb, blt, flt };

			float left = flb.x;
			float top = flb.y;
			float righ = flb.x;
			float bottom = flb.y;

			for (int n = 1; n < 8; n++) {
				if (left > arr[n].x)
					left = arr[n].x;

				if (top < arr[n].y)
					top = arr[n].y;

				if (righ < arr[n].x)
					righ = arr[n].x;

				if (bottom > arr[n].y)
					bottom = arr[n].y;
			}

			float x_ = left;
			float y_ = bottom;
			float w_ = (righ - left);
			float h_ = (top - bottom);

			if (entity->is_player()) {
				x_ += ((righ - left) / 8.0f);
				w_ -= (((righ - left) / 8.0f) * 2.0f);
			}

			x = static_cast<int>(x_);
			y = static_cast<int>(y_);
			w = static_cast<int>(w_);
			h = static_cast<int>(h_);

			if (x > utils::screen_x || (x + w) < 0 || y > utils::screen_y || (y + h) < 0)
				return false;

			return true;
		}

		return false;
	}
}