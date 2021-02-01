#include "misc.h"

namespace misc {
	void bunny_hop(c_user_cmd* cmd) {
		static bool released = true;
		auto local_player = interfaces::entity_list->get_client_entity(interfaces::engine->get_local_player());

		if (!local_player) {
			return;
		}

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
}