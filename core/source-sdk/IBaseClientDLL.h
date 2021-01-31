#pragma once
#include "IEntity.h"
#include "..\utils\utils.hpp"
#include "../utils/game/misc.hpp"

class ClientClass
{
public:
	unsigned char _chPadding[8];
	char* szName;
	RecvTable* rtTable;
	ClientClass* pNextClass;
	int iClassID;
};

class IBaseClientDLL
{
public:
	ClientClass * get_all_classes()
	{
		typedef ClientClass* (__thiscall* GetAllClassesFn)(void*);
		return utils::get_vfunc<GetAllClassesFn>(this, 8)(this);
	}
};

class IGlobalVars
{
	// Absolute time (per frame still - Use Plat_FloatTime() for a high precision real time 
	//  perf clock, but not that it doesn't obey host_timescale/host_framerate)
	float			realtime;
	// Absolute frame counter
	int				framecount;
	// Non-paused frametime
	float			absoluteframetime;

	// Current time 
	//
	// On the client, this (along with tickcount) takes a different meaning based on what
	// piece of code you're in:
	// 
	//   - While receiving network packets (like in PreDataUpdate/PostDataUpdate and proxies),
	//     this is set to the SERVER TICKCOUNT for that packet. There is no interval between
	//     the server ticks.
	//     [server_current_Tick * tick_interval]
	//
	//   - While rendering, this is the exact client clock 
	//     [client_current_tick * tick_interval + interpolation_amount]
	//
	//   - During prediction, this is based on the client's current tick:
	//     [client_current_tick * tick_interval]
	float			curtime;

	// Time spent on last server or client frame (has nothing to do with think intervals)
	float			frametime;
	// current maxplayers setting
	int				maxClients;

	// Simulation ticks
	int				tickcount;

	// Simulation tick interval
	float			interval_per_tick;

	// interpolation amount ( client-only ) based on fraction of next tick which has elapsed
	float			interpolation_amount;
	int				simTicksThisFrame;

	int				network_protocol;

	// current saverestore data
	unsigned long* pSaveData;

private:
	// Set to true in client code.
	bool			m_bClient;

	// 100 (i.e., tickcount is rounded down to this base and then the "delta" from this base is networked
	int				nTimestampNetworkingBase;
	// 32 (entindex() % nTimestampRandomizeWindow ) is subtracted from gpGlobals->tickcount to set the networking basis, prevents
	//  all of the entities from forcing a new PackedEntity on the same tick (i.e., prevents them from getting lockstepped on this)
	int				nTimestampRandomizeWindow;
};

class IClientModeShared
{
public:
		virtual             ~IClientModeShared() {}
		virtual void        Init() = 0;
		virtual void        InitViewport() = 0;
		virtual void        Shutdown() = 0;
		virtual void	LevelInit(const char* newmap);
		virtual void	LevelShutdown(void);
		virtual void        Enable() = 0;
		virtual void        Disable() = 0;
		virtual void        Layout() = 0;
		virtual void	ReloadScheme(bool flushLowLevel) = 0;
		virtual void	OverrideView(unsigned long* pSetup) = 0;
		virtual bool	ShouldDrawDetailObjects() = 0;
		virtual bool	ShouldDrawEntity(C_BaseEntity* pEnt) = 0;
		virtual bool	ShouldDrawLocalPlayer(C_BaseEntity* pPlayer) = 0;
		virtual bool	ShouldDrawViewModel() = 0;
		virtual bool	ShouldDrawParticles() = 0;
		virtual bool	ShouldDrawCrosshair(void) = 0;
		virtual bool	ShouldBlackoutAroundHUD() = 0;
		virtual unsigned long ShouldOverrideHeadtrackControl() = 0;
		virtual void	AdjustEngineViewport(int& x, int& y, int& width, int& height) = 0;
		virtual void	PreRender(unsigned long* pSetup) = 0;
		virtual void	PostRender() = 0;
		virtual void	PostRenderVGui() = 0;
		virtual void	ProcessInput(bool bActive) = 0;
		virtual bool	CreateMove(float flInputSampleTime, CUserCmd* cmd) = 0;
		virtual void	Update() = 0;
};