#include "c_base_combat_weapon.hpp"
#include "..\..\utils\memory\memory.hpp"
#include "../structs/structs.hpp"
#include "..\..\utils\netvars\netvars.hpp"
#include "../../interfaces/interfaces.hpp"

template<class t>
t c_base_combat_weapon::get_value(const int offset) {
	return *reinterpret_cast<t*>(reinterpret_cast<uintptr_t>(this) + offset);
}

int c_base_combat_weapon::get_weapon_id()
{
	typedef int(__thiscall* fn)(void*);
	return utils::get_vfunc<fn>(this, 377)(this);
}

weapon_data c_base_combat_weapon::get_weapon_data() {
	using Data = weapon_info * (__cdecl*)(int);
	static int offset = memory::find_pattern("client.dll", "55 8B EC 66 8B ? ? 66 3B 05 ? ? ? ? 73");
	static auto get_tf_weapon_data_fn = reinterpret_cast<Data>(offset);
	return get_tf_weapon_data_fn(get_weapon_id())->m_WeaponData[0];
}

int c_base_combat_weapon::get_clip_1()
{
	static int team_num = g_netvar->get_offset("DT_BaseCombatWeapon", "LocalWeaponData", "m_iClip1");
	return get_value<int>(team_num);
}

int c_base_combat_weapon::get_clip_2()
{
	static int team_num = g_netvar->get_offset("DT_BaseCombatWeapon", "LocalWeaponData", "m_iClip2");
	return get_value<int>(team_num);
}

int c_base_combat_weapon::get_slot()
{
	typedef int(__thiscall* fn)(PVOID);
	return utils::get_vfunc<fn>(this, 327)(this);
}

float c_base_combat_weapon::get_charge_time()
{
	static int team_num = g_netvar->get_offset("DT_WeaponPipebombLauncher", "PipebombLauncherLocalData", "m_flChargeBeginTime");
	return get_value<float>(team_num);
}

float c_base_combat_weapon::get_charge_damage()
{
	static int team_num = g_netvar->get_offset("DT_TFSniperRifle", "SniperRifleLocalData", "m_flChargedDamage");
	return get_value<float>(team_num);
}

int c_base_combat_weapon::get_item_definition_index()
{
	static int team_num = g_netvar->get_offset("DT_EconEntity", "m_AttributeManager", "m_Item", "m_iItemDefinitionIndex");
	return get_value<int>(team_num);
}

float c_base_combat_weapon::get_last_fire_time()
{
	static int team_num = g_netvar->get_offset("DT_TFWeaponBase", "LocalActiveTFWeaponData", "m_flLastFireTime");
	return get_value<float>(team_num);
}

float c_base_combat_weapon::get_swing_range(c_base_entity* pLocal)
{
	typedef int(__thiscall* fn)(c_base_entity*);
	return (static_cast<float>(utils::get_vfunc<fn>(this, 451)(pLocal)));
}

bool c_base_combat_weapon::do_swing_trace(c_game_trace& Trace)
{
	typedef int(__thiscall* fn)(c_game_trace&);
	return utils::get_vfunc<fn>(this, 453)(Trace);
}

bool c_base_combat_weapon::will_crit()
{
	typedef bool(__thiscall* FN)(c_base_combat_weapon*);
	static DWORD dwFN = memory::find_pattern("client.dll", "55 8B EC 83 EC 18 56 57 6A 00 68 ? ? ? ? 68 ? ? ? ? 6A 00 8B F9 E8 ? ? ? ? 50 E8 ? ? ? ? 8B F0 83 C4 14 89 75 EC");
	return ((FN)dwFN)(this);
}

vector& c_base_combat_weapon::get_bullet_spread()
{
	typedef vector& (__thiscall* fn)(PVOID);
	return utils::get_vfunc<fn>(this, 286)(this);
}

int c_base_combat_weapon::get_damage_type()
{
	typedef int(__thiscall* fn)(void*);
	return utils::get_vfunc<fn>(this, 378)(this);
}

bool c_base_combat_weapon::can_fire_critical_shot(bool bHeadShot)
{
	typedef bool(__thiscall* fn)(void*, bool, c_base_entity*);
	return utils::get_vfunc<fn>(this, 421)(this, bHeadShot, nullptr);
}

float c_base_combat_weapon::get_next_secondary_attack()
{
	static int team_num = g_netvar->get_offset("DT_BaseCombatWeapon", "LocalActiveWeaponData", "m_flNextSecondaryAttack");
	return get_value<float>(team_num);
}

float c_base_combat_weapon::get_next_primary_attack()
{
	static int team_num = g_netvar->get_offset("DT_BaseCombatWeapon", "LocalActiveWeaponData", "m_flNextPrimaryAttack");
	return get_value<float>(team_num);
}
