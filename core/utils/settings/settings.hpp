#pragma once

class color;

namespace settings {

	// visuals

	extern bool visuals;

	extern bool team_visuals;

	extern bool box;

	extern color box_color;

	extern bool health_bar;

	extern bool glow_players;

	extern bool skeleton;

	extern color skeleton_color;

	extern bool snap_lines;

	extern color snap_lines_color;

	extern bool direction_line;

	extern color direction_line_color;

	extern bool health_text;

	extern bool class_name;

	extern color class_name_color;

	extern bool buildings;

	extern bool glow_buildings;

	extern bool team_buildings;

	extern bool teleporter_esp;

	extern color teleporter_esp_color;

	extern bool dispenser_esp;

	extern color dispenser_esp_color;

	extern bool turret_esp;

	extern color turret_esp_color;

	extern bool pickups;

	extern bool health_pack_esp;

	extern color health_pack_esp_color;

	extern bool ammo_box_esp;

	extern color ammo_box_esp_color;

	extern bool chams;

	extern bool enemy_chams;

	extern color enemy_chams_color;

	extern bool gold_arm;

	// aimbot

	extern bool aimbot;

	extern int aimbot_fov;

	extern float aimbot_smoothness;

	extern bool trigger_bot;

	extern int trigger_bot_bone;

	extern bool trigger_bot_always_on;

	extern bool trigger_bot_scoped_only;

	extern bool trigger_bot_ignore_cloaked;

	// misc

	extern bool misc;

	extern bool bunny_hop;

	extern bool auto_backstab;

}