#include "../menu.hpp"
#include "../menu_helpers.h"
#include "../imgui/imgui_internal.h"
#include "../../utils/settings/settings.h"

void main_child();
void weapon_child();
void chams_child();
void misc_child();
void world_child();

ImVec2 padding{ 5, 10 }; //  y = 17 with child title text
ImVec2 real_padding{ 12, 17 }; // the real padding applied

void menu::visuals_tab()
{
	main_child();
	weapon_child();
	helpers::change_pos(ImVec2((menu::menu_size.x - real_padding.x * 3) * .5 + (real_padding.x * 2) - 4, padding.y - 2));
	chams_child();
	helpers::change_pos(ImVec2((menu::menu_size.x - real_padding.x * 3) * .5 + (real_padding.x * 2) - 4, (padding.y * 2) + ((menu::menu_size.y - real_padding.y * 3) * .4)));
	misc_child();
	helpers::change_pos(ImVec2((menu::menu_size.x - real_padding.x * 3) * .5 + (real_padding.x * 2) - 4, (padding.y * 3) + ((menu::menu_size.y - real_padding.y * 3) * .7 + 1)));
	world_child();
}

void main_child()
{
	helpers::apply_padding(padding);
	ImGui::BeginChild("ESP Main", ImVec2((menu::menu_size.x - real_padding.x * 3) * .5, (menu::menu_size.y - real_padding.y * 3) * .65), true, ImGuiCorner_TopLeft, 10, ImGuiWindowFlags_AlwaysUseWindowPadding);
	{
		helpers::toggle("esp", &settings::esp, helpers::to_color({ 1, 0.321, 0.321, 1 }));
		helpers::toggle("box", &settings::box, helpers::to_color({ 1, 0.321, 0.321, 1 }));
		helpers::toggle("health bar", &settings::health_bar, helpers::to_color({ 1, 0.321, 0.321, 1 }));
		helpers::toggle("health text", &settings::health_text, helpers::to_color({ 1, 0.321, 0.321, 1 }));
		helpers::toggle("skeleton", &settings::skeleton, helpers::to_color({ 1, 0.321, 0.321, 1 }));
		helpers::toggle("snap lines", &settings::snap_lines, helpers::to_color({ 1, 0.321, 0.321, 1 }));
		helpers::toggle("direction lines", &settings::direction_line, helpers::to_color({ 1, 0.321, 0.321, 1 }));
		helpers::toggle("direction lines", &settings::direction_line, helpers::to_color({ 1, 0.321, 0.321, 1 }));
		helpers::toggle("class name", &settings::class_name, helpers::to_color({ 1, 0.321, 0.321, 1 }));
	}
	ImGui::EndChild(true, menu::font_child_title);
}

void weapon_child()
{
	helpers::apply_padding(padding);
	helpers::change_pos(ImVec2(ImGui::GetCursorPosX() , ImGui::GetCursorPosY() - 6));
	ImGui::BeginChild("Weapons", ImVec2((menu::menu_size.x - real_padding.x * 3) * .5, (menu::menu_size.y - real_padding.y * 3) * .35 + 9), true, 0, -1, ImGuiWindowFlags_AlwaysUseWindowPadding);
	{
	}
	ImGui::EndChild(true, menu::font_child_title);
}

void chams_child()
{
	helpers::apply_padding(padding);
	ImGui::BeginChild("Chams", ImVec2((menu::menu_size.x - real_padding.x * 3) * .5, (menu::menu_size.y - real_padding.y * 3) * .4), true, ImGuiCorner_TopRight, 10, ImGuiWindowFlags_AlwaysUseWindowPadding);
	{
	}
	ImGui::EndChild(true, menu::font_child_title);
}

void misc_child()
{
	helpers::apply_padding(padding);
	ImGui::BeginChild("Misc", ImVec2((menu::menu_size.x - real_padding.x * 3) * .5, (menu::menu_size.y - real_padding.y * 3) * .3), true, 0, -1, ImGuiWindowFlags_AlwaysUseWindowPadding);
	{
	}
	ImGui::EndChild(true, menu::font_child_title);
}

void world_child()
{
	helpers::apply_padding(padding);
	ImGui::BeginChild("World", ImVec2((menu::menu_size.x - real_padding.x * 3) * .5, (menu::menu_size.y - real_padding.y * 3) * .3 - 2), true, 0, -1, ImGuiWindowFlags_AlwaysUseWindowPadding);
	{
		helpers::toggle("show teleporters", &settings::teleporter_esp, helpers::to_color({ 1, 0.321, 0.321, 1 }));
		helpers::toggle("show dispensers", &settings::dispenser_esp, helpers::to_color({ 1, 0.321, 0.321, 1 }));
		helpers::toggle("show turrets", &settings::turret_esp, helpers::to_color({ 1, 0.321, 0.321, 1 }));
		helpers::toggle("show health packs", &settings::health_pack_esp, helpers::to_color({ 1, 0.321, 0.321, 1 }));
		helpers::toggle("show ammo packs", &settings::ammo_box_esp, helpers::to_color({ 1, 0.321, 0.321, 1 }));
	}
	ImGui::EndChild(true, menu::font_child_title);
}
