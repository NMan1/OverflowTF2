#include "triggerbot.hpp"
#include "..\..\utils\math\math.hpp"
#include "..\..\utils\settings\settings.hpp"
#include "..\..\interfaces\interfaces.hpp"

namespace triggerbot {
	void run(c_base_entity* local_player, c_user_cmd* cmd) {
		if (settings::trigger_bot_scoped_only && !local_player->is_scoped()) {
			return;
		}

		trace_t trace;
		ray_t ray;

		c_trace_filter filter;
		filter.skip = local_player;

		vector view_angles = {}, forward = {};
		interfaces::engine->get_view_angles(view_angles);
		math::angle_vectors(view_angles, &forward);

		vector start = local_player->get_eye_position();
		vector end = forward * 10000 + start;

		ray.init(start, end);

		interfaces::trace->trace_ray(ray, (MASK_SHOT | CONTENTS_GRATE), &filter, &trace);

		if (trace.entity && trace.entity->is_player()) {
			if (trace.entity->get_team_num() == local_player->get_team_num() || (trace.entity->is_cloaked() && settings::trigger_bot_ignore_cloaked)) {
				return;
			}

			if (settings::trigger_bot_bone == 0 ? true : trace.hitbox == hitboxes::HEAD) {  
				cmd->buttons |= IN_ATTACK;
			}
		}
	}
}