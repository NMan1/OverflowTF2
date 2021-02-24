#include "visualize_walkbot.hpp"
#include "..\..\..\utils\draw\draw.hpp"
#include "..\..\..\utils\game\helpers.hpp"
#include "..\..\..\utils\math\math.hpp"
#include "..\..\..\utils\settings\settings.hpp"
#include "..\..\..\utils\math\math.hpp"

namespace visualize_walkbot {

	void move(c_base_entity* local_player, c_user_cmd* cmd) {
		if (GetAsyncKeyState(VK_UP) & 0x8000) {
			cmd->forwardmove = 450;
		}

		static vector start = local_player->get_origin();
		vector current = local_player->get_origin();
		std::cout << current.dist_to(start) << std::endl;
	}

	void visualize_path() {
		auto local_player = interfaces::entity_list->get_client_entity(interfaces::engine->get_local_player());
		if (!local_player) {
			return;
		}

		vector view_angles = {}, forward = {};
		interfaces::engine->get_view_angles(view_angles);
		math::angle_vectors(view_angles, &forward);

		vector start = local_player->get_origin();
		static vector end = forward * 1000 + start;

		vector screen_start, screen_end;
		if (draw::w2s(start, screen_start) && draw::w2s(end, screen_end)) {
			draw::line(screen_start, screen_end, color(255, 0, 0));
		}
	}
}