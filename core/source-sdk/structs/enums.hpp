#pragma once


enum weapon_type
{
	WEAPON_NONE = 0,
	BAT,
	BAT_WOOD,
	BOTTLE,
	FIREAXE,
	CLUB,
	CROWBAR,
	KNIFE,
	FISTS,
	SHOVEL,
	WRENCH,
	BONESAW,
	SHOTGUN_PRIMARY,
	SHOTGUN_SOLDIER,
	SHOTGUN_HWG,
	SHOTGUN_PYRO,
	SCATTERGUN,
	SNIPERRIFLE,
	MINIGUN,
	SMG,
	SYRINGEGUN_MEDIC,
	TRANQ,
	ROCKETLAUNCHER,
	GRENADELAUNCHER,
	PIPEBOMBLAUNCHER,
	FLAMETHROWER,
	GRENADE_NORMAL,
	GRENADE_CONCUSSION,
	GRENADE_NAIL,
	GRENADE_MIRV,
	GRENADE_MIRV_DEMOMAN,
	GRENADE_NAPALM,
	GRENADE_GAS,
	GRENADE_EMP,
	GRENADE_CALTROP,
	GRENADE_PIPEBOMB,
	GRENADE_SMOKE_BOMB,
	GRENADE_HEAL,
	GRENADE_STUNBALL,
	GRENADE_JAR,
	GRENADE_JAR_MILK,
	PISTOL,
	PISTOL_SCOUT,
	REVOLVER,
	NAILGUN,
	PDA,
	PDA_ENGINEER_BUILD,
	PDA_ENGINEER_DESTROY,
	PDA_SPY,
	BUILDER,
	MEDIGUN,
	GRENADE_MIRVBOMB,
	FLAMETHROWER_ROCKET,
	GRENADE_DEMOMAN,
	SENTRY_BULLET,
	SENTRY_ROCKET,
	DISPENSER,
	INVIS,
	FLAREGUN,
	LUNCHBOX,
	JAR,
	COMPOUND_BOW,
	BUFF_ITEM,
	PUMPKIN_BOMB,
	SWORD,
	ROCKETLAUNCHER_DIRECTHIT,
	LIFELINE,
	LASER_POINTER,
	DISPENSER_GUN,
	SENTRY_REVENGE,
	JAR_MILK,
	HANDGUN_SCOUT_PRIMARY,
	BAT_FISH,
	CROSSBOW,
	STICKBOMB,
	HANDGUN_SCOUT_SECONDARY,
	SODA_POPPER,
	SNIPERRIFLE_DECAP,
	RAYGUN,
	PARTICLE_CANNON,
	MECHANICAL_ARM,
	DRG_POMSON,
	BAT_GIFTWRAP,
	GRENADE_ORNAMENT_BALL,
	FLAREGUN_REVENGE,
	PEP_BRAWLER_BLASTER,
	CLEAVER,
	GRENADE_CLEAVER,
	STICKY_BALL_LAUNCHER,
	GRENADE_STICKY_BALL,
	SHOTGUN_BUILDING_RESCUE,
	CANNON,
	THROWABLE,
	GRENADE_THROWABLE,
	PDA_SPY_BUILD,
	GRENADE_WATERBALLOON,
	HARVESTER_SAW,
	SPELLBOOK,
	SPELLBOOK_PROJECTILE,
	SNIPERRIFLE_CLASSIC,
	PARACHUTE,
	GRAPPLINGHOOK,
	PASSTIME_GUN,
	CHARGED_SMG,
	COUNT
};

enum stereo_eye
{
	STEREO_EYE_MONO = 0,
	STEREO_EYE_LEFT = 1,
	STEREO_EYE_RIGHT = 2,
	STEREO_EYE_MAX = 3,
};

enum vgui_panel
{
	ROOT = 0,
	GAMEUIDLL,
	CLIENTDLL,
	TOOLS,
	INGAMESCREENS,
	GAMEDLL,
	CLIENTDLL_TOOLS
};

enum paint_mode
{
	UIPANELS = (1 << 0),
	INGAMEPANELS = (1 << 1),
	CURSOR = (1 << 2)
};

enum font_flags
{
	NONE,
	ITALIC = 0x001,
	UNDERLINE = 0x002,
	STRIKEOUT = 0x004,
	SYMBOL = 0x008,
	ANTIALIAS = 0x010,
	GAUSSIANBLUR = 0x020,
	ROTARY = 0x040,
	DROPSHADOW = 0x080,
	ADDITIVE = 0x100,
	OUTLINE = 0x200,
	CUSTOM = 0x400,
};

enum conditions
{
	SLOWED = (1 << 0), //TOGGLED WHEN A PLAYER IS SLOWED DOWN. 
	ZOOMED = (1 << 1), //TOGGLED WHEN A PLAYER IS ZOOMED. 
	DISGUISING = (1 << 2), //TOGGLED WHEN A SPY IS DISGUISING.  
	DISGUISED = (1 << 3), //TOGGLED WHEN A SPY IS DISGUISED. 
	CLOAKED = (1 << 4), //TOGGLED WHEN A SPY IS INVISIBLE. 
	UBERCHARGED = (1 << 5), //TOGGLED WHEN A PLAYER IS �BERCHARGED. 
	TELEPORTEDGLOW = (1 << 6), //TOGGLED WHEN SOMEONE LEAVES A TELEPORTER AND HAS GLOW BENEATH THEIR FEET. 
	TAUNTING = (1 << 7), //TOGGLED WHEN A PLAYER IS TAUNTING. 
	UBERCHARGEFADING = (1 << 8), //TOGGLED WHEN THE �BERCHARGE IS FADING. 
	CLOAKFLICKER = (1 << 9), //TOGGLED WHEN A SPY IS VISIBLE DURING CLOAK. 
	TELEPORTING = (1 << 10), //ONLY ACTIVATES FOR A BRIEF SECOND WHEN THE PLAYER IS BEING TELEPORTED; NOT VERY USEFUL. 
	KRITZKRIEGED = (1 << 11), //TOGGLED WHEN A PLAYER IS BEING CRIT BUFFED BY THE KRITZKRIEG. 
	TMPDAMAGEBONUS = (1 << 12), //UNKNOWN WHAT THIS IS FOR. NAME TAKEN FROM THE ALLIEDMODDERS SDK. 
	DEADRINGERED = (1 << 13), //TOGGLED WHEN A PLAYER IS TAKING REDUCED DAMAGE FROM THE DEADRINGER. 
	BONKED = (1 << 14), //TOGGLED WHEN A PLAYER IS UNDER THE EFFECTS OF THE BONK! ATOMIC PUNCH. 
	STUNNED = (1 << 15), //TOGGLED WHEN A PLAYER'S SPEED IS REDUCED FROM AIRBLAST OR A SANDMAN BALL. 
	BUFFED = (1 << 16), //TOGGLED WHEN A PLAYER IS WITHIN RANGE OF AN ACTIVATED BUFF BANNER. 
	CHARGING = (1 << 17), //TOGGLED WHEN A DEMOMAN CHARGES WITH THE SHIELD. 
	DEMOBUFF = (1 << 18), //TOGGLED WHEN A DEMOMAN HAS HEADS FROM THE EYELANDER. 
	CRITCOLA = (1 << 19), //TOGGLED WHEN THE PLAYER IS UNDER THE EFFECT OF THE CRIT-A-COLA. 
	INHEALRADIUS = (1 << 20), //UNUSED CONDITION, NAME TAKEN FROM ALLIEDMODDERS SDK. 
	HEALING = (1 << 21), //TOGGLED WHEN SOMEONE IS BEING HEALED BY A MEDIC OR A DISPENSER. 
	ONFIRE = (1 << 22), //TOGGLED WHEN A PLAYER IS ON FIRE. 
	OVERHEALED = (1 << 23), //TOGGLED WHEN A PLAYER HAS >100% HEALTH. 
	JARATED = (1 << 24), //TOGGLED WHEN A PLAYER IS HIT WITH A SNIPER'S JARATE. 
	BLEEDING = (1 << 25), //TOGGLED WHEN A PLAYER IS TAKING BLEEDING DAMAGE. 
	DEFENSEBUFFED = (1 << 26), //TOGGLED WHEN A PLAYER IS WITHIN RANGE OF AN ACTIVATED BATTALION'S BACKUP. 
	MILKED = (1 << 27), //PLAYER WAS HIT WITH A JAR OF MAD MILK. 
	MEGAHEAL = (1 << 28), //PLAYER IS UNDER THE EFFECT OF QUICK-FIX CHARGE. 
	REGENBUFFED = (1 << 29), //TOGGLED WHEN A PLAYER IS WITHIN A CONCHEROR'S RANGE. 
	MARKEDFORDEATH = (1 << 30), //PLAYER IS MARKED FOR DEATH BY A FAN O'WAR HIT. EFFECTS ARE SIMILAR TO JARATED. 
	NOHEALINGDAMAGEBUFF = (1 << 31), //UNKNOWN WHAT THIS IS USED FOR.

	SPEEDBUFFALLY = (1 << 0), //TOGGLED WHEN A PLAYER GETS HIT WITH THE DISCIPLINARY ACTION. 
	HALLOWEENCRITCANDY = (1 << 1), //ONLY FOR SCREAM FORTRESS EVENT MAPS THAT DROP CRIT CANDY. 
	CRITCANTEEN = (1 << 2), //PLAYER IS GETTING A CRIT BOOST FROM A MVM CANTEEN.
	CRITDEMOCHARGE = (1 << 3), //FROM DEMO'S SHIELD
	CRITHYPE = (1 << 4), //SODA POPPER CRITS. 
	CRITONFIRSTBLOOD = (1 << 5), //ARENA FIRST BLOOD CRIT BUFF. 
	CRITONWIN = (1 << 6), //END OF ROUND CRITS. 
	CRITONFLAGCAPTURE = (1 << 7), //CTF INTELLIGENCE CAPTURE CRITS. 
	CRITONKILL = (1 << 8), //UNKNOWN WHAT THIS IS FOR. 
	RESTRICTTOMELEE = (1 << 9), //UNKNOWN WHAT THIS IS FOR. 
	DEFENSEBUFFNOCRITBLOCK = (1 << 10), //MVM BUFF.
	REPROGRAMMED = (1 << 11), //MVM BOT HAS BEEN REPROGRAMMED.
	PYROCRITS = (1 << 12), //PLAYER IS GETTING CRITS FROM THE MMMPH CHARGE. 
	PYROHEAL = (1 << 13), //PLAYER IS BEING HEALED FROM THE MMMPH CHARGE. 
	FOCUSBUFF = (1 << 14), //PLAYER IS GETTING A FOCUS BUFF.
	DISGUISEDREMOVED = (1 << 15), //DISGUISED REMOVE FROM A BOT.
	MARKEDFORDEATHSILENT = (1 << 16), //PLAYER IS UNDER THE EFFECTS OF THE ESCAPE PLAN/EQUALIZER OR GRU.
	DISGUISEDASDISPENSER = (1 << 17), //BOT IS DISGUISED AS DISPENSER.
	SAPPED = (1 << 18), //MVM BOT IS BEING SAPPED.
	UBERCHARGEDHIDDEN = (1 << 19), //MVM RELATED
	UBERCHARGEDCANTEEN = (1 << 20), //PLAYER IS RECEIVING �BERCHARGE FROM A CANTEEN.
	HALLOWEENBOMBHEAD = (1 << 21), //PLAYER HAS A BOMB ON THEIR HEAD FROM MERASMUS.
	HALLOWEENTHRILLER = (1 << 22), //PLAYERS ARE FORCED TO DANCE FROM MERASMUS.
	BULLETCHARGE = (1 << 26), //PLAYER IS RECEIVING 75% REDUCED DAMAGE FROM BULLETS.
	EXPLOSIVECHARGE = (1 << 27), //PLAYER IS RECEIVING 75% REDUCED DAMAGE FROM EXPLOSIVES.
	FIRECHARGE = (1 << 28), //PLAYER IS RECEIVING 75% REDUCED DAMAGE FROM FIRE.
	BULLETRESISTANCE = (1 << 29), //PLAYER IS RECEIVING 10% REDUCED DAMAGE FROM BULLETS.
	EXPLOSIVERESISTANCE = (1 << 30), //PLAYER IS RECEIVING 10% REDUCED DAMAGE FROM EXPLOSIVES.
	FIRERESISTANCE = (1 << 31), //PLAYER IS RECEIVING 10% REDUCED DAMAGE FROM FIRE.

	STEALTHED = (1 << 0),
	MEDIGUNDEBUFF = (1 << 1),
	STEALTHEDUSERBUFFFADE = (1 << 2),
	BULLETIMMUNE = (1 << 3),
	BLASTIMMUNE = (1 << 4),
	FIREIMMUNE = (1 << 5),
	PREVENTDEATH = (1 << 6),
	MVMBOTRADIOWAVE = (1 << 7),
	HALLOWEENSPEEDBOOST = (1 << 8), //WHEEL HAS GRANTED PLAYER SPEED BOOST.
	HALLOWEENQUICKHEAL = (1 << 9), //WHEEL HAS GRANTED PLAYER QUICK HEAL.
	HALLOWEENGIANT = (1 << 10), //WHEEL HAS GRANTED PLAYER GIANT MODE.
	HALLOWEENTINY = (1 << 11), //WHEEL HAS GRANTED PLAYER TINY MODE.
	HALLOWEENINHELL = (1 << 12), //WHEEL HAS GRANTED PLAYER IN HELL MODE.
	HALLOWEENGHOSTMODE = (1 << 13), //WHEEL HAS GRANTED PLAYER GHOST MODE.
	TF_PARACHUTE = (1 << 16), //PLAYER HAS DEPLOYED THE BASE JUMPER.
	BLASTJUMPING = (1 << 17), //PLAYER HAS STICKY OR ROCKET JUMPED.

	MINICRITS = (BUFFED | CRITCOLA),
	IGNORESTATES = (UBERCHARGED | BONKED),
	IGNORESTATES_PYRO = (PYROHEAL)
};

enum classes
{
	SCOUT = 1,
	SOLDIER = 3,
	PYRO = 7,
	DEMOMAN = 4,
	HEAVY = 6,
	ENGINEER = 9,
	MEDIC = 5,
	SNIPER = 2,
	SPY = 8,
};

enum life_states
{
	ALIVE,
	DYING,
	DEAD,
	RESPAWNABLE,
	DISCARDBODY,
};

enum entity_flags : int
{
	GROUND = (1 << 0),
	DUCKING = (1 << 1),
	WATERJUMP = (1 << 2),
	ONTRAIN = (1 << 3),
	INRAIN = (1 << 4),
	FROZEN = (1 << 5),
	ATCONTROLS = (1 << 6),
	CLIENT = (1 << 7),
	FAKECLIENT = (1 << 8)
};

enum hitboxes
{
	HEAD,
	NECK,
	LOWER_NECK,
	PELVIS,
	BODY,
	THORAX,
	CHEST,
	UPPER_CHEST,
	RIGHT_THIGH,
	LEFT_THIGH,
	RIGHT_CALF,
	LEFT_CALF,
	RIGHT_FOOT,
	LEFT_FOOT,
	RIGHT_HAND,
	LEFT_HAND,
	RIGHT_UPPER_ARM,
	RIGHT_FOREARM,
	LEFT_UPPER_ARM,
	LEFT_FOREARM,
	MAX
};

enum surface_flags
{
	SURFACE = (1 << 0),
	WALKABLE = (1 << 1),
	BUILDABLE = (1 << 2),
	SURFPROP1 = (1 << 3),
	SURFPROP2 = (1 << 4),
};

enum trace_type
{
	EVERYTHING = 0,
	WORLD_ONLY,				// NOTE: This does *not* test static props!!!
	ENTITIES_ONLY,			// NOTE: This version will *not* test static props
	EVERYTHING_FILTER_PROPS,	// NOTE: This version will pass the IHandleEntity for props through the filter, unlike all other filters
};

enum class_ids
{
	CAI_BaseNPC = 0,
	CBaseAnimating = 1,
	CBaseAnimatingOverlay = 2,
	CBaseAttributableItem = 3,
	CBaseCombatCharacter = 4,
	CBaseCombatWeapon = 5,
	CBaseDoor = 6,
	CBaseEntity = 7,
	CBaseFlex = 8,
	CBaseGrenade = 9,
	CBaseObject = 10,
	CBaseObjectUpgrade = 11,
	CBaseParticleEntity = 12,
	CBasePlayer = 13,
	CBaseProjectile = 14,
	CBasePropDoor = 15,
	CBaseTeamObjectiveResource = 16,
	CBaseTempEntity = 17,
	CBaseViewModel = 18,
	CBeam = 19,
	CBoneFollower = 20,
	CBonusDuckPickup = 21,
	CBonusPack = 22,
	CBonusRoundLogic = 23,
	CBreakableProp = 24,
	CBreakableSurface = 25,
	CCaptureFlag = 26,
	CCaptureFlagReturnIcon = 27,
	CCaptureZone = 28,
	CColorCorrection = 29,
	CColorCorrectionVolume = 30,
	CCurrencyPack = 31,
	CDynamicLight = 32,
	CDynamicProp = 33,
	CEconEntity = 34,
	CEconWearable = 35,
	CEmbers = 36,
	CEntityDissolve = 37,
	CEntityFlame = 38,
	CEntityParticleTrail = 39,
	CEnvDetailController = 40,
	CEnvParticleScript = 41,
	CEnvProjectedTexture = 42,
	CEnvQuadraticBeam = 43,
	CEnvScreenEffect = 44,
	CEnvScreenOverlay = 45,
	CEnvTonemapController = 46,
	CEnvWind = 47,
	CEyeballBoss = 48,
	CFireSmoke = 49,
	CFireTrail = 50,
	CFish = 51,
	CFogController = 52,
	CFuncAreaPortalWindow = 55,
	CFuncConveyor = 56,
	CFuncForceField = 57,
	CFuncLadder = 58,
	CFuncMonitor = 59,
	CFuncOccluder = 60,
	CFuncPasstimeGoal = 61,
	CFuncReflectiveGlass = 62,
	CFuncRespawnRoom = 63,
	CFuncRespawnRoomVisualizer = 64,
	CFuncRotating = 65,
	CFuncSmokeVolume = 66,
	CFuncTrackTrain = 67,
	CFunc_Dust = 53,
	CFunc_LOD = 54,
	CGameRulesProxy = 68,
	CHalloweenGiftPickup = 69,
	CHalloweenPickup = 70,
	CHalloweenSoulPack = 71,
	CHandleTest = 72,
	CHeadlessHatman = 73,
	CHightower_TeleportVortex = 74,
	CInfoLadderDismount = 75,
	CInfoLightingRelative = 76,
	CInfoOverlayAccessor = 77,
	CLaserDot = 78,
	CLightGlow = 79,
	CMannVsMachineStats = 80,
	CMaterialModifyControl = 81,
	CMerasmus = 82,
	CMerasmusDancer = 83,
	CMonsterResource = 84,
	CObjectCartDispenser = 85,
	CObjectDispenser = 86,
	CObjectSapper = 87,
	CObjectSentrygun = 88,
	CObjectTeleporter = 89,
	CParticleFire = 90,
	CParticlePerformanceMonitor = 91,
	CParticleSystem = 92,
	CPasstimeBall = 93,
	CPasstimeGun = 94,
	CPhysBox = 95,
	CPhysBoxMultiplayer = 96,
	CPhysMagnet = 99,
	CPhysicsProp = 97,
	CPhysicsPropMultiplayer = 98,
	CPlasma = 100,
	CPlayerDestructionDispenser = 101,
	CPlayerResource = 102,
	CPointCamera = 103,
	CPointCommentaryNode = 104,
	CPoseController = 105,
	CPrecipitation = 106,
	CPropVehicleDriveable = 107,
	CRagdollManager = 108,
	CRagdollProp = 109,
	CRagdollPropAttached = 110,
	CRobotDispenser = 111,
	CRopeKeyframe = 112,
	CSceneEntity = 113,
	CShadowControl = 114,
	CSlideshowDisplay = 115,
	CSmokeStack = 116,
	CSniperDot = 117,
	CSpotlightEnd = 118,
	CSprite = 119,
	CSpriteOriented = 120,
	CSpriteTrail = 121,
	CSteamJet = 122,
	CSun = 123,
	CTEArmorRicochet = 128,
	CTEBSPDecal = 141,
	CTEBaseBeam = 129,
	CTEBeamEntPoint = 130,
	CTEBeamEnts = 131,
	CTEBeamFollow = 132,
	CTEBeamLaser = 133,
	CTEBeamPoints = 134,
	CTEBeamRing = 135,
	CTEBeamRingPoint = 136,
	CTEBeamSpline = 137,
	CTEBloodSprite = 138,
	CTEBloodStream = 139,
	CTEBreakModel = 140,
	CTEBubbleTrail = 143,
	CTEBubbles = 142,
	CTEClientProjectile = 144,
	CTEDecal = 145,
	CTEDust = 146,
	CTEDynamicLight = 147,
	CTEEffectDispatch = 148,
	CTEEnergySplash = 149,
	CTEExplosion = 150,
	CTEFireBullets = 151,
	CTEFizz = 152,
	CTEFootprintDecal = 153,
	CTEGaussExplosion = 154,
	CTEGlowSprite = 155,
	CTEImpact = 156,
	CTEKillPlayerAttachments = 157,
	CTELargeFunnel = 158,
	CTEMetalSparks = 160,
	CTEMuzzleFlash = 161,
	CTEParticleSystem = 162,
	CTEPhysicsProp = 163,
	CTEPlayerAnimEvent = 164,
	CTEPlayerDecal = 165,
	CTEProjectedDecal = 166,
	CTEShatterSurface = 167,
	CTEShowLine = 168,
	CTESmoke = 170,
	CTESparks = 171,
	CTESprite = 172,
	CTESpriteSpray = 173,
	CTETFBlood = 176,
	CTETFExplosion = 177,
	CTETFParticleEffect = 178,
	CTEWorldDecal = 179,
	CTFAmmoPack = 180,
	CTFBall_Ornament = 181,
	CTFBaseBoss = 182,
	CTFBaseProjectile = 183,
	CTFBaseRocket = 184,
	CTFBat = 185,
	CTFBat_Fish = 186,
	CTFBat_Giftwrap = 187,
	CTFBat_Wood = 188,
	CTFBonesaw = 189,
	CTFBotHintEngineerNest = 190,
	CTFBottle = 191,
	CTFBreakableMelee = 192,
	CTFBreakableSign = 193,
	CTFBuffItem = 194,
	CTFCannon = 195,
	CTFChargedSMG = 196,
	CTFCleaver = 197,
	CTFClub = 198,
	CTFCompoundBow = 199,
	CTFCrossbow = 200,
	CTFDRGPomson = 201,
	CTFDroppedWeapon = 202,
	CTFFireAxe = 203,
	CTFFists = 204,
	CTFFlameManager = 205,
	CTFFlameRocket = 206,
	CTFFlameThrower = 207,
	CTFFlareGun = 208,
	CTFFlareGun_Revenge = 209,
	CTFGameRulesProxy = 210,
	CTFGasManager = 211,
	CTFGenericBomb = 212,
	CTFGlow = 213,
	CTFGrapplingHook = 214,
	CTFGrenadeLauncher = 215,
	CTFGrenadePipebombProjectile = 216,
	CTFHalloweenMinigame = 217,
	CTFHalloweenMinigame_FallingPlatforms = 218,
	CTFHellZap = 219,
	CTFItem = 220,
	CTFJar = 221,
	CTFJarGas = 222,
	CTFJarMilk = 223,
	CTFKatana = 224,
	CTFKnife = 225,
	CTFLaserPointer = 226,
	CTFLunchBox = 227,
	CTFLunchBox_Drink = 228,
	CTFMechanicalArm = 229,
	CTFMedigunShield = 230,
	CTFMiniGame = 231,
	CTFMinigameLogic = 232,
	CTFMinigun = 233,
	CTFObjectiveResource = 234,
	CTFPEPBrawlerBlaster = 240,
	CTFParachute = 235,
	CTFParachute_Primary = 236,
	CTFParachute_Secondary = 237,
	CTFParticleCannon = 238,
	CTFPasstimeLogic = 239,
	CTFPipebombLauncher = 241,
	CTFPistol = 242,
	CTFPistol_Scout = 243,
	CTFPistol_ScoutPrimary = 244,
	CTFPistol_ScoutSecondary = 245,
	CTFPlayer = 246,
	CTFPlayerDestructionLogic = 247,
	CTFPlayerResource = 248,
	CTFPointManager = 249,
	CTFPowerupBottle = 250,
	CTFProjectile_Arrow = 251,
	CTFProjectile_BallOfFire = 252,
	CTFProjectile_Cleaver = 253,
	CTFProjectile_EnergyBall = 254,
	CTFProjectile_EnergyRing = 255,
	CTFProjectile_Flare = 256,
	CTFProjectile_GrapplingHook = 257,
	CTFProjectile_HealingBolt = 258,
	CTFProjectile_Jar = 259,
	CTFProjectile_JarGas = 260,
	CTFProjectile_JarMilk = 261,
	CTFProjectile_MechanicalArmOrb = 262,
	CTFProjectile_Rocket = 263,
	CTFProjectile_SentryRocket = 264,
	CTFProjectile_SpellBats = 265,
	CTFProjectile_SpellFireball = 266,
	CTFProjectile_SpellKartBats = 267,
	CTFProjectile_SpellKartOrb = 268,
	CTFProjectile_SpellLightningOrb = 269,
	CTFProjectile_SpellMeteorShower = 270,
	CTFProjectile_SpellMirv = 271,
	CTFProjectile_SpellPumpkin = 272,
	CTFProjectile_SpellSpawnBoss = 273,
	CTFProjectile_SpellSpawnHorde = 274,
	CTFProjectile_SpellSpawnZombie = 275,
	CTFProjectile_SpellTransposeTeleport = 276,
	CTFProjectile_Throwable = 277,
	CTFProjectile_ThrowableBreadMonster = 278,
	CTFProjectile_ThrowableBrick = 279,
	CTFProjectile_ThrowableRepel = 280,
	CTFPumpkinBomb = 281,
	CTFRagdoll = 282,
	CTFRaygun = 283,
	CTFReviveMarker = 284,
	CTFRevolver = 285,
	CTFRobotArm = 286,
	CTFRobotDestructionLogic = 290,
	CTFRobotDestruction_Robot = 287,
	CTFRobotDestruction_RobotGroup = 288,
	CTFRobotDestruction_RobotSpawn = 289,
	CTFRocketLauncher = 291,
	CTFRocketLauncher_AirStrike = 292,
	CTFRocketLauncher_DirectHit = 293,
	CTFRocketLauncher_Mortar = 294,
	CTFRocketPack = 295,
	CTFSMG = 305,
	CTFScatterGun = 296,
	CTFShotgun = 297,
	CTFShotgunBuildingRescue = 302,
	CTFShotgun_HWG = 298,
	CTFShotgun_Pyro = 299,
	CTFShotgun_Revenge = 300,
	CTFShotgun_Soldier = 301,
	CTFShovel = 303,
	CTFSlap = 304,
	CTFSniperRifle = 306,
	CTFSniperRifleClassic = 307,
	CTFSniperRifleDecap = 308,
	CTFSodaPopper = 309,
	CTFSpellBook = 310,
	CTFStickBomb = 311,
	CTFStunBall = 312,
	CTFSword = 313,
	CTFSyringeGun = 314,
	CTFTankBoss = 315,
	CTFTauntProp = 316,
	CTFTeam = 317,
	CTFThrowable = 318,
	CTFViewModel = 319,
	CTFWeaponBase = 320,
	CTFWeaponBaseGrenadeProj = 321,
	CTFWeaponBaseGun = 322,
	CTFWeaponBaseMelee = 323,
	CTFWeaponBaseMerasmusGrenade = 324,
	CTFWeaponBuilder = 325,
	CTFWeaponFlameBall = 326,
	CTFWeaponInvis = 327,
	CTFWeaponPDA = 328,
	CTFWeaponPDAExpansion_Dispenser = 332,
	CTFWeaponPDAExpansion_Teleporter = 333,
	CTFWeaponPDA_Engineer_Build = 329,
	CTFWeaponPDA_Engineer_Destroy = 330,
	CTFWeaponPDA_Spy = 331,
	CTFWeaponSapper = 334,
	CTFWearable = 335,
	CTFWearableCampaignItem = 336,
	CTFWearableDemoShield = 337,
	CTFWearableItem = 338,
	CTFWearableLevelableItem = 339,
	CTFWearableRazorback = 340,
	CTFWearableRobotArm = 341,
	CTFWearableVM = 342,
	CTFWrench = 343,
	CTeam = 124,
	CTeamRoundTimer = 126,
	CTeamTrainWatcher = 127,
	CTeamplayRoundBasedRulesProxy = 125,
	CTeleportVortex = 159,
	CTesla = 169,
	CTestTraceline = 175,
	CTest_ProxyToggle_Networkable = 174,
	CVGuiScreen = 344,
	CVoteController = 345,
	CWaterBullet = 346,
	CWaterLODControl = 347,
	CWeaponIFMBase = 348,
	CWeaponIFMBaseCamera = 349,
	CWeaponIFMSteadyCam = 350,
	CWeaponMedigun = 351,
	CWorld = 352,
	CZombie = 353,
	DustTrail = 354,
	MovieExplosion = 355,
	NextBotCombatCharacter = 356,
	ParticleSmokeGrenade = 357,
	RocketTrail = 358,
	SmokeTrail = 359,
	SporeExplosion = 360,
	SporeTrail = 361
};