#include "misc.hpp"
#include "..\..\interfaces\interfaces.hpp"
#include "..\..\source-sdk\interfaces\c_base_combat_weapon.hpp"
#include "..\..\utils\memory\memory.hpp"

namespace misc {
	void bunny_hop(c_base_entity* local_player, c_user_cmd* cmd) {
		static bool released = true;

		if (cmd->buttons & IN_JUMP) {
			if (!released) {
				if (!(local_player->get_flags() & entity_flags::GROUND))
					cmd->buttons &= ~(1 << 1);
			}
			else {
				released = false;
			}
		}
		else if (!released) {
			released = true;
		}
	}

	void auto_backstab(c_base_entity* local_player, c_user_cmd* cmd) {
		auto weapon = local_player->get_active_weapon();

		if (weapon && weapon->get_item_definition_index() == weapon_type::Spy_t_Knife) {
			if (local_player->get_active_weapon()->can_backstab()) {
				cmd->buttons |= IN_ATTACK;
			}
		}
	}

    void change_name(const char* name) {
		auto name_var = interfaces::convar->find_var("name");
		name_var->set_value(name);

		//interfaces::engine->get_net_channel_info()->send_net_msg(msg_SetConVar);
    }
}