#pragma once
#include <d3d9.h>
#include "../../utils/color.hpp"
#include "../../utils/utils.hpp"

#define FLOW_OUTGOING	0
#define FLOW_INCOMING	1
#define MAX_FLOWS		2		// in & out
typedef float matrix3x4[3][4];

typedef struct InputContextHandle_t__ *InputContextHandle_t;
struct client_textmessage_t;
struct model_t;
class SurfInfo;
class i_material;
class CSentence;
class CAudioSource;
class AudioState_t;
class ISpatialQuery;
class IMaterialSystem;
class CPhysCollide;
class IAchievementMgr;
class KeyValues;

class i_net_channel_info
{
public:
	enum {
		GENERIC = 0,	// must be first and is default group
		LOCALPLAYER,	// bytes for local player entity update
		OTHERPLAYERS,	// bytes for other players update
		ENTITIES,		// all other entity bytes
		SOUNDS,			// game sounds
		EVENTS,			// event messages
		USERMESSAGES,	// user messages
		ENTMESSAGES,	// entity messages
		VOICE,			// voice data
		STRINGTABLE,	// a stringtable update
		MOVE,			// client move cmds
		STRINGCMD,		// string command
		SIGNON,			// various signondata
		TOTAL,			// must be last and is not a real group
	};

	virtual const char* get_name(void) const = 0;	// get channel name
	virtual const char* get_address(void) const = 0; // get channel IP address as string
	virtual float		get_time(void) const = 0;	// current net time
	virtual float		get_time_connected(void) const = 0;	// get connection time in seconds
	virtual int			get_buffer_size(void) const = 0;	// netchannel packet history size
	virtual int			get_data_rate(void) const = 0; // send data rate in byte/sec

	virtual bool		is_loopback(void) const = 0;	// true if loopback channel
	virtual bool		is_timing_out(void) const = 0;	// true if timing out
	virtual bool		is_playback(void) const = 0;	// true if demo playback

	virtual float		get_latency(int flow) const = 0;	 // current latency (RTT), more accurate but jittering
	virtual float		get_avg_latency(int flow) const = 0; // average packet latency in seconds
	virtual float		get_avg_loss(int flow) const = 0;	 // avg packet loss[0..1]
	virtual float		get_avg_choke(int flow) const = 0;	 // avg packet choke[0..1]
	virtual float		get_avg_data(int flow) const = 0;	 // data flow in bytes/sec
	virtual float		get_avg_packets(int flow) const = 0; // avg packets/sec
	virtual int			get_total_data(int flow) const = 0;	 // total flow in/out in bytes
	virtual int			get_sequence_nr(int flow) const = 0;	// last send seq number
	virtual bool		is_valid_packet(int flow, int frame_number) const = 0; // true if packet was not lost/dropped/chocked/flushed
	virtual float		get_packet_time(int flow, int frame_number) const = 0; // time when packet was send
	virtual int			get_packet_bytes(int flow, int frame_number, int group) const = 0; // group size of this packet
	virtual bool		get_stream_progress(int flow, int* received, int* total) const = 0;  // TCP progress if transmitting
	virtual float		get_time_since_last_received(void) const = 0;	// get time since last recieved packet in seconds
	virtual	float		get_command_interpolation_amount(int flow, int frame_number) const = 0;
	virtual void		get_packet_response_latency(int flow, int frame_number, int* pnLatencyMsecs, int* pnChoke) const = 0;
	virtual void		get_remote_framerate(float* pflFrameTime, float* pflFrameTimeStdDeviation) const = 0;

	virtual float		get_timeout_seconds() const = 0;
};

class ISPSharedMemory;
class CGamestatsData;
class CSteamAPIContext;
struct Frustum_t;

class iv_engine_client
{
public:
	int get_player_for_user_i_d(int UserID)
	{
		using fn = int(__thiscall*)(void*, int);
		return utils::get_vfunc<fn>(this, 9)(this, UserID);
	}

	void server_cmd(const char* chCommandString, bool bReliable = true)
	{
		typedef void(__thiscall* fn)(void*, const char*, bool);
		return utils::get_vfunc<fn>(this, 6)(this, chCommandString, bReliable);
	}

	void get_screen_size(int& width, int& height)
	{
		typedef void(__thiscall* fn)(void*, int&, int&);
		return utils::get_vfunc<fn>(this, 5)(this, width, height);
	}

	bool con_is_visible(void)
	{
		typedef bool(__thiscall* fn)(void*);
		return utils::get_vfunc<fn>(this, 11)(this);
	}

	int get_local_player(void)
	{
		typedef int(__thiscall* fn)(void*);
		return utils::get_vfunc<fn>(this, 12)(this);
	}

	float time(void)
	{
		typedef float(__thiscall* fn)(void*);
		return utils::get_vfunc<fn>(this, 14)(this);
	}

	void get_view_angles(vector& va)
	{
		typedef void(__thiscall* fn)(void*, vector& va);
		return utils::get_vfunc<fn>(this, 19)(this, va);
	}

	void set_view_angles(vector& va)
	{
		typedef void(__thiscall* fn)(void*, vector& va);
		return utils::get_vfunc<fn>(this, 20)(this, va);
	}

	int get_max_clients(void)
	{
		typedef int(__thiscall* fn)(void*);
		return utils::get_vfunc<fn>(this, 21)(this);
	}

	bool is_in_game(void)
	{
		typedef bool(__thiscall* fn)(void*);
		return utils::get_vfunc<fn>(this, 26)(this);
	}

	bool is_connected(void)
	{
		typedef bool(__thiscall* fn)(void*);
		return utils::get_vfunc<fn>(this, 27)(this);
	}

	bool is_drawing_loading_image(void)
	{
		typedef bool(__thiscall* fn)(void*);
		return utils::get_vfunc<fn>(this, 28)(this);
	}

	const matrix3x4& world_to_screen_matrix(void)
	{
		typedef const matrix3x4& (__thiscall* fn)(void*);
		return utils::get_vfunc<fn>(this, 36)(this);
	}

	bool is_taking_screenshot(void)
	{
		typedef bool(__thiscall* fn)(void*);
		return utils::get_vfunc<fn>(this, 85)(this);
	}

	void client_cmd(const char* szCommandString)
	{
		typedef void(__thiscall* ClientCmdFn)(void*, const char*);
		return utils::get_vfunc<ClientCmdFn>(this, 7)(this, szCommandString);
	}

	int GetAppId()
	{
		typedef int(__thiscall* fn)(void*);
		return utils::get_vfunc<fn>(this, 104)(this);
	}

	void client_cmd__unrestricted(const char* chCommandString)
	{
		typedef void(__thiscall* fn)(void*, const char*);
		return utils::get_vfunc<fn>(this, 106)(this, chCommandString);
	}

	void server_cmd_key_values(void* kv)
	{
		typedef void(__thiscall* fn)(void*, void*);
		utils::get_vfunc<fn>(this, 127)(this, kv);
	}
};