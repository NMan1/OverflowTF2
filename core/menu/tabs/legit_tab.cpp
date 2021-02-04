#include "../menu.hpp"
#include "../menu_helpers.h"
#include "../../utils/settings/settings.h"

const char* legit_select[] =
{
	"Closest To Crosshair",
	"Closest Distance",
	"Lowest Health"
};

const char* legit_bone[] =
{
	"Head",
	"Neck",
	"Chest",

};

const char* trigger_bone[] =
{
	"All Bones",
	"Head",
	"Chest",
	"Stomach",
	"Chest + Stomach"
};

void menu::legit_tab() {
	ImVec2 padding{ 5, 10 }; //  y = 17 with child title text
	ImVec2 real_padding{ 12, 17 }; // the real padding applied

	helpers::apply_padding(padding);
	ImGui::BeginChild("Aimbot Main", ImVec2((menu::menu_size.x - real_padding.x * 3) * .5, (menu::menu_size.y - real_padding.y * 3) * .65), true, ImGuiCorner_TopLeft, 10, ImGuiWindowFlags_AlwaysUseWindowPadding);
	{
		helpers::toggle("aimbot", &settings::aimbot, helpers::to_color({ 1, 0.321, 0.321, 1 }));
		helpers::slider<int>("fov", &settings::aimbot_fov, 1, 100);
	}
	ImGui::EndChild(true, menu::font_child_title);
}
