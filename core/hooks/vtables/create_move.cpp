#include "..\hook.hpp"
#include "..\..\utils\settings\settings.hpp"
#include "..\..\interfaces\interfaces.hpp"
#include "..\..\source-sdk\interfaces\c_base_combat_weapon.hpp"

#include "../../features/misc/misc.hpp"
#include "../../features/aimbot/aimbot.hpp"
#include "../../features/triggerbot/triggerbot.hpp"
#include "../../features/visuals/walkbot/visualize_walkbot.hpp"
#include "../../menu/menu.hpp"
#include "../../features/backtrack/backtrack.hpp"

bool __stdcall hooks::client_mode::create_move::fn(float input_sample_time, c_user_cmd* cmd)
{
	static const auto original_return_value = m_client_mode->get_original<t>(index)(input_sample_time, cmd);

	if (!cmd || !cmd->command_number) {
		return original_return_value;
	}

	auto local_player = interfaces::entity_list->get_client_entity(interfaces::engine->get_local_player());
	if (local_player && local_player->is_alive() && settings::misc) {
		if (settings::bunny_hop) {
			misc::bunny_hop(local_player, cmd);
		}

		if (settings::auto_backstab) {
			misc::auto_backstab(local_player, cmd);
		}

		if (settings::legit_backtrack) {
			backtrack::save_ticks(local_player, cmd);
			backtrack::set_backtrack_tick(local_player, cmd);
		}

		if (!menu::open && settings::aimbot && GetAsyncKeyState(settings::aimbot_key) & 0x8000) {
			aimbot::run(local_player, cmd);
		}

		if (settings::triggerbot && (GetAsyncKeyState(settings::triggerbot_key) & 0x8000 || settings::triggerbot_always_on)) {
			triggerbot::run(local_player, cmd);
		}

		//visualize_walkbot::move();
	}

	return original_return_value;
}