#include "settings.hpp"
#include "..\color.hpp"

namespace settings {

	bool visuals = true;

	bool team_visuals = false;

	bool box = true;

	color box_color = {255, 255, 255};

	bool health_bar = true;

	bool glow_players = false;

	bool skeleton = true;

	color skeleton_color = { 238, 130, 238 };

	bool snap_lines = false;

	color snap_lines_color = { 255, 255, 255 };

	bool direction_line = true;

	color direction_line_color = { 255, 255, 255 };

	bool health_text = true;

	bool class_name = true;

	color class_name_color = { 255, 255, 255 };

	bool buildings = true;

	color buildings_color = { 255, 0, 0 };

	bool glow_buildings = true;

	bool team_buildings = true;

	color team_buildings_color = { 0, 244, 0 };

	bool health_bar_buildings = true;
	
	bool pickups = false;

	bool health_pack_esp = true;

	color health_pack_esp_color = { 255, 255, 255 };

	bool ammo_box_esp = true;

	color ammo_box_esp_color = { 255, 255, 255 };

	bool chams = true;

	bool enemy_chams = false;

	color enemy_chams_color = { 255, 255, 255 };

	bool gold_arm = true;

	bool projectile_esp = false;

	color projectile_esp_color = { 111, 242, 253 };

	bool rocket_esp = false;

	bool arrow_esp = false;

	bool flare_esp = false;

	bool pipe_bomb_esp = false;

	bool visualize_backtrack = false;

	color visualize_backtrack_color = { 238, 130, 238 };

	// aimbot

	bool aimbot = true;

	int aimbot_key = 0x10; // VK_SHIFT

	int aimbot_bone = 1;

	int aimbot_fov = 5;

	float aimbot_smoothness = 0.0f;

	bool aimbot_proj = true;

	int aimbot_proj_fov = 30;

	float aimbot_proj_smoothness = 0;

	int aimbot_proj_launcher_bone = 0;

	bool triggerbot = false;

	int triggerbot_key = 0;

	int triggerbot_bone = 0;

	bool triggerbot_always_on = false;

	bool triggerbot_scoped_only = true;

	bool triggerbot_ignore_cloaked = true;
	
	bool legit_backtrack = true;

	// misc

	bool misc = true;

	bool bunny_hop = true;

	bool auto_backstab = false;

	// others

	bool spectator_list = true;
}