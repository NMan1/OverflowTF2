#pragma once
#include "math\vector.hpp"
#include "color.hpp"
#include "..\source-sdk\interfaces\i_entity.hpp"

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

static int hash_string(const char* szOrg) {
	int iHash = 5381;

	while (int iStr = *szOrg++) iHash = iHash * 33 + iStr;

	return iHash;
}

static bool is_health_hash(int nHash)
{
	constexpr int MedKitSmall = 1941719626;
	constexpr int MedKitMedium = 642350162;
	constexpr int MedKitLarge = 1102367452;
	constexpr int MedKitSmallBday = -2020233079;
	constexpr int MedKitMediumBday = -1898223727;
	constexpr int MedKitLargeBday = -1183884197;
	constexpr int MedKitPlate = -159986486;
	constexpr int MedKitSteak = -1325824063;
	constexpr int MedKitSmallHalloween = 1667112440;
	constexpr int MedKitMediumHalloween = 170247616;
	constexpr int MedKitLargeHalloween = 827760266;
	constexpr int MedKitLargeMushRoom = 687823304;

	switch (nHash) {
	case MedKitSmall:
	case MedKitMedium:
	case MedKitLarge:
	case MedKitSmallBday:
	case MedKitMediumBday:
	case MedKitLargeBday:
	case MedKitSmallHalloween:
	case MedKitMediumHalloween:
	case MedKitLargeHalloween:
	case MedKitPlate:
	case MedKitSteak:
	case MedKitLargeMushRoom:
		return true;
	default:
		return false;
	}
}

static bool is_ammo_hash(int nHash) {
	constexpr int AmmoSmall = 913481717;
	constexpr int AmmoMedium = 1070237533;
	constexpr int AmmoLarge = 74129543;
	constexpr int AmmoLargeBday = 1933898982;
	constexpr int AmmoMediumBday = -2090593924;

	switch (nHash) {
	case AmmoSmall:
	case AmmoMedium:
	case AmmoLarge:
	case AmmoMediumBday:
	case AmmoLargeBday:
		return true;
	default:
		return false;
	}
}