#pragma once
#include "i_entity.hpp"
#include "..\utils\utils.hpp"
#include "../utils/game/structs.hpp"
#include "../utils/netvars/dt_recv.hpp"

class c_client_class
{
public:
	unsigned char _chPadding[8];
	char* szName;
	RecvTable* rtTable;
	c_client_class* pNextClass;
	int iClassID;
};

class i_base_client_dll
{
public:
	c_client_class * get_all_classes()
	{
		typedef c_client_class* (__thiscall* fn)(void*);
		return utils::get_vfunc<fn>(this, 8)(this);
	}
};

class i_global_vars
{
public:
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

class i_client_mode_shared
{
public:
		virtual             ~i_client_mode_shared() {}
		virtual void        init() = 0;
		virtual void        init_viewport() = 0;
		virtual void        shutdown() = 0;
		virtual void		level_init(const char* newmap);
		virtual void		level_shutdown(void);
		virtual void        enable() = 0;
		virtual void        disable() = 0;
		virtual void        layout() = 0;
		virtual void		reload_scheme(bool flushLowLevel) = 0;
		virtual void		override_view(unsigned long* pSetup) = 0;
		virtual bool		should_draw_detail_objects() = 0;
		virtual bool		should_draw_entity(c_base_entity* pEnt) = 0;
		virtual bool		should_draw_local_player(c_base_entity* pPlayer) = 0;
		virtual bool		should_draw_view_model() = 0;
		virtual bool		should_draw_particles() = 0;
		virtual bool		should_draw_crosshair(void) = 0;
		virtual bool		should_blackout_around_hud() = 0;
		virtual unsigned long should_override_headtrack_control() = 0;
		virtual void		adjust_engine_viewport(int& x, int& y, int& width, int& height) = 0;
		virtual void		pre_render(unsigned long* pSetup) = 0;
		virtual void		post_render() = 0;
		virtual void		post_render_vgui() = 0;
		virtual void		process_input(bool bActive) = 0;
		virtual bool		create_move(float flInputSampleTime, c_user_cmd* cmd) = 0;
		virtual void		update() = 0;
};