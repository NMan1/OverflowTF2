#pragma once
#include "..\..\utils\utils.hpp"
#include "i_entity.hpp"
#include "c_base_combat_weapon.hpp"

struct weapon_data;
class c_game_trace;
class vector;
class c_base_entity;

class c_base_combat_weapon : public c_base_entity
{
private:
	template<class t>
	t get_value(const int offset);

public:
	
	int get_weapon_id();

	weapon_data get_weapon_data();

	int get_clip_1();

	int get_clip_2();

	int get_slot();

	float get_charge_time();

	float get_charge_damage();

	short get_item_definition_index();

	float get_last_fire_time();

	float get_swing_range(c_base_entity* pLocal);

	bool do_swing_trace(c_game_trace& Trace);

	bool will_crit();

	vector& get_bullet_spread();

	int get_damage_type();

	bool can_fire_critical_shot(bool bHeadShot);

	float get_next_secondary_attack();

	float get_next_primary_attack();
};