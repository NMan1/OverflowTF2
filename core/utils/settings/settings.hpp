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

	extern color buildings_color;

	extern bool glow_buildings;

	extern bool team_buildings;

	extern color team_buildings_color;

	extern bool health_bar_buildings;

	extern bool pickups;

	extern bool health_pack_esp;

	extern color health_pack_esp_color;

	extern bool ammo_box_esp;

	extern color ammo_box_esp_color;

	extern bool chams;

	extern bool enemy_chams;

	extern color enemy_chams_color;

	extern bool gold_arm;

	extern bool projectile_esp;

	extern color projectile_esp_color;

	extern bool rocket_esp;

	extern bool arrow_esp;

	extern bool flare_esp;

	extern bool pipe_bomb_esp;

	extern bool visualize_backtrack;

	extern color visualize_backtrack_color;

	// aimbot

	extern bool aimbot;

	extern int aimbot_key;

	extern int aimbot_bone;

	extern int aimbot_fov;

	extern float aimbot_smoothness;
	
	extern float aimbot_smoothness;

	extern bool aimbot_proj;

	extern int aimbot_proj_fov;

	extern float aimbot_proj_smoothness;

	extern int aimbot_proj_launcher_bone;

	extern bool triggerbot;

	extern int triggerbot_key;

	extern int triggerbot_bone;

	extern bool triggerbot_always_on;

	extern bool triggerbot_scoped_only;

	extern bool triggerbot_ignore_cloaked;

	extern bool legit_backtrack;

	// misc

	extern bool misc;

	extern bool bunny_hop;

	extern bool auto_backstab;

	// others

	extern bool spectator_list;
}