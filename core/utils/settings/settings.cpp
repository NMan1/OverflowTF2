#include "settings.h"
#include "..\color.hpp"

namespace settings {

	bool esp = true;

	bool box = true;

	color box_color = {255, 255, 255};

	bool health_bar = true;

	bool skeleton = true;

	color skeleton_color = { 238, 130, 238 };

	bool snap_lines = true;

	color snap_lines_color = { 255, 255, 255 };

	bool direction_line = true;

	color direction_line_color = { 255, 255, 255 };

	bool health_text = true;

	bool class_name = true;

	color class_name_color = { 255, 255, 255 };

	bool teleporter_esp = true;

	color teleporter_esp_color = { 255, 255, 255 };

	bool dispenser_esp = true;

	color dispenser_esp_color = { 255, 255, 255 };

	bool turret_esp = true;

	color turret_esp_color = { 255, 255, 255 };

	bool health_pack_esp = true;

	color health_pack_esp_color = { 255, 255, 255 };

	bool ammo_box_esp = true;

	color ammo_box_esp_color = { 255, 255, 255 };

	// aimbot

	bool aimbot = true;

	int aimbot_fov = 20;

	int aimbot_smoothness = 1;

	// misc

	bool bunny_hop = true;

	bool auto_backstab = true;
}