#pragma once

class c_base_entity;
class c_user_cmd;

namespace visualize_walkbot {

	void move(c_base_entity* local_player, c_user_cmd* cmd);

	void visualize_path();

}