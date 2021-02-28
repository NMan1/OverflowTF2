#pragma once
#include <vector>
#include "..\..\utils\math\vector.hpp"

class c_base_entity;
class c_user_cmd;

struct saved_ticks {
	saved_ticks(int tick_number, vector head_positon) {
		this->tick_number = tick_number;
		this->head_position = head_positon;
	}

	int tick_number = -1;
	vector head_position = { 0, 0, 0 };
};

namespace backtrack {
	void save_ticks(c_base_entity* local_player, c_user_cmd* cmd);

	void set_backtrack_tick(c_base_entity* local_player, c_user_cmd* cmd);

	extern std::vector<saved_ticks> player_ticks[64];
}