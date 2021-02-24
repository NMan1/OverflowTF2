#include "..\math\vector.hpp"
#include "..\color.hpp"
#include "..\..\source-sdk\interfaces\i_entity.hpp"
#include "..\..\source-sdk\interfaces\c_base_combat_weapon.hpp"
#include "..\..\source-sdk\structs\enums.hpp"
#include "../../interfaces/interfaces.hpp"

const char* get_class_name_string(int class_id) {
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

color get_team_color(c_base_entity* entity) {
	return (entity->get_team_num() == 2
		? color(255, 102, 0, 255)
		: entity->get_team_num() == 3
		? color(0, 102, 255, 255)
		: color(255, 255, 255, 255));
}

int hash_string(const char* szOrg) {
	int iHash = 5381;

	while (int iStr = *szOrg++) iHash = iHash * 33 + iStr;

	return iHash;
}

bool is_health_hash(int nHash)
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

bool is_ammo_hash(int nHash) {
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

// credits to project_ic for the values
bool get_projectile_info(c_base_entity* local_player, float& speed, float& gravity) {
	switch (local_player->get_active_weapon()->get_item_definition_index())
	{
	case Soldier_m_RocketLauncher:
	case Soldier_m_RocketLauncherR:
	case Soldier_m_TheBlackBox:
	case Soldier_m_TheCowMangler5000:
	case Soldier_m_TheOriginal:
	case Soldier_m_FestiveRocketLauncher:
	case Soldier_m_TheBeggarsBazooka:
	case Soldier_m_SilverBotkillerRocketLauncherMkI:
	case Soldier_m_GoldBotkillerRocketLauncherMkI:
	case Soldier_m_RustBotkillerRocketLauncherMkI:
	case Soldier_m_BloodBotkillerRocketLauncherMkI:
	case Soldier_m_CarbonadoBotkillerRocketLauncherMkI:
	case Soldier_m_DiamondBotkillerRocketLauncherMkI:
	case Soldier_m_SilverBotkillerRocketLauncherMkII:
	case Soldier_m_GoldBotkillerRocketLauncherMkII:
	case Soldier_m_FestiveBlackBox:
	case Soldier_m_TheAirStrike:
	case Soldier_m_WoodlandWarrior:
	case Soldier_m_SandCannon:
	case Soldier_m_AmericanPastoral:
	case Soldier_m_SmalltownBringdown:
	case Soldier_m_ShellShocker:
	case Soldier_m_AquaMarine:
	case Soldier_m_Autumn:
	case Soldier_m_BlueMew:
	case Soldier_m_BrainCandy:
	case Soldier_m_CoffinNail:
	case Soldier_m_HighRollers:
	case Soldier_m_Warhawk: {
		speed = 1100.0f;
		gravity = 0.0f;
		break;
	}
	case Soldier_m_TheDirectHit: {
		speed = 1980.0f;
		gravity = 0.0f;
		break;
	}

	case Soldier_m_TheLibertyLauncher: {
		speed = 1540.0f;
		gravity = 0.0f;
		break;
	}
	case Demoman_m_GrenadeLauncher:
	case Demoman_m_GrenadeLauncherR:
	case Demoman_m_FestiveGrenadeLauncher:
	case Demoman_m_TheIronBomber:
	case Demoman_m_Autumn:
	case Demoman_m_MacabreWeb:
	case Demoman_m_Rainbow:
	case Demoman_m_SweetDreams:
	case Demoman_m_CoffinNail:
	case Demoman_m_TopShelf:
	case Demoman_m_Warhawk:
	case Demoman_m_ButcherBird: {
		speed = 1217.0f;
		gravity = 0.4f;
		break;
	}
	case Soldier_s_TheRighteousBison:
	case Engi_m_ThePomson6000: {
		speed = 1200.0f;
		gravity = 0.0f;
		break;
	}
	case Demoman_m_TheLooseCannon: {
		speed = 1453.9f;
		gravity = 0.4f;
		break;
	}
	case Demoman_m_TheLochnLoad: {
		speed = 1513.3f;
		gravity = 0.4f;
		break;
	}
	case Engi_m_TheRescueRanger:
	case Medic_m_FestiveCrusadersCrossbow:
	case Medic_m_CrusadersCrossbow: {
		speed = 2400.0f;
		gravity = 0.2f;
		break;
	}
	case Pyro_m_DragonsFury: {
		speed = 3000.0f;
		gravity = 0.0f;
		break;
	}
	case Pyro_m_FlameThrower:
	case Pyro_m_ThePhlogistinator:
	case Pyro_m_TheBackburner:
	case Pyro_m_TheDegreaser: {
		speed = 1000.0f;
		gravity = 0.0f;
		break;
	}
	case Pyro_s_TheDetonator:
	case Pyro_s_TheFlareGun:
	case Pyro_s_FestiveFlareGun:
	case Pyro_s_TheScorchShot: {
		speed = 2000.0f;
		gravity = 0.3f;
		break;
	}
	case Pyro_s_TheManmelter: {
		speed = 3000.0f;
		gravity = 0.2f;
		break;
	}
	case Medic_m_SyringeGun:
	case Medic_m_SyringeGunR:
	case Medic_m_TheBlutsauger:
	case Medic_m_TheOverdose: {
		speed = 1000.0f;
		gravity = 0.2f;
		break;
	}

	case Sniper_m_TheHuntsman:
	case Sniper_m_FestiveHuntsman:
	case Sniper_m_TheFortifiedCompound: {
		float charge = (interfaces::globals->curtime - local_player->get_active_weapon()->get_charge_time());
		speed = ((fminf(fmaxf(charge, 0.0f), 1.0f) * 800.0f) + 1800.0f);
		gravity = ((fminf(fmaxf(charge, 0.0f), 1.0f) * -0.4f) + 0.5f);
		break;
	}
	default:
		speed = 0.0f;
		gravity = 0.0f;
		return false;
	}
	return true;
}