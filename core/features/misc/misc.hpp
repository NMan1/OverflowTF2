#pragma once

class c_base_entity;
class c_user_cmd;

namespace misc {
	void bunny_hop(c_base_entity* local_player, c_user_cmd* cmd);

	void auto_backstab(c_base_entity* local_player, c_user_cmd* cmd);
}