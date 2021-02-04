#include "../menu.hpp"
#include "../../utils/settings/settings.h"
#include "../menu_helpers.h"

void menu::misc_tab() {
	ImVec2 padding{ 5, 10 }; //  y = 17 with child title text
	ImVec2 real_padding{ 12, 17 }; // the real padding applied

	helpers::apply_padding(padding);
	ImGui::BeginChild("Misc Main", ImVec2((menu::menu_size.x - real_padding.x * 3) * .5, (menu::menu_size.y - real_padding.y * 3) * .65), true, ImGuiCorner_TopLeft, 10, ImGuiWindowFlags_AlwaysUseWindowPadding);
	{
		helpers::toggle("bunny hop", &settings::bunny_hop, helpers::to_color({ 1, 0.321, 0.321, 1 }));
		helpers::toggle("auto backstab", &settings::auto_backstab, helpers::to_color({ 1, 0.321, 0.321, 1 }));
	}
	ImGui::EndChild(true, menu::font_child_title);
}
