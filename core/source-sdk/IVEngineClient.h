#pragma once
#include <d3d9.h>
#include "../utils/vmatrix.hpp"
#include "../utils/color.hpp"

#define FLOW_OUTGOING	0
#define FLOW_INCOMING	1
#define MAX_FLOWS		2		// in & out
typedef float matrix3x4[3][4];

typedef struct InputContextHandle_t__ *InputContextHandle_t;
struct client_textmessage_t;
struct model_t;
class SurfInfo;
class IMaterial;
class CSentence;
class CAudioSource;
class AudioState_t;
class ISpatialQuery;
class IMaterialSystem;
class CPhysCollide;
class IAchievementMgr;
class KeyValues;

class INetChannelInfo
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

	virtual const char* GetName(void) const = 0;	// get channel name
	virtual const char* GetAddress(void) const = 0; // get channel IP address as string
	virtual float		GetTime(void) const = 0;	// current net time
	virtual float		GetTimeConnected(void) const = 0;	// get connection time in seconds
	virtual int			GetBufferSize(void) const = 0;	// netchannel packet history size
	virtual int			GetDataRate(void) const = 0; // send data rate in byte/sec

	virtual bool		IsLoopback(void) const = 0;	// true if loopback channel
	virtual bool		IsTimingOut(void) const = 0;	// true if timing out
	virtual bool		IsPlayback(void) const = 0;	// true if demo playback

	virtual float		GetLatency(int flow) const = 0;	 // current latency (RTT), more accurate but jittering
	virtual float		GetAvgLatency(int flow) const = 0; // average packet latency in seconds
	virtual float		GetAvgLoss(int flow) const = 0;	 // avg packet loss[0..1]
	virtual float		GetAvgChoke(int flow) const = 0;	 // avg packet choke[0..1]
	virtual float		GetAvgData(int flow) const = 0;	 // data flow in bytes/sec
	virtual float		GetAvgPackets(int flow) const = 0; // avg packets/sec
	virtual int			GetTotalData(int flow) const = 0;	 // total flow in/out in bytes
	virtual int			GetSequenceNr(int flow) const = 0;	// last send seq number
	virtual bool		IsValidPacket(int flow, int frame_number) const = 0; // true if packet was not lost/dropped/chocked/flushed
	virtual float		GetPacketTime(int flow, int frame_number) const = 0; // time when packet was send
	virtual int			GetPacketBytes(int flow, int frame_number, int group) const = 0; // group size of this packet
	virtual bool		GetStreamProgress(int flow, int* received, int* total) const = 0;  // TCP progress if transmitting
	virtual float		GetTimeSinceLastReceived(void) const = 0;	// get time since last recieved packet in seconds
	virtual	float		GetCommandInterpolationAmount(int flow, int frame_number) const = 0;
	virtual void		GetPacketResponseLatency(int flow, int frame_number, int* pnLatencyMsecs, int* pnChoke) const = 0;
	virtual void		GetRemoteFramerate(float* pflFrameTime, float* pflFrameTimeStdDeviation) const = 0;

	virtual float		GetTimeoutSeconds() const = 0;
};

class ISPSharedMemory;
class CGamestatsData;
class CSteamAPIContext;
struct Frustum_t;

//class IVEngineClient
//{
//public:
//	virtual int					GetIntersectingSurfaces(const model_t* model,const vector& vCenter,const float radius,const bool bOnlyVisibleSurfaces,	SurfInfo* pInfos,const int nMaxInfos) = 0;
//	virtual vector				GetLightForPoint(const vector& pos, bool bClamp) = 0;
//	virtual IMaterial* TraceLineMaterialAndLighting(const vector& start, const vector& end, vector& diffuseLightColor, vector& baseColor) = 0;
//	virtual const char* ParseFile(const char* data, char* token, int maxlen) = 0;
//	virtual bool				CopyLocalFile(const char* source, const char* destination) = 0;
//	virtual void				get_screen_size(int& width, int& height) = 0;
//	virtual void				ServerCmd(const char* szCmdString, bool bReliable = true) = 0;
//	virtual void				ClientCmd(const char* szCmdString) = 0;
//	virtual bool				GetPlayerInfo(int ent_num, PlayerInfo_t* pinfo) = 0;
//	virtual int					GetPlayerForUserID(int userID) = 0;
//	virtual client_textmessage_t* TextMessageGet(const char* pName) = 0;
//	virtual bool				Con_IsVisible(void) = 0;
//	virtual int					get_local_player(void) = 0;
//	virtual const model_t* LoadModel(const char* pName, bool bProp = false) = 0;
//	virtual float				Time(void) = 0;
//	virtual float				GetLastTimeStamp(void) = 0;
//	virtual CSentence* GetSentence(CAudioSource* pAudioSource) = 0;
//	virtual float				GetSentenceLength(CAudioSource* pAudioSource) = 0;
//	virtual bool				IsStreaming(CAudioSource* pAudioSource) const = 0;
//	virtual void				GetViewAngles(QAngle& va) = 0;
//	virtual void				SetViewAngles(QAngle& va) = 0;
//	virtual int					GetMaxClients(void) = 0;
//	virtual	const char* Key_LookupBinding(const char* pBinding) = 0;
//	virtual const char* Key_BindingForKey(DWORD code) = 0;
//	virtual void				StartKeyTrapMode(void) = 0;
//	virtual bool				CheckDoneKeyTrapping(DWORD& code) = 0;
//	virtual bool				is_in_game(void) = 0;
//	virtual bool				is_connected(void) = 0;
//	virtual bool				IsDrawingLoadingImage(void) = 0;
//	virtual void				Con_NPrintf(int pos, DWORD* fmt, ...) = 0;
//	virtual void				Con_NXPrintf(const struct con_nprint_s* info, DWORD* fmt, ...) = 0;
//	virtual int					IsBoxVisible(const vector& mins, const vector& maxs) = 0;
//	virtual int					IsBoxInViewCluster(const vector& mins, const vector& maxs) = 0;
//	virtual bool				CullBox(const vector& mins, const vector& maxs) = 0;
//	virtual void				Sound_ExtraUpdate(void) = 0;
//	virtual const char* GetGameDirectory(void) = 0;
//	virtual const D3DMATRIX& WorldToScreenMatrix() = 0;
//	virtual const VMatrix& WorldToViewMatrix() = 0;
//	virtual int					GameLumpVersion(int lumpId) const = 0;
//	virtual int					GameLumpSize(int lumpId) const = 0;
//	virtual bool				LoadGameLump(int lumpId, void* pBuffer, int size) = 0;
//	virtual int					LevelLeafCount() const = 0;
//	virtual ISpatialQuery* GetBSPTreeQuery() = 0;
//	virtual void		LinearToGamma(float* linear, float* gamma) = 0;
//	virtual float		LightStyleValue(int style) = 0;
//	virtual void		ComputeDynamicLighting(const vector& pt, const vector* pNormal, vector& color) = 0;
//	virtual void		GetAmbientLightColor(vector& color) = 0;
//	virtual int			GetDXSupportLevel() = 0;
//	virtual bool        SupportsHDR() = 0;
//	virtual void		Mat_Stub(IMaterialSystem* pMatSys) = 0;
//	virtual void GetChapterName(char* pchBuff, int iMaxLength) = 0;
//	virtual char const* GetLevelName(void) = 0;
//	virtual int	GetLevelVersion(void) = 0;
//	virtual struct IVoiceTweak_s* GetVoiceTweakAPI(void) = 0;
//	virtual void		EngineStats_BeginFrame(void) = 0;
//	virtual void		EngineStats_EndFrame(void) = 0;
//	virtual void		FireEvents() = 0;
//	virtual int			GetLeavesArea(int* pLeaves, int nLeaves) = 0;
//	virtual bool		DoesBoxTouchAreaFrustum(const vector& mins, const vector& maxs, int iArea) = 0;
//	virtual void		SetAudioState(const AudioState_t& state) = 0;
//	virtual int			SentenceGroupPick(int groupIndex, char* name, int nameBufLen) = 0;
//	virtual int			SentenceGroupPickSequential(int groupIndex, char* name, int nameBufLen, int sentenceIndex, int reset) = 0;
//	virtual int			SentenceIndexFromName(const char* pSentenceName) = 0;
//	virtual const char* SentenceNameFromIndex(int sentenceIndex) = 0;
//	virtual int			SentenceGroupIndexFromName(const char* pGroupName) = 0;
//	virtual const char* SentenceGroupNameFromIndex(int groupIndex) = 0;
//	virtual float		SentenceLength(int sentenceIndex) = 0;
//	virtual void		ComputeLighting(const vector& pt, const vector* pNormal, bool bClamp, vector& color, vector* pBoxColors = NULL) = 0;
//	virtual void		ActivateOccluder(int nOccluderIndex, bool bActive) = 0;
//	virtual bool		IsOccluded(const vector& vecAbsMins, const vector& vecAbsMaxs) = 0;
//	virtual void* SaveAllocMemory(size_t num, size_t size) = 0;
//	virtual void		SaveFreeMemory(void* pSaveMem) = 0;
//	virtual INetChannelInfo* GetNetChannelInfo(void) = 0;
//	virtual void		DebugDrawPhysCollide(const CPhysCollide* pCollide, IMaterial* pMaterial, matrix3x4_t& transform, const color& color) = 0;
//	virtual void		CheckPoint(const char* pName) = 0;
//	virtual void		DrawPortals() = 0;
//	virtual bool		IsPlayingDemo(void) = 0;
//	virtual bool		IsRecordingDemo(void) = 0;
//	virtual bool		IsPlayingTimeDemo(void) = 0;
//	virtual int			GetDemoRecordingTick(void) = 0;
//	virtual int			GetDemoPlaybackTick(void) = 0;
//	virtual int			GetDemoPlaybackStartTick(void) = 0;
//	virtual float		GetDemoPlaybackTimeScale(void) = 0;
//	virtual int			GetDemoPlaybackTotalTicks(void) = 0;
//	virtual bool		IsPaused(void) = 0;
//	virtual bool		IsTakingScreenshot(void) = 0;
//	virtual bool		IsHLTV(void) = 0;
//	virtual bool		IsLevelMainMenuBackground(void) = 0;
//	virtual void		GetMainMenuBackgroundName(char* dest, int destlen) = 0;
//	virtual void		GetVideoModes(int& nCount, DWORD*& pModes) = 0;
//	virtual void		SetOcclusionParameters(const DWORD& params) = 0;
//	virtual void		GetUILanguage(char* dest, int destlen) = 0;
//	virtual DWORD IsSkyboxVisibleFromPoint(const vector& vecPoint) = 0;
//	virtual const char* GetMapEntitiesString() = 0;
//	virtual bool		IsInEditMode(void) = 0;
//	virtual float		GetScreenAspectRatio() = 0;
//
//	// allow the game UI to login a user
//	virtual bool		REMOVED_SteamRefreshLogin(const char* password, bool isSecure) = 0;
//	virtual bool		REMOVED_SteamProcessCall(bool& finished) = 0;
//
//	// allow other modules to know about engine versioning (one use is a proxy for network compatability)
//	virtual unsigned int	GetEngineBuildNumber() = 0; // engines build
//	virtual const char* GetProductVersionString() = 0; // mods version number (steam.inf)
//
//	virtual void			GrabPreColorCorrectedFrame(int x, int y, int width, int height) = 0;
//	virtual bool			IsHammerRunning() const = 0;
//
//	virtual void			ExecuteClientCmd(const char* szCmdString) = 0;
//	virtual bool MapHasHDRLighting(void) = 0;
//
//	virtual int	GetAppID() = 0;
//	virtual vector			GetLightForPointFast(const vector& pos, bool bClamp) = 0;
//
//	virtual void			ClientCmd_Unrestricted(const char* szCmdString) = 0;
//
//	virtual void			SetRestrictServerCommands(bool bRestrict) = 0;
//
//	// If set to true (defaults to true for Valve games and false for others), then IVEngineClient::ClientCmd
//	// can only execute things marked with FCVAR_CLIENTCMD_CAN_EXECUTE.
//	virtual void			SetRestrictClientCommands(bool bRestrict) = 0;
//	virtual void			SetOverlayBindProxy(int iOverlayID, void* pBindProxy) = 0;
//	virtual bool			CopyFrameBufferToMaterial(const char* pMaterialName) = 0;
//	virtual void			ChangeTeam(const char* pTeamName) = 0;
//	virtual void			ReadConfiguration(const bool readDefault = false) = 0;
//	virtual void SetAchievementMgr(IAchievementMgr* pAchievementMgr) = 0;
//	virtual IAchievementMgr* GetAchievementMgr() = 0;
//	virtual bool			MapLoadFailed(void) = 0;
//	virtual void			SetMapLoadFailed(bool bState) = 0;
//	virtual bool			IsLowViolence() = 0;
//	virtual const char* GetMostRecentSaveGame(void) = 0;
//	virtual void			SetMostRecentSaveGame(const char* lpszFilename) = 0;
//
//	virtual void			StartXboxExitingProcess() = 0;
//	virtual bool			IsSaveInProgress() = 0;
//	virtual int			OnStorageDeviceAttached(void) = 0;
//	virtual void			OnStorageDeviceDetached(void) = 0;
//	virtual void			ResetDemoInterpolation(void) = 0;
//	virtual void SetGamestatsData(CGamestatsData* pGamestatsData) = 0;
//	virtual CGamestatsData* GetGamestatsData() = 0;
//	virtual void GetMouseDelta(int& x, int& y, bool bIgnoreNextMouseDelta = false) = 0;
//	virtual void			ServerCmdKeyValues(KeyValues* pKeyValues) = 0;
//	virtual bool			IsSkippingPlayback(void) = 0;
//	virtual bool			IsLoadingDemo(void) = 0;
//	virtual bool			IsPlayingDemoALocallyRecordedDemo() = 0;
//	virtual	const char* Key_LookupBindingExact(const char* pBinding) = 0;
//	virtual void			AddPhonemeFile(const char* pszPhonemeFile) = 0;
//	virtual float			GetPausedExpireTime(void) = 0;
//	virtual bool			StartDemoRecording(const char* pszFilename, const char* pszFolder = NULL) = 0;
//	virtual void			StopDemoRecording(void) = 0;
//	virtual void			TakeScreenshot(const char* pszFilename, const char* pszFolder = NULL) = 0;
//};

class IVEngineClient
{
public:
	int GetPlayerForUserID(int UserID)
	{
		using Original = int(__thiscall*)(PVOID, int);
		return utils::get_vfunc<Original>(this, 9)(this, UserID);
	}
	void ServerCmd(const char* chCommandString, bool bReliable = true)
	{
		typedef void(__thiscall* OriginalFn)(PVOID, const char*, bool);
		return utils::get_vfunc<OriginalFn>(this, 6)(this, chCommandString, bReliable);
	}
	void get_screen_size(int& width, int& height)
	{
		typedef void(__thiscall* OriginalFn)(PVOID, int&, int&);
		return utils::get_vfunc<OriginalFn>(this, 5)(this, width, height);
	}
	bool Con_IsVisible(void)
	{
		typedef bool(__thiscall* OriginalFn)(PVOID);
		return utils::get_vfunc<OriginalFn>(this, 11)(this);
	}
	int get_local_player(void)
	{
		typedef int(__thiscall* OriginalFn)(PVOID);
		return utils::get_vfunc<OriginalFn>(this, 12)(this);
	}
	float Time(void)
	{
		typedef float(__thiscall* OriginalFn)(PVOID);
		return utils::get_vfunc<OriginalFn>(this, 14)(this);
	}
	void GetViewAngles(vector& va)
	{
		typedef void(__thiscall* OriginalFn)(PVOID, vector& va);
		return utils::get_vfunc<OriginalFn>(this, 19)(this, va);
	}
	void SetViewAngles(vector& va)
	{
		typedef void(__thiscall* OriginalFn)(PVOID, vector& va);
		return utils::get_vfunc<OriginalFn>(this, 20)(this, va);
	}
	int get_max_clients(void)
	{
		typedef int(__thiscall* OriginalFn)(PVOID);
		return utils::get_vfunc<OriginalFn>(this, 21)(this);
	}
	bool is_in_game(void)
	{
		typedef bool(__thiscall* OriginalFn)(PVOID);
		return utils::get_vfunc<OriginalFn>(this, 26)(this);
	}
	bool is_connected(void)
	{
		typedef bool(__thiscall* OriginalFn)(PVOID);
		return utils::get_vfunc<OriginalFn>(this, 27)(this);
	}
	bool IsDrawingLoadingImage(void)
	{
		typedef bool(__thiscall* OriginalFn)(PVOID);
		return utils::get_vfunc<OriginalFn>(this, 28)(this);
	}
	const matrix3x4& WorldToScreenMatrix(void)
	{
		typedef const matrix3x4& (__thiscall* OriginalFn)(PVOID);
		return utils::get_vfunc<OriginalFn>(this, 36)(this);
	}
	bool IsTakingScreenshot(void)
	{
		typedef bool(__thiscall* OriginalFn)(PVOID);
		return utils::get_vfunc<OriginalFn>(this, 85)(this);
	}
	void ClientCmd(const char* szCommandString)
	{
		typedef void(__thiscall* ClientCmdFn)(void*, const char*);
		return utils::get_vfunc<ClientCmdFn>(this, 7)(this, szCommandString);
	}
	int GetAppId()
	{
		typedef int(__thiscall* OriginalFn)(PVOID);
		return utils::get_vfunc<OriginalFn>(this, 104)(this);
	}
	void ClientCmd_Unrestricted(const char* chCommandString)
	{
		typedef void(__thiscall* OriginalFn)(PVOID, const char*);
		return utils::get_vfunc<OriginalFn>(this, 106)(this, chCommandString);
	}
	void ServerCmdKeyValues(PVOID kv)
	{
		typedef void(__thiscall* OriginalFn)(PVOID, PVOID);
		utils::get_vfunc<OriginalFn>(this, 127)(this, kv);
	}
};