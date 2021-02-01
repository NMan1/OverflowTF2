#pragma once
#include "..\vector.hpp"
#include "..\color.hpp"
#include "..\..\source-sdk\i_entity.hpp"

static const char* get_class_name_string(int class_id) {
	switch (class_id) {
	case 1:
		return "Scout";
	case 2:
		return "Sniper";
	case 3:
		return "Soldier";
	case 4:
		return "Demoman";
	case 5:
		return "Medic";
	case 6:
		return "Heavy";
	case 7:
		return "Pyro";
	case 8:
		return "Spy";
	case 9:
		return "Engineer";
	default:
		return "Enemy";
	}
}

static color get_team_color(c_base_entity* entity) {
	return (entity->get_team_num() == 2
		? color(255, 102, 0, 255)
		: entity->get_team_num() == 3
		? color(0, 102, 255, 255)
		: color(255, 255, 255, 255));
}