#include "..\hook.hpp"
#include "..\..\interfaces\interfaces.hpp"
#include "../../features/misc/misc.h"
#include "../../features/aimbot/aimbot.h"

bool __stdcall hooks::client_mode::create_move::fn(float input_sample_time, c_user_cmd* cmd)
{
	static const auto original_return_value = m_client_mode->get_original<t>(index)(input_sample_time, cmd);

	if (!cmd || !cmd->command_number) {
		return original_return_value;
	}

	misc::bunny_hop(cmd);

	if (GetAsyncKeyState(VK_SHIFT) & 0x8000) {
		aimbot::run(cmd);
	}

	return original_return_value;
}