#pragma once
#include "..\utils\netvars\netvars.hpp"
#include "..\utils\vector.hpp"
#include "..\utils\utils.hpp"
#include "c_handle.hpp"
#include "i_client_networkable.hpp"

class c_base_combat_weapon;

class c_base_entity
{
private:
	template<class T>
	T get_value(const int offset)
	{
		return *reinterpret_cast<T*>(reinterpret_cast<std::uintptr_t>(this) + offset);
	}
public:
	bool get_life_state()
	{
		static int m_lifeState = g_netvar->get_offset("DT_BasePlayer", "m_lifeState");
		return get_value<bool>(m_lifeState);
	}

	int get_health()
	{
		static int m_iHealth = g_netvar->get_offset("DT_BasePlayer", "m_iHealth");
		return get_value<int>(m_iHealth);
	}

	int get_team_num()
	{
		static int m_iTeamNum = g_netvar->get_offset("DT_BaseEntity", "m_iTeamNum");
		return get_value<int>(m_iTeamNum);
	}

	vector get_origin()
	{
		static int m_vecOrigin = g_netvar->get_offset("DT_BaseEntity", "m_vecOrigin");
		return get_value<vector>(m_vecOrigin);
	}

	int get_class_name()
	{
		static int m_PlayerClass = g_netvar->get_offset("DT_TFPlayer", "m_PlayerClass", "m_iClass");
		return get_value<int>(m_PlayerClass);
	}

	int get_condition()
	{
		static int m_nPlayerCond = g_netvar->get_offset("DT_TFPlayer", "m_Shared", "m_nPlayerCond");
		return get_value<int>(m_nPlayerCond);
	}

	int get_flags()
	{
		static int m_fFlags = g_netvar->get_offset("DT_BasePlayer", "m_fFlags");
		return get_value<int>(m_fFlags);
	}

	bool is_dormant()
	{
		void* networkable = (void*)(this + 0x8);
		typedef bool(__thiscall* fn)(void*);
		return utils::get_vfunc< fn >(networkable, 8)(networkable);
	}
};


class c_base_combat_weapon : public c_base_entity
{
private:

public:

};

struct spatialization_info_t;
class i_client_entity
{
public:
	// Delete yourself.
	virtual void			release(void) = 0;

	// Network origin + angles
	virtual const vector& get_abs_origin(void) const = 0;
	virtual const QAngle& get_abs_angles(void) const = 0;

	virtual unsigned long* get_mouth(void) = 0;

	// Retrieve sound spatialization info for the specified sound on this entity
	// Return false to indicate sound is not audible
	virtual bool			get_sound_spatialization(spatialization_info_t& info) = 0;
};

class i_client_entityList
{
public:
	virtual i_client_networkable*	get_client_networkable(int entnum) = 0;
	virtual i_client_networkable*	get_client_networkable_from_handle(c_base_handle hEnt) = 0;
	virtual i_client_unknown*		get_client_unknown_from_handle(c_base_handle hEnt) = 0;
	virtual c_base_entity*			get_client_entity(int entnum) = 0;
	virtual i_client_entity*		get_client_entity_from_handle(c_base_handle hEnt) = 0;
	virtual int						number_of_entities(bool bIncludeNonNetworkable) = 0;
	virtual int						get_highest_entity_index(void) = 0;
	virtual void					set_max_entities(int maxents) = 0;
	virtual int						get_max_entitys() = 0;
};