#include "..\hook.hpp"
#include "..\..\interfaces\interfaces.hpp"

void bunny_hop(CUserCmd* cmd) {
	static bool released = true;
	static auto local_player = interfaces::entity_list->get_client_entity(interfaces::engine->get_local_player());

	if (!local_player) {
		return;
	}

	if (cmd->buttons & IN_JUMP) {
		if (!released) {
			if (!(local_player->get_flags() & FL_ONGROUND))
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

bool __stdcall hooks::client_mode::create_move::fn(float input_sample_time, CUserCmd* cmd)
{
	static const auto original_return_value = m_client_mode->get_original<t>(index)(input_sample_time, cmd);

	if (!cmd || !cmd->command_number) {
		return original_return_value;
	}

	bunny_hop(cmd);

	return original_return_value;
}