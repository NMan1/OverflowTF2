#pragma once
#include "..\vector.hpp"
#include "..\utils.hpp"
#include "..\..\source-sdk\i_entity.hpp"

#define IN_ATTACK		(1 << 0)
#define IN_JUMP			(1 << 1)
#define IN_DUCK			(1 << 2)
#define IN_FORWARD		(1 << 3)
#define IN_BACK			(1 << 4)
#define IN_USE			(1 << 5)
#define IN_CANCEL		(1 << 6)
#define IN_LEFT			(1 << 7)
#define IN_RIGHT		(1 << 8)
#define IN_MOVELEFT		(1 << 9)
#define IN_MOVERIGHT	(1 << 10)
#define IN_ATTACK2		(1 << 11)
#define IN_RUN			(1 << 12)
#define IN_RELOAD		(1 << 13)
#define IN_ALT1			(1 << 14)
#define IN_ALT2			(1 << 15)
#define IN_SCORE		(1 << 16)   // Used by client.dll for when scoreboard is held down
#define IN_SPEED		(1 << 17)	// Player is holding the speed key
#define IN_WALK			(1 << 18)	// Player holding walk key
#define IN_ZOOM			(1 << 19)	// Zoom key for HUD zoom
#define IN_WEAPON1		(1 << 20)	// weapon defines these bits
#define IN_WEAPON2		(1 << 21)	// weapon defines these bits
#define IN_BULLRUSH		(1 << 22)
#define IN_GRENADE1		(1 << 23)	// grenade 1
#define IN_GRENADE2		(1 << 24)	// grenade 2
#define	IN_ATTACK3		(1 << 25)

const float OUTLINE_WIDTH = 3;
const float LINE_WIDTH = 1;

typedef void* (*CreateInterfaceFn) (const char* pName, int* pReturnCode);
typedef void (*pfnDemoCustomDataCallback) (unsigned char* pData, size_t iSize);

typedef struct player_info_s
{
	char			name[32];
	int				userID;
	char			guid[33];
	unsigned long	friends_id;
	char			friends_name[32];
	bool			fakeplayer;
	bool			ishltv;
	unsigned long	customFiles[4];
	unsigned char	files_downloaded;
} player_info_t;

struct cplane_t
{
	vector	normal;
	float	dist;
	unsigned char	type;			// for fast side tests
	unsigned char	signbits;		// signx + (sigsny<<1) + (signz<<1)
	unsigned char	pad[2];

};

enum vgui_panel_t
{
	PANEL_ROOT = 0,
	PANEL_GAMEUIDLL,
	PANEL_CLIENTDLL,
	PANEL_TOOLS,
	PANEL_INGAMESCREENS,
	PANEL_GAMEDLL,
	PANEL_CLIENTDLL_TOOLS
};

enum paint_mode_t
{
	PAINT_UIPANELS = (1 << 0),
	PAINT_INGAMEPANELS = (1 << 1),
	PAINT_CURSOR = (1 << 2)
};

enum e_font_flags
{
	FONTFLAG_NONE,
	FONTFLAG_ITALIC = 0x001,
	FONTFLAG_UNDERLINE = 0x002,
	FONTFLAG_STRIKEOUT = 0x004,
	FONTFLAG_SYMBOL = 0x008,
	FONTFLAG_ANTIALIAS = 0x010,
	FONTFLAG_GAUSSIANBLUR = 0x020,
	FONTFLAG_ROTARY = 0x040,
	FONTFLAG_DROPSHADOW = 0x080,
	FONTFLAG_ADDITIVE = 0x100,
	FONTFLAG_OUTLINE = 0x200,
	FONTFLAG_CUSTOM = 0x400,
};

enum tf_cond
{
	TFCond_Slowed = (1 << 0), //Toggled when a player is slowed down. 
	TFCond_Zoomed = (1 << 1), //Toggled when a player is zoomed. 
	TFCond_Disguising = (1 << 2), //Toggled when a Spy is disguising.  
	TFCond_Disguised = (1 << 3), //Toggled when a Spy is disguised. 
	TFCond_Cloaked = (1 << 4), //Toggled when a Spy is invisible. 
	TFCond_Ubercharged = (1 << 5), //Toggled when a player is �berCharged. 
	TFCond_TeleportedGlow = (1 << 6), //Toggled when someone leaves a teleporter and has glow beneath their feet. 
	TFCond_Taunting = (1 << 7), //Toggled when a player is taunting. 
	TFCond_UberchargeFading = (1 << 8), //Toggled when the �berCharge is fading. 
	TFCond_CloakFlicker = (1 << 9), //Toggled when a Spy is visible during cloak. 
	TFCond_Teleporting = (1 << 10), //Only activates for a brief second when the player is being teleported; not very useful. 
	TFCond_Kritzkrieged = (1 << 11), //Toggled when a player is being crit buffed by the KritzKrieg. 
	TFCond_TmpDamageBonus = (1 << 12), //Unknown what this is for. Name taken from the AlliedModders SDK. 
	TFCond_DeadRingered = (1 << 13), //Toggled when a player is taking reduced damage from the Deadringer. 
	TFCond_Bonked = (1 << 14), //Toggled when a player is under the effects of The Bonk! Atomic Punch. 
	TFCond_Stunned = (1 << 15), //Toggled when a player's speed is reduced from airblast or a Sandman ball. 
	TFCond_Buffed = (1 << 16), //Toggled when a player is within range of an activated Buff Banner. 
	TFCond_Charging = (1 << 17), //Toggled when a Demoman charges with the shield. 
	TFCond_DemoBuff = (1 << 18), //Toggled when a Demoman has heads from the Eyelander. 
	TFCond_CritCola = (1 << 19), //Toggled when the player is under the effect of The Crit-a-Cola. 
	TFCond_InHealRadius = (1 << 20), //Unused condition, name taken from AlliedModders SDK. 
	TFCond_Healing = (1 << 21), //Toggled when someone is being healed by a medic or a dispenser. 
	TFCond_OnFire = (1 << 22), //Toggled when a player is on fire. 
	TFCond_Overhealed = (1 << 23), //Toggled when a player has >100% health. 
	TFCond_Jarated = (1 << 24), //Toggled when a player is hit with a Sniper's Jarate. 
	TFCond_Bleeding = (1 << 25), //Toggled when a player is taking bleeding damage. 
	TFCond_DefenseBuffed = (1 << 26), //Toggled when a player is within range of an activated Battalion's Backup. 
	TFCond_Milked = (1 << 27), //Player was hit with a jar of Mad Milk. 
	TFCond_MegaHeal = (1 << 28), //Player is under the effect of Quick-Fix charge. 
	TFCond_RegenBuffed = (1 << 29), //Toggled when a player is within a Concheror's range. 
	TFCond_MarkedForDeath = (1 << 30), //Player is marked for death by a Fan O'War hit. Effects are similar to TFCond_Jarated. 
	TFCond_NoHealingDamageBuff = (1 << 31), //Unknown what this is used for.

	TFCondEx_SpeedBuffAlly = (1 << 0), //Toggled when a player gets hit with the disciplinary action. 
	TFCondEx_HalloweenCritCandy = (1 << 1), //Only for Scream Fortress event maps that drop crit candy. 
	TFCondEx_CritCanteen = (1 << 2), //Player is getting a crit boost from a MVM canteen.
	TFCondEx_CritDemoCharge = (1 << 3), //From demo's shield
	TFCondEx_CritHype = (1 << 4), //Soda Popper crits. 
	TFCondEx_CritOnFirstBlood = (1 << 5), //Arena first blood crit buff. 
	TFCondEx_CritOnWin = (1 << 6), //End of round crits. 
	TFCondEx_CritOnFlagCapture = (1 << 7), //CTF intelligence capture crits. 
	TFCondEx_CritOnKill = (1 << 8), //Unknown what this is for. 
	TFCondEx_RestrictToMelee = (1 << 9), //Unknown what this is for. 
	TFCondEx_DefenseBuffNoCritBlock = (1 << 10), //MvM Buff.
	TFCondEx_Reprogrammed = (1 << 11), //MvM Bot has been reprogrammed.
	TFCondEx_PyroCrits = (1 << 12), //Player is getting crits from the Mmmph charge. 
	TFCondEx_PyroHeal = (1 << 13), //Player is being healed from the Mmmph charge. 
	TFCondEx_FocusBuff = (1 << 14), //Player is getting a focus buff.
	TFCondEx_DisguisedRemoved = (1 << 15), //Disguised remove from a bot.
	TFCondEx_MarkedForDeathSilent = (1 << 16), //Player is under the effects of the Escape Plan/Equalizer or GRU.
	TFCondEx_DisguisedAsDispenser = (1 << 17), //Bot is disguised as dispenser.
	TFCondEx_Sapped = (1 << 18), //MvM bot is being sapped.
	TFCondEx_UberchargedHidden = (1 << 19), //MvM Related
	TFCondEx_UberchargedCanteen = (1 << 20), //Player is receiving �berCharge from a canteen.
	TFCondEx_HalloweenBombHead = (1 << 21), //Player has a bomb on their head from Merasmus.
	TFCondEx_HalloweenThriller = (1 << 22), //Players are forced to dance from Merasmus.
	TFCondEx_BulletCharge = (1 << 26), //Player is receiving 75% reduced damage from bullets.
	TFCondEx_ExplosiveCharge = (1 << 27), //Player is receiving 75% reduced damage from explosives.
	TFCondEx_FireCharge = (1 << 28), //Player is receiving 75% reduced damage from fire.
	TFCondEx_BulletResistance = (1 << 29), //Player is receiving 10% reduced damage from bullets.
	TFCondEx_ExplosiveResistance = (1 << 30), //Player is receiving 10% reduced damage from explosives.
	TFCondEx_FireResistance = (1 << 31), //Player is receiving 10% reduced damage from fire.

	TFCondEx2_Stealthed = (1 << 0),
	TFCondEx2_MedigunDebuff = (1 << 1),
	TFCondEx2_StealthedUserBuffFade = (1 << 2),
	TFCondEx2_BulletImmune = (1 << 3),
	TFCondEx2_BlastImmune = (1 << 4),
	TFCondEx2_FireImmune = (1 << 5),
	TFCondEx2_PreventDeath = (1 << 6),
	TFCondEx2_MVMBotRadiowave = (1 << 7),
	TFCondEx2_HalloweenSpeedBoost = (1 << 8), //Wheel has granted player speed boost.
	TFCondEx2_HalloweenQuickHeal = (1 << 9), //Wheel has granted player quick heal.
	TFCondEx2_HalloweenGiant = (1 << 10), //Wheel has granted player giant mode.
	TFCondEx2_HalloweenTiny = (1 << 11), //Wheel has granted player tiny mode.
	TFCondEx2_HalloweenInHell = (1 << 12), //Wheel has granted player in hell mode.
	TFCondEx2_HalloweenGhostMode = (1 << 13), //Wheel has granted player ghost mode.
	TFCondEx2_Parachute = (1 << 16), //Player has deployed the BASE Jumper.
	TFCondEx2_BlastJumping = (1 << 17), //Player has sticky or rocket jumped.

	TFCond_MiniCrits = (TFCond_Buffed | TFCond_CritCola),
	TFCond_IgnoreStates = (TFCond_Ubercharged | TFCond_Bonked),
	TFCondEx_IgnoreStates = (TFCondEx_PyroHeal)
};

enum tf_classes
{
	TF2_Scout = 1,
	TF2_Soldier = 3,
	TF2_Pyro = 7,
	TF2_Demoman = 4,
	TF2_Heavy = 6,
	TF2_Engineer = 9,
	TF2_Medic = 5,
	TF2_Sniper = 2,
	TF2_Spy = 8,
};

enum source_lifestates
{
	LIFE_ALIVE,
	LIFE_DYING,
	LIFE_DEAD,
	LIFE_RESPAWNABLE,
	LIFE_DISCARDBODY,
};

enum entity_flags : int
{
	FL_ONGROUND = (1 << 0),
	FL_DUCKING = (1 << 1),
	FL_WATERJUMP = (1 << 2),
	FL_ONTRAIN = (1 << 3),
	FL_INRAIN = (1 << 4),
	FL_FROZEN = (1 << 5),
	FL_ATCONTROLS = (1 << 6),
	FL_CLIENT = (1 << 7),
	FL_FAKECLIENT = (1 << 8)
};

class c_user_cmd final
{
public:
	virtual ~c_user_cmd() {}; //Destructor 0
	int command_number; //4
	int tick_count; //8
	vector viewangles; //C
	float forwardmove; //18
	float sidemove; //1C
	float upmove; //20
	int	buttons; //24
	unsigned char impulse; //28
	int weaponselect; //2C
	int weaponsubtype; //30
	int random_seed; //34
	short mousedx; //38
	short mousedy; //3A
	bool has_been_predicted; //3C;
};

struct mstudiobbox_t
{
	int bone;
	int group;
	vector bbmin;
	vector bbmax;
	int szhitboxnameindex;
	int unused[8];
};

struct mstudiohitboxset_t
{
	int sznameindex;
	inline char* const name(void) const { return ((char*)this) + sznameindex; }
	int numhitboxes;
	int hitboxindex;
	mstudiobbox_t* hitbox(int i) const { return (mstudiobbox_t*)(((unsigned char*)this) + hitboxindex) + i; };
};

struct studiohdr_t
{
	unsigned char		pad00[12];
	char				name[64];
	unsigned char		pad01[80];
	int					numbones;
	int					boneindex;
	unsigned char		pad02[12];
	int					hitboxsetindex;
	unsigned char		pad03[228];

	mstudiohitboxset_t* pHitboxSet(int i) const
	{
		return (mstudiohitboxset_t*)(((unsigned char*)this) + hitboxsetindex) + i;
	};

	mstudiobbox_t* pHitbox(int i, int set) const
	{
		const mstudiohitboxset_t* s = pHitboxSet(set);
		if (!s)
			return 0;

		return s->hitbox(i);
	};

	int			iHitboxCount(int set) const
	{
		const mstudiohitboxset_t* s = pHitboxSet(set);
		if (!s)
			return 0;

		return s->numhitboxes;
	};
};

enum hitboxes
{
	HITBOX_HEAD,
	HITBOX_NECK,
	HITBOX_LOWER_NECK,
	HITBOX_PELVIS,
	HITBOX_BODY,
	HITBOX_THORAX,
	HITBOX_CHEST,
	HITBOX_UPPER_CHEST,
	HITBOX_RIGHT_THIGH,
	HITBOX_LEFT_THIGH,
	HITBOX_RIGHT_CALF,
	HITBOX_LEFT_CALF,
	HITBOX_RIGHT_FOOT,
	HITBOX_LEFT_FOOT,
	HITBOX_RIGHT_HAND,
	HITBOX_LEFT_HAND,
	HITBOX_RIGHT_UPPER_ARM,
	HITBOX_RIGHT_FOREARM,
	HITBOX_LEFT_UPPER_ARM,
	HITBOX_LEFT_FOREARM,
	HITBOX_MAX
};

enum SurfaceFlags_t
{
	DISPSURF_FLAG_SURFACE = (1 << 0),
	DISPSURF_FLAG_WALKABLE = (1 << 1),
	DISPSURF_FLAG_BUILDABLE = (1 << 2),
	DISPSURF_FLAG_SURFPROP1 = (1 << 3),
	DISPSURF_FLAG_SURFPROP2 = (1 << 4),
};


struct csurface_t
{
	const char* name;
	short			surfaceProps;
	unsigned short	flags;
};

class __declspec(align(16))VectorAligned : public vector
{
public:
	inline VectorAligned(void) {};

	inline VectorAligned(float X, float Y, float Z)
	{
		init(X, Y, Z);
	}

	explicit VectorAligned(const vector& vOther)
	{
		init(vOther.x, vOther.y, vOther.z);
	}

	VectorAligned& operator=(const vector& vOther)
	{
		init(vOther.x, vOther.y, vOther.z);
		return *this;
	}

	float w;
};

struct Ray_t
{
	VectorAligned   m_Start;
	VectorAligned   m_Delta;
	VectorAligned   m_StartOffset;
	VectorAligned   m_Extents;

	bool    m_IsRay;
	bool    m_IsSwept;

	void Init(vector& start, vector& end)
	{
		m_Delta = end - start;

		m_IsSwept = (m_Delta.length_sqr() != 0);

		m_Extents.init();
		m_IsRay = true;

		m_StartOffset.init();
		m_Start = start;
	}

	void Init(vector& start, vector& end, vector& mins, vector& maxs)
	{
		m_Delta = end - start;

		m_IsSwept = (m_Delta.length_sqr() != 0);

		m_Extents = maxs - mins;
		m_Extents *= 0.5f;
		m_IsRay = (m_Extents.length_sqr() < 1e-6);

		m_StartOffset = mins + maxs;
		m_StartOffset *= 0.5f;
		m_Start = start - m_StartOffset;
		m_StartOffset *= -1.0f;
	}
};

class c_base_trace
{
public:
	bool IsDispSurface(void) { return ((dispFlags & DISPSURF_FLAG_SURFACE) != 0); }
	bool IsDispSurfaceWalkable(void) { return ((dispFlags & DISPSURF_FLAG_WALKABLE) != 0); }
	bool IsDispSurfaceBuildable(void) { return ((dispFlags & DISPSURF_FLAG_BUILDABLE) != 0); }
	bool IsDispSurfaceProp1(void) { return ((dispFlags & DISPSURF_FLAG_SURFPROP1) != 0); }
	bool IsDispSurfaceProp2(void) { return ((dispFlags & DISPSURF_FLAG_SURFPROP2) != 0); }

public:
	vector			startpos;
	vector			endpos;
	cplane_t		plane;

	float			fraction;

	int				contents;
	unsigned short	dispFlags;

	bool			allsolid;
	bool			startsolid;

	c_base_trace() {}

private:
	c_base_trace(const c_base_trace& vOther);
};

class c_game_trace : public c_base_trace
{
public:
	bool did_hit_world() const;

	bool did_hit_non_world_entity() const;

	int get_entity_index() const;

	bool did_hit() const
	{
		return fraction < 1 || allsolid || startsolid;
	}

public:
	float			fractionleftsolid;
	csurface_t		surface;

	int				hitgroup;

	short			physicsbone;

	c_base_entity*  m_pEnt;
	int				hitbox;

	c_game_trace() {}
	c_game_trace(const c_game_trace& vOther);
};
typedef c_game_trace trace_t;

enum TraceType_t
{
	TRACE_EVERYTHING = 0,
	TRACE_WORLD_ONLY,				// NOTE: This does *not* test static props!!!
	TRACE_ENTITIES_ONLY,			// NOTE: This version will *not* test static props
	TRACE_EVERYTHING_FILTER_PROPS,	// NOTE: This version will pass the IHandleEntity for props through the filter, unlike all other filters
};

class ITraceFilter
{
public:
	virtual bool ShouldHitEntity(void* pEntity, int contentsMask) = 0;
	virtual TraceType_t	GetTraceType() const = 0;
};

class i_engine_trace
{
public:	  //We really only need this I guess...
	void trace_ray(const Ray_t& ray, unsigned int fMask, ITraceFilter* pTraceFilter, trace_t* pTrace)//5
	{
		typedef void(__thiscall* TraceRayFn)(void*, const Ray_t&, unsigned int, ITraceFilter*, trace_t*);
		return utils::get_vfunc <TraceRayFn>(this, 4)(this, ray, fMask, pTraceFilter, pTrace);
	}
};
class RecvTable;
class client_class
{
private:
	unsigned char _chPadding[8];
public:
	char* chName;
	RecvTable* Table;
	client_class* pNextClass;
	int iClassID;
};

class c_trace_filter : public ITraceFilter
{
public:
	virtual bool ShouldHitEntity(void* pEntityHandle, int contentsMask)
	{
		c_base_entity* pEntity = (c_base_entity*)pEntityHandle;

		switch (pEntity->get_client_class()->iClassID)
		{
		case 55: // Portal Window
		case 64: // Spawn Door visualizers
		case 117: // Sniper Dots
		case 225: // Medigun Shield
			return false;
			break;
		}

		return !(pEntityHandle == pSkip);
	}

	virtual TraceType_t	GetTraceType() const
	{
		return TRACE_EVERYTHING;
	}

	void* pSkip;
};

#define CONTENTS_EMPTY 0 // No contents

#define CONTENTS_SOLID 0x1  // an eye is never valid in a solid
#define CONTENTS_WINDOW 0x2 // translucent, but not watery (glass)
#define CONTENTS_AUX 0x4
#define CONTENTS_GRATE 0x8 // alpha-tested "grate" textures.  Bullets/sight pass through, but solids don't
#define CONTENTS_SLIME 0x10
#define CONTENTS_WATER 0x20
#define CONTENTS_BLOCKLOS 0x40 // block AI line of sight
#define CONTENTS_OPAQUE 0x80   // things that cannot be seen through (may be non-solid though)
#define LAST_VISIBLE_CONTENTS 0x80

#define ALL_VISIBLE_CONTENTS ( LAST_VISIBLE_CONTENTS | ( LAST_VISIBLE_CONTENTS - 1 ) )

#define CONTENTS_TESTFOGVOLUME 0x100
#define CONTENTS_UNUSED 0x200

// unused
// NOTE: If it's visible, grab from the top + update LAST_VISIBLE_CONTENTS
// if not visible, then grab from the bottom.
#define CONTENTS_UNUSED6 0x400

#define CONTENTS_TEAM1 0x800  // per team contents used to differentiate collisions
#define CONTENTS_TEAM2 0x1000 // between players and objects on different teams

// ignore CONTENTS_OPAQUE on surfaces that have SURF_NODRAW
#define CONTENTS_IGNORE_NODRAW_OPAQUE 0x2000

// hits entities which are MOVETYPE_PUSH (doors, plats, etc.)
#define CONTENTS_MOVEABLE 0x4000

// remaining contents are non-visible, and don't eat brushes
#define CONTENTS_AREAPORTAL 0x8000

#define CONTENTS_PLAYERCLIP 0x10000
#define CONTENTS_MONSTERCLIP 0x20000

// currents can be added to any other contents, and may be mixed
#define CONTENTS_CURRENT_0 0x40000
#define CONTENTS_CURRENT_90 0x80000
#define CONTENTS_CURRENT_180 0x100000
#define CONTENTS_CURRENT_270 0x200000
#define CONTENTS_CURRENT_UP 0x400000
#define CONTENTS_CURRENT_DOWN 0x800000

#define CONTENTS_ORIGIN 0x1000000 // removed before bsping an entity

#define CONTENTS_MONSTER 0x2000000 // should never be on a brush, only in game
#define CONTENTS_DEBRIS 0x4000000
#define CONTENTS_DETAIL 0x8000000		// brushes to be added after vis leafs
#define CONTENTS_TRANSLUCENT 0x10000000 // auto set if any surface has trans
#define CONTENTS_LADDER 0x20000000
#define CONTENTS_HITBOX 0x40000000 // use accurate hitboxes on trace

// NOTE: These are stored in a short in the engine now.  Don't use more than 16 bits
#define SURF_LIGHT 0x0001 // value will hold the light strength
#define SURF_SKY2D 0x0002 // don't draw, indicates we should skylight + draw 2d sky but not draw the 3D skybox
#define SURF_SKY 0x0004   // don't draw, but add to skybox
#define SURF_WARP 0x0008  // turbulent water warp
#define SURF_TRANS 0x0010
#define SURF_NOPORTAL 0x0020 // the surface can not have a portal placed on it
#define SURF_TRIGGER 0x0040  // FIXME: This is an xbox hack to work around elimination of trigger surfaces, which breaks occluders
#define SURF_NODRAW 0x0080   // don't bother referencing the texture

#define SURF_HINT 0x0100 // make a primary bsp splitter

#define SURF_SKIP 0x0200	  // completely ignore, allowing non-closed brushes
#define SURF_NOLIGHT 0x0400   // Don't calculate light
#define SURF_BUMPLIGHT 0x0800 // calculate three lightmaps for the surface for bumpmapping
#define SURF_NOSHADOWS 0x1000 // Don't receive shadows
#define SURF_NODECALS 0x2000  // Don't receive decals
#define SURF_NOCHOP 0x4000	// Don't subdivide patches on this surface
#define SURF_HITBOX 0x8000	// surface is part of a hitbox

// -----------------------------------------------------
// spatial content masks - used for spatial queries (traceline,etc.)
// -----------------------------------------------------
#define MASK_ALL ( 0xFFFFFFFF )
// everything that is normally solid
#define MASK_SOLID ( CONTENTS_SOLID | CONTENTS_MOVEABLE | CONTENTS_WINDOW | CONTENTS_MONSTER | CONTENTS_GRATE )
// everything that blocks player movement
#define MASK_PLAYERSOLID ( CONTENTS_SOLID | CONTENTS_MOVEABLE | CONTENTS_PLAYERCLIP | CONTENTS_WINDOW | CONTENTS_MONSTER | CONTENTS_GRATE )
// blocks npc movement
#define MASK_NPCSOLID ( CONTENTS_SOLID | CONTENTS_MOVEABLE | CONTENTS_MONSTERCLIP | CONTENTS_WINDOW | CONTENTS_MONSTER | CONTENTS_GRATE )
// water physics in these contents
#define MASK_WATER ( CONTENTS_WATER | CONTENTS_MOVEABLE | CONTENTS_SLIME )
// everything that blocks lighting
#define MASK_OPAQUE ( CONTENTS_SOLID | CONTENTS_MOVEABLE | CONTENTS_OPAQUE )
// everything that blocks lighting, but with monsters added.
#define MASK_OPAQUE_AND_NPCS ( MASK_OPAQUE | CONTENTS_MONSTER )
// everything that blocks line of sight for AI
#define MASK_BLOCKLOS ( CONTENTS_SOLID | CONTENTS_MOVEABLE | CONTENTS_BLOCKLOS )
// everything that blocks line of sight for AI plus NPCs
#define MASK_BLOCKLOS_AND_NPCS ( MASK_BLOCKLOS | CONTENTS_MONSTER )
// everything that blocks line of sight for players
#define MASK_VISIBLE ( MASK_OPAQUE | CONTENTS_IGNORE_NODRAW_OPAQUE )
// everything that blocks line of sight for players, but with monsters added.
#define MASK_VISIBLE_AND_NPCS ( MASK_OPAQUE_AND_NPCS | CONTENTS_IGNORE_NODRAW_OPAQUE )
// bullets see these as solid
#define MASK_SHOT ( CONTENTS_SOLID | CONTENTS_MOVEABLE | CONTENTS_MONSTER | CONTENTS_WINDOW | CONTENTS_DEBRIS | CONTENTS_HITBOX )
// non-raycasted weapons see this as solid (includes grates)
#define MASK_SHOT_HULL ( CONTENTS_SOLID | CONTENTS_MOVEABLE | CONTENTS_MONSTER | CONTENTS_WINDOW | CONTENTS_DEBRIS | CONTENTS_GRATE )
// hits solids (not grates) and passes through everything else
#define MASK_SHOT_PORTAL ( CONTENTS_SOLID | CONTENTS_MOVEABLE | CONTENTS_WINDOW | CONTENTS_MONSTER )
// everything normally solid, except monsters (world+brush only)
#define MASK_SOLID_BRUSHONLY ( CONTENTS_SOLID | CONTENTS_MOVEABLE | CONTENTS_WINDOW | CONTENTS_GRATE )
// everything normally solid for player movement, except monsters (world+brush only)
#define MASK_PLAYERSOLID_BRUSHONLY ( CONTENTS_SOLID | CONTENTS_MOVEABLE | CONTENTS_WINDOW | CONTENTS_PLAYERCLIP | CONTENTS_GRATE )
// everything normally solid for npc movement, except monsters (world+brush only)
#define MASK_NPCSOLID_BRUSHONLY ( CONTENTS_SOLID | CONTENTS_MOVEABLE | CONTENTS_WINDOW | CONTENTS_MONSTERCLIP | CONTENTS_GRATE )
// just the world, used for route rebuilding
#define MASK_NPCWORLDSTATIC ( CONTENTS_SOLID | CONTENTS_WINDOW | CONTENTS_MONSTERCLIP | CONTENTS_GRATE )
// These are things that can split areaportals
#define MASK_SPLITAREAPORTAL ( CONTENTS_WATER | CONTENTS_SLIME )

// UNDONE: This is untested, any moving water
#define MASK_CURRENT ( CONTENTS_CURRENT_0 | CONTENTS_CURRENT_90 | CONTENTS_CURRENT_180 | CONTENTS_CURRENT_270 | CONTENTS_CURRENT_UP | CONTENTS_CURRENT_DOWN )

// everything that blocks corpse movement
// UNDONE: Not used yet / may be deleted
#define MASK_DEADSOLID ( CONTENTS_SOLID | CONTENTS_PLAYERCLIP | CONTENTS_WINDOW | CONTENTS_GRATE )
