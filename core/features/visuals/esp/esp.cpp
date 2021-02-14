#define NOMINMAX
#include "esp.hpp"
#include "..\..\..\utils\draw\draw.hpp"
#include "..\..\..\utils\helpers.hpp"
#include "..\..\..\utils\math\math.hpp"
#include "..\..\..\utils\settings\settings.hpp"
#include "..\..\..\source-sdk\interfaces\c_base_combat_weapon.hpp"

namespace esp {
	void box(c_base_entity* entity, int x, int y, int w, int h);

	void health_bar(c_base_entity* entity, int x, int y, int w, int h);

	void class_name(c_base_entity* entity, int x, int y, int w, int h);

	void snap_lines(c_base_entity* entity, int x, int y, int w, int h);

	void skeleton(c_base_entity* entity);

	void direction_line(c_base_entity* entity);

	void fov_circle(c_base_entity* local_player);

	void pickups(c_base_entity* entity);

	void buildings(c_base_entity* entity, c_base_entity* local_player);

	bool get_item_bounds(c_base_entity* entity, int& x, int& y, int& w, int& h);

	void run() {
		auto local_player = interfaces::entity_list->get_client_entity(interfaces::engine->get_local_player());

		if (!local_player) {
			return;
		}

		if (!local_player->is_in_valid_team()) {
			return;
		}

		for (int i = 1; i <= interfaces::engine->get_max_clients(); i++) {
			auto entity = interfaces::entity_list->get_client_entity(i);

			if (!entity || entity == local_player || entity->is_dormant() || !entity->is_alive() || !entity->get_health()) {
				continue;
			}

			if (!settings::team_visuals && entity->get_team_num() == local_player->get_team_num()) {
				continue;
			}

			int x, y, w, h;
			if (!get_item_bounds(entity, x, y, w, h)) {
				continue;
			}

			if (settings::box) {
				box(entity, x, y, w, h);
			}

			if (settings::health_bar) {
				health_bar(entity, x, y, w, h);
			}

			if (settings::class_name) {
				class_name(entity, x, y, w, h);
			}

			if (settings::snap_lines) {
				snap_lines(entity, x, y, w, h);
			}

			if (settings::skeleton) {
				skeleton(entity);
			}

			if (settings::direction_line) {
				direction_line(entity);
			}
		}

		for (int i = 1; i <= interfaces::entity_list->get_max_entitys(); i++) {
			auto entity = interfaces::entity_list->get_client_entity(i);
			if (!entity || entity->is_player() || !entity->is_alive() || entity->is_dormant()) {
				continue;
			}

			if (settings::buildings) {
				buildings(entity, local_player);
			}

			if (settings::pickups) {
				pickups(entity);
			}
		}
	}

	void box(c_base_entity* entity, int x, int y, int w, int h) {
		draw::rect(x, y, w, h, settings::box_color);
		draw::rect(x - 1, y - 1, w + 2, h + 2, color(0, 0, 0));
	}

	void health_bar(c_base_entity* entity, int x, int y, int w, int h) {
		float current_health = entity->get_health();
		float max_health = entity->get_max_health();
		auto health_height = current_health <= max_health ? h * (current_health / max_health) : h;

		draw::filled_rect(x - 6 - 1, y + (h - health_height), 2, health_height, current_health <= max_health ? color(0, 255, 0) : color(255, 215, 0));

		if (settings::health_text && current_health != max_health) {
			auto health_str = std::to_string((int)current_health);
			draw::text(draw::health_font, health_str, x - 6 - 1 - 2 - draw::get_text_size_width(draw::health_font, health_str), y + (h - health_height) - 2,
				current_health <= max_health ? color(255, 255, 255) : color(255, 215, 0));
		}
	}

	void class_name(c_base_entity* entity, int x, int y, int w, int h) {
		auto class_name = get_class_name_string(entity->get_class_name());
		draw::text(draw::class_name_font, class_name, x + (w / 2), y - 15, settings::class_name_color, true);
	}

	void snap_lines(c_base_entity* entity, int x, int y, int w, int h) {
		draw::line(utils::screen_x / 2, utils::screen_y, x + (w / 2), y + h, settings::snap_lines_color);
	}

	void skeleton(c_base_entity* entity) {
		auto studio_hdr = interfaces::model_info->get_studio_model(entity->get_model());
		if (studio_hdr) {
			for (int i = 0; i < studio_hdr->numbones; i++) {
				auto bone = studio_hdr->get_bone(i);
				if (bone && (bone->flags & BONE_USED_BY_HITBOX) && (bone->parent != -1)) {
					auto bone_pos = entity->get_bone_pos(i);
					auto parent_pos = entity->get_bone_pos(bone->parent);

					vector screen_bone, screen_parent;
					if (draw::w2s(bone_pos, screen_bone) && draw::w2s(parent_pos, screen_parent)) {
						draw::line(screen_parent.x, screen_parent.y, screen_bone.x, screen_bone.y, settings::skeleton_color);
					}
				}
			}
		}
	}

	void direction_line(c_base_entity* entity) {
		vector start = entity->get_hitbox_pos(hitboxes::HEAD);
		vector angles = entity->get_view_angles();
		vector forward_vector;

		math::angle_vectors(angles, &forward_vector);

		vector screen_start, screen_end;
		if (draw::w2s(start, screen_start) && draw::w2s(forward_vector * 50 + start, screen_end)) {
			draw::line(screen_start, screen_end, settings::direction_line_color);
		}
	}

	void fov_circle(c_base_entity* local_player) {
		//auto fuck_me = ((tanf((settings::aimbot_fov / 2) * M_PI / 180)) / tanf((90 / 2) * M_PI / 180) * 800 / 2);  //+10 because that fine tunes the circle to where we need it
		//draw::circle(vector_2d(utils::screen_x / 2, utils::screen_y / 2), fuck_me, color(255, 0, 0));
	}

	void pickups(c_base_entity* entity) {
		if (settings::health_pack_esp && entity->is_health_pack()) {
			int x, y, w, h;
			if (get_item_bounds(entity, x, y, w, h)) {
				draw::rect(x, y, w, h, settings::health_pack_esp_color);
				draw::text(draw::pickup_font, "Health", x + (w / 2), y, settings::health_pack_esp_color, true);
			}
		}
		else if (settings::ammo_box_esp && entity->is_ammo_pack()) {
			int x, y, w, h;
			if (get_item_bounds(entity, x, y, w, h)) {
				draw::rect(x, y, w, h, settings::ammo_box_esp_color);
				draw::text(draw::pickup_font, "Ammo", x + (w / 2), y, settings::ammo_box_esp_color, true);
			}
		}
	}

	void buildings(c_base_entity* entity, c_base_entity* local_player) {
		if (!settings::team_buildings && entity->get_team_num() == local_player->get_team_num()) {
			return;
		}

		auto class_id = entity->get_client_class()->class_id;

		if (settings::teleporter_esp && class_id == class_ids::CObjectTeleporter) {
			int x, y, w, h;
			if (get_item_bounds(entity, x, y, w, h)) {
				color clr = (settings::team_buildings && entity->get_team_num() == local_player->get_team_num()) ? color(0, 255, 0) : settings::teleporter_esp_color;
				draw::rect(x, y, w, h, clr);
				draw::text(draw::pickup_font, "Teleporter", x + (w / 2), y, settings::teleporter_esp_color, true);
			}
		}
		else if (settings::turret_esp && class_id == class_ids::CObjectSentrygun) {
			int x, y, w, h;
			if (get_item_bounds(entity, x, y, w, h)) {
				color clr = (settings::team_buildings && entity->get_team_num() == local_player->get_team_num()) ? color(0, 255, 0) : settings::turret_esp_color;
				draw::rect(x, y, w, h, clr);
				draw::text(draw::pickup_font, "Sentry", x + (w / 2), y, settings::turret_esp_color, true);

			}
		}
		else if (settings::dispenser_esp && class_id == class_ids::CObjectDispenser) {
			int x, y, w, h;
			if (get_item_bounds(entity, x, y, w, h)) {
				color clr = (settings::team_buildings && entity->get_team_num() == local_player->get_team_num()) ? color(0, 255, 0) : settings::dispenser_esp_color;
				draw::rect(x, y, w, h, clr);
				draw::text(draw::pickup_font, "Dispenser", x + (w / 2), y, settings::dispenser_esp_color, true);
			}
		}
	}

	bool get_item_bounds(c_base_entity* entity, int& x, int& y, int& w, int& h) {
		if (!interfaces::game_movement || !entity) {
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

		vector flb, brt, blb, frt, frb, brb, blt, flt;

		if (draw::w2s(transformed_points[3], flb) && draw::w2s(transformed_points[5], brt)
			&& draw::w2s(transformed_points[0], blb) && draw::w2s(transformed_points[4], frt)
			&& draw::w2s(transformed_points[2], frb) && draw::w2s(transformed_points[1], brb)
			&& draw::w2s(transformed_points[6], blt) && draw::w2s(transformed_points[7], flt)
			&& draw::w2s(transformed_points[6], blt) && draw::w2s(transformed_points[7], flt))
		{
			vector arr[] = { flb, brt, blb, frt, frb, brb, blt, flt };

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