#pragma once
#include "..\vector.hpp"
#include "..\color.hpp"
#include "..\..\source-sdk\IEntity.h"

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

typedef struct PlayerInfo_s
{
	char			name[32];
	int				userID;
	char			guid[33];
	unsigned long	friendsID;
	char			friendsName[32];
	bool			fakeplayer;
	bool			ishltv;
	unsigned long	customFiles[4];
	unsigned char	filesDownloaded;
} PlayerInfo_t; // fixed for tf2.

struct cplane_t
{
	vector	normal;
	float	dist;
	unsigned char	type;			// for fast side tests
	unsigned char	signbits;		// signx + (sigsny<<1) + (signz<<1)
	unsigned char	pad[2];

};

enum VGuiPanel_t
{
	PANEL_ROOT = 0,
	PANEL_GAMEUIDLL,
	PANEL_CLIENTDLL,
	PANEL_TOOLS,
	PANEL_INGAMESCREENS,
	PANEL_GAMEDLL,
	PANEL_CLIENTDLL_TOOLS
};

enum PaintMode_t
{
	PAINT_UIPANELS = (1 << 0),
	PAINT_INGAMEPANELS = (1 << 1),
	PAINT_CURSOR = (1 << 2)
};

enum EFontFlags
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

enum EntityFlags : int
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

class CUserCmd final
{
public:
	virtual ~CUserCmd() {}; //Destructor 0
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
	bool hasbeenpredicted; //3C;
	/**
		// For matching server and client commands for debugging
	int		command_number;

	// the tick the client created this command
	int		tick_count;

	// Player instantaneous view angles.
	QAngle	viewangles;
	// Intended velocities
	//	forward velocity.
	float	forwardmove;
	//  sideways velocity.
	float	sidemove;
	//  upward velocity.
	float	upmove;
	// Attack button states
	int		buttons;
	// Impulse command issued.
	byte    impulse;
	// Current weapon id
	int		weaponselect;
	int		weaponsubtype;
	int		random_seed;	// For shared random functions
#ifdef GAME_DLL
	int		server_random_seed; // Only the server populates this seed
#endif
	short	mousedx;		// mouse accum in x from create move
	short	mousedy;		// mouse accum in y from create move
	// Client only, tracks whether we've predicted this command at least once
	bool	hasbeenpredicted;
	**/
};

static const char* get_class_name_string(int class_id) {
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
	}
}

static color get_team_color(C_BaseEntity* entity) {
	return (entity->get_team_num() == 2
		? color(255, 102, 0, 255)
		: entity->get_team_num() == 3
		? color(0, 102, 255, 255)
		: color(255, 255, 255, 255));
}