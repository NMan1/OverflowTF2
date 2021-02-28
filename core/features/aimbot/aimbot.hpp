#pragma once

class c_base_entity;
class c_user_cmd;
class vector;

namespace aimbot {
	void run(c_base_entity* local_player, c_user_cmd* cmd);

	c_base_entity* get_closest_to_crosshair(c_base_entity* local_player, const vector view_angles, int settings_fov);
}