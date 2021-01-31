#pragma once
#include "..\utils\netvars\netvars.hpp"
#include "..\utils\vector.hpp"
#include "..\utils\utils.hpp"
#include "CHandle.h"
#include "IClientNetworkable.h"

class C_BaseCombatWeapon;

class C_BaseEntity
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
		static int m_lifeState = g_netvar->GetOffset("DT_BasePlayer", "m_lifeState");
		return get_value<bool>(m_lifeState);
	}

	int get_health()
	{
		static int m_iHealth = g_netvar->GetOffset("DT_BasePlayer", "m_iHealth");
		return get_value<int>(m_iHealth);
	}

	int get_team_num()
	{
		static int m_iTeamNum = g_netvar->GetOffset("DT_BaseEntity", "m_iTeamNum");
		return get_value<int>(m_iTeamNum);
	}

	vector get_origin()
	{
		static int m_vecOrigin = g_netvar->GetOffset("DT_BaseEntity", "m_vecOrigin");
		return get_value<vector>(m_vecOrigin);
	}

	int get_class_name()
	{
		static int m_PlayerClass = g_netvar->GetOffset("DT_TFPlayer", "m_PlayerClass", "m_iClass");
		return get_value<int>(m_PlayerClass);
	}

	int get_condition()
	{
		static int m_nPlayerCond = g_netvar->GetOffset("DT_TFPlayer", "m_Shared", "m_nPlayerCond");
		return get_value<int>(m_nPlayerCond);
	}

	int get_flags()
	{
		static int m_fFlags = g_netvar->GetOffset("DT_BasePlayer", "m_fFlags");
		return get_value<int>(m_fFlags);
	}

	bool is_dormant()
	{
		void* networkable = (void*)(this + 0x8);
		typedef bool(__thiscall* original_fn)(void*);
		return utils::get_vfunc< original_fn >(networkable, 8)(networkable);
	}
};


class C_BaseCombatWeapon : public C_BaseEntity
{
private:

public:

};

struct SpatializationInfo_t;
class IClientEntity
{
public:
	// Delete yourself.
	virtual void			Release(void) = 0;

	// Network origin + angles
	virtual const vector& GetAbsOrigin(void) const = 0;
	virtual const QAngle& GetAbsAngles(void) const = 0;

	virtual unsigned long* GetMouth(void) = 0;

	// Retrieve sound spatialization info for the specified sound on this entity
	// Return false to indicate sound is not audible
	virtual bool			GetSoundSpatialization(SpatializationInfo_t& info) = 0;
};

class IClientEntityList
{
public:
	virtual IClientNetworkable* GetClientNetworkable(int entnum) = 0;
	virtual IClientNetworkable* GetClientNetworkableFromHandle(CBaseHandle hEnt) = 0;
	virtual IClientUnknown* GetClientUnknownFromHandle(CBaseHandle hEnt) = 0;
	virtual C_BaseEntity* get_client_entity(int entnum) = 0;
	virtual IClientEntity* GetClientEntityFromHandle(CBaseHandle hEnt) = 0;
	virtual int					NumberOfEntities(bool bIncludeNonNetworkable) = 0;
	virtual int					GetHighestEntityIndex(void) = 0;
	virtual void				SetMaxEntities(int maxents) = 0;
	virtual int					get_max_entitys() = 0;
};