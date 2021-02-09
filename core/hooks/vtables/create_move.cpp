#include "..\hook.hpp"
#include "..\..\interfaces\interfaces.hpp"
#include "../../features/misc/misc.h"
#include "../../features/aimbot/aimbot.h"
#include "../../utils/settings/settings.hpp"

bool __stdcall hooks::client_mode::create_move::fn(float input_sample_time, c_user_cmd* cmd)
{
	static const auto original_return_value = m_client_mode->get_original<t>(index)(input_sample_time, cmd);

	if (!cmd || !cmd->command_number) {
		return original_return_value;
	}

	// yes create_move is called only when your in game, HOWEVER i am parnoid so it wont hurt
	if (interfaces::engine->is_in_game() && interfaces::engine->is_connected() &&
		!interfaces::engine->con_is_visible() && !interfaces::engine_vgui->is_game_ui_visible()) {

		auto local_player = interfaces::entity_list->get_client_entity(interfaces::engine->get_local_player());

		if (local_player && settings::misc) {
			if (settings::bunny_hop) {
				misc::bunny_hop(local_player, cmd);
			}

			if (settings::auto_backstab) {
				misc::auto_backstab(local_player, cmd);
			}

			if (GetAsyncKeyState(VK_SHIFT) & 0x8000) {
				if (settings::aimbot) {
					aimbot::run(cmd);
				}
			}
		}

	}

	return original_return_value;
}