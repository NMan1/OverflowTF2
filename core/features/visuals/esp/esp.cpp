#define NOMINMAX
#include "esp.hpp"
#include "..\..\..\utils\draw\draw.hpp"
#include "..\..\..\utils\helpers.hpp"
#include "..\..\..\utils\math\math.hpp"
#include "..\..\..\utils\settings\settings.hpp"
#include "..\..\..\source-sdk\interfaces\c_base_combat_weapon.hpp"

namespace esp {
	void box(c_base_entity* entity);

	void skeleton(c_base_entity* entity);

	void class_name(c_base_entity* entity);

	void direction_line(c_base_entity* entity);

	void snap_lines(c_base_entity* entity);

	void fov_circle(c_base_entity* local_player);

	void object_esp(c_base_entity* entity);

	bool get_item_bounds(c_base_entity* entity, int& x, int& y, int& w, int& h);

	void run() {
		auto local_player = interfaces::entity_list->get_client_entity(interfaces::engine->get_local_player());

		if (!local_player) {
			return;
		}

		//fov_circle(local_player);

		for (int i = 1; i <= interfaces::engine->get_max_clients(); i++) {
			auto entity = interfaces::entity_list->get_client_entity(i);

			if (!entity || entity == local_player || entity->is_dormant() || !entity->is_alive()) {
				continue;
			}

			if (entity->get_team_num() == local_player->get_team_num()) {
				continue;
			}

			box(entity);

			if (settings::skeleton) {
				skeleton(entity);
			}
			
			if (settings::snap_lines) {
				snap_lines(entity);
			}

			if (settings::direction_line) {
				direction_line(entity);
			}
			
			if (settings::class_name) {
				class_name(entity);
			}
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
		int x, y, w, h;
		if (get_item_bounds(entity, x, y, w, h)) {
			if (settings::box) {
				draw::box(x, y, w, h, settings::box_color);
				draw::box(x - 1, y - 1, w + 2, h + 2, color(0, 0, 0));
			}

			if (settings::health_bar) {
				float current_health = entity->get_health();
				float max_health = entity->get_max_health();
				auto health_height = h * (current_health / max_health);

				draw::filled_box(x - 6 - 1, y + (h - health_height), 2, health_height, color(0, 255, 0));

				if (settings::health_text && current_health != max_health) {
					draw::text(std::to_string((int)current_health), vector_2d(x - 6 - 4, y + (h - health_height) - draw::get_text_size_height(std::to_string(current_health), 12) + 2.5), color(255, 255, 255), 12, true);
				}
			}
		}
	}

	void skeleton(c_base_entity* entity) {
		auto studio_hdr = interfaces::model_info->get_studio_model(entity->get_model());
		if (studio_hdr) {
			for (int i = 0; i < studio_hdr->numbones; i++) {
				auto bone = studio_hdr->get_bone(i);
				if (bone && (bone->flags & BONE_USED_BY_HITBOX) && (bone->parent != -1)) {
					auto bone_pos = entity->get_bone_pos(i);
					auto parent_pos = entity->get_bone_pos(bone->parent);

					vector_2d screen_bone, screen_parent;
					if (draw::w2s(bone_pos, screen_bone) && draw::w2s(parent_pos, screen_parent)) {
						draw::line(screen_parent.x, screen_parent.y, screen_bone.x, screen_bone.y, settings::skeleton_color);
					}
				}
			}
		}
	}

	void snap_lines(c_base_entity* entity) {
		vector_2d origin_screen;
		if (draw::w2s(entity->get_origin(), origin_screen)) {
			draw::line(utils::screen_x / 2, utils::screen_y, origin_screen.x, origin_screen.y, settings::snap_lines_color);
		}
	}
	
	void class_name(c_base_entity* entity) {
		int x, y, w, h;
		if (get_item_bounds(entity, x, y, w, h)) {
			auto class_name = get_class_name_string(entity->get_class_name());
			draw::text(class_name, vector_2d(x + (w / 2), y - draw::get_text_size_height(class_name, 15) * .75), settings::class_name_color, 16, true);
		}
	}

	void direction_line(c_base_entity* entity) {
		vector start = entity->get_hitbox_pos(hitboxes::HEAD);
		vector angles = entity->get_view_angles();
		vector forward_vector;

		math::angle_vectors(angles, &forward_vector);

		vector_2d screen_start, screen_end;
		if (draw::w2s(start, screen_start) && draw::w2s(forward_vector * 50 + start, screen_end)) {
			draw::line(screen_start, screen_end, settings::direction_line_color);
		}
	}

	void fov_circle(c_base_entity* local_player) {
		//auto fuck_me = ((tanf((settings::aimbot_fov / 2) * M_PI / 180)) / tanf((90 / 2) * M_PI / 180) * 800 / 2);  //+10 because that fine tunes the circle to where we need it
		//draw::circle(vector_2d(utils::screen_x / 2, utils::screen_y / 2), fuck_me, color(255, 0, 0));
	}

	void object_esp(c_base_entity* entity) {
		auto class_id = entity->get_client_class()->class_id;

		if (settings::health_pack_esp && entity->is_health_pack()) {
			int x, y, w, h;
			if (get_item_bounds(entity, x, y, w, h)) {
				draw::box(x, y, w, h, settings::health_pack_esp_color);
				draw::text("Health", vector_2d(x + (w / 2), y - draw::get_text_size_height("Health", 15) * .75), settings::health_pack_esp_color, 15, true);
			}
		}
		else if (settings::ammo_box_esp && entity->is_ammo_pack()) {
			int x, y, w, h;
			if (get_item_bounds(entity, x, y, w, h)) {
				draw::box(x, y, w, h, settings::ammo_box_esp_color);
				draw::text("Ammo", vector_2d(x + (w / 2), y - draw::get_text_size_height("Ammo", 15) * .75), settings::ammo_box_esp_color, 15, true);
			}
		}
		else if (settings::teleporter_esp && class_id == class_ids::CObjectTeleporter) {
			int x, y, w, h;
			if (get_item_bounds(entity, x, y, w, h)) {
				draw::box(x, y, w, h, settings::teleporter_esp_color);
				draw::text("Teleporter", vector_2d(x + (w / 2), y - draw::get_text_size_height("Teleporter", 15) * .75), settings::teleporter_esp_color, 15, true);
			}
		}
		else if (settings::turret_esp && class_id == class_ids::CObjectSentrygun) {
			int x, y, w, h;
			if (get_item_bounds(entity, x, y, w, h)) {
				draw::box(x, y, w, h, settings::turret_esp_color);
				draw::text("Sentry", vector_2d(x + (w / 2), y - draw::get_text_size_height("Sentry", 15) * .75), settings::turret_esp_color, 15, true);
			}
		}
		else if (settings::dispenser_esp && class_id == class_ids::CObjectDispenser) {
			int x, y, w, h;
			if (get_item_bounds(entity, x, y, w, h)) {
				draw::box(x, y, w, h, settings::dispenser_esp_color);
				draw::text("Dispenser", vector_2d(x + (w / 2), y - draw::get_text_size_height("Dispenser", 15) * .75), settings::dispenser_esp_color, 15, true);
			}
		}
	}

	bool get_item_bounds(c_base_entity* entity, int& x, int& y, int& w, int& h) {
		if (!entity) {
			return false;
		}

		const matrix3x4& transform = entity->get_rgfl_coordinate_frame();

		vector mins = {};
		vector maxs = {};

		if (entity->is_player()) {
			if (interfaces::game_movement) {
				mins = interfaces::game_movement->get_player_mins(entity->is_ducking());
				maxs = interfaces::game_movement->get_player_maxs(entity->is_ducking());
			}
			else {
				return false;
			}
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