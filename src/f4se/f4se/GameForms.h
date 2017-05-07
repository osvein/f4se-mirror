#pragma once

#include "f4se_common/Relocation.h"
#include "f4se/GameFormComponents.h"
#include "f4se/GameCustomization.h"
#include "f4se/GameUtilities.h"

class TESForm;
class TESNPC;
class BGSColorForm;
class BGSHeadPart;
class BSFile;

class ActorValueInfo;
class TESEffectShader;
class BGSProjectile;
class BGSPerk;
class BGSExplosion;
class BGSArtObject;
class TESImageSpaceModifier;
class TESObjectLIGH;
class BGSEncounterZone;
class BGSMusicType;

typedef TESForm* (* _LookupFormByID)(UInt32 id);
extern RelocAddr <_LookupFormByID> LookupFormByID;

/**** form types ***************************************************************
*	
*
*	Code	id	name
	NONE	0
	TES4	1
	GRUP	2
	GMST	3
	KYWD	4	BGSKeyword
	LCRT	5	BGSLocationRefType
	AACT	6	BGSAction
	TRNS	7
	CMPO	8
	TXST	9	BGSTextureSet
	MICN	10	BGSMenuIcon
	GLOB	11	TESGlobal
	DMGT	12
	CLAS	13	TESClass
	FACT	14	TESFaction
	HDPT	15	BGSHeadPart
	EYES	16	TESEyes
	RACE	17	TESRace
	SOUN	18	TESSound
	ASPC	19	BGSAcousticSpace
	SKIL	20
	MGEF	21	EffectSetting
	SCPT	22	Script
	LTEX	23	TESLandTexture
	ENCH	24	EnchantmentItem
	SPEL	25	SpellItem
	SCRL	26	ScrollItem
	ACTI	27	TESObjectACTI
	TACT	28	BGSTalkingActivator
	ARMO	29	TESObjectARMO
	BOOK	30	TESObjectBOOK
	CONT	31	TESObjectCONT
	DOOR	32	TESObjectDOOR
	INGR	33	IngredientItem
	LIGH	34	TESObjectLIGH
	MISC	35	TESObjectMISC
	STAT	36	TESObjectSTAT
	SCOL	37	BGSStaticCollection
	MSTT	38	BGSMovableStatic
	GRAS	39	TESGrass
	TREE	40	TESObjectTREE
	FLOR	41	TESFlora
	FURN	42	TESFurniture
	WEAP	43	TESObjectWEAP
	AMMO	44	TESAmmo
	NPC_	45	TESNPC
	LVLN	46	TESLevCharacter
	KEYM	47	TESKey
	ALCH	48	AlchemyItem
	IDLM	49	BGSIdleMarker
	NOTE	50	BGSNote
	PROJ	51	BGSProjectile
	HAZD	52	BGSHazard
	BNDS	53
	SLGM	54	TESSoulGem
	TERM	55	BGSTerminal
	LVLI	56	TESLevItem
	WTHR	57	TESWeather
	CLMT	58	TESClimate
	SPGD	59	BGSShaderParticleGeometryData
	RFCT	60	BGSReferenceEffect
	REGN	61	TESRegion
	NAVI	62	NavMeshInfoMap
	CELL	63	TESObjectCELL
	REFR	64	TESObjectREFR / Actor
	ACHR	65	Character / PlayerCharacter
	PMIS	66	MissileProjectile
	PARW	67	ArrowProjectile
	PGRE	68	GrenadeProjectile
	PBEA	69	BeamProjectile
	PFLA	70	FlameProjectile
	PCON	71	ConeProjectile
	PBAR	72	BarrierProjectile
	PHZD	73	Hazard
	WRLD	74	TESWorldSpace
	LAND	75	TESObjectLAND
	NAVM	76	NavMesh
	TLOD	77
	DIAL	78	TESTopic
	INFO	79	TESTopicInfo
	QUST	80	TESQuest
	IDLE	81	TESIdleForm
	PACK	82	TESPackage
	CSTY	83	TESCombatStyle
	LSCR	84	TESLoadScreen
	LVSP	85	TESLevSpell
	ANIO	86	TESObjectANIO
	WATR	87	TESWaterForm
	EFSH	88	TESEffectShader
	TOFT	89
	EXPL	90	BGSExplosion
	DEBR	91	BGSDebris
	IMGS	92	TESImageSpace
	IMAD	93	TESImageSpaceModifier
	FLST	94	BGSListForm
	PERK	95	BGSPerk
	BPTD	96	BGSBodyPartData
	ADDN	97	BGSAddonNode
	AVIF	98	ActorValueInfo
	CAMS	99	BGSCameraShot
	CPTH	100	BGSCameraPath
	VTYP	101	BGSVoiceType
	MATT	102	BGSMaterialType
	IPCT	103	BGSImpactData
	IPDS	104	BGSImpactDataSet
	ARMA	105	TESObjectARMA
	ECZN	106	BGSEncounterZone
	LCTN	107	BGSLocation
	MESG	108	BGSMessage
	RGDL	109	BGSRagdoll
	DOBJ	110
	DFOB	111
	LGTM	112	BGSLightingTemplate
	MUSC	113	BGSMusicType
	FSTP	114	BGSFootstep
	FSTS	115	BGSFootstepSet
	SMBN	116	BGSStoryManagerBranchNode
	SMQN	117	BGSStoryManagerQuestNode
	SMEN	118	BGSStoryManagerEventNode
	DLBR	119	BGSDialogueBranch
	MUST	120	BGSMusicTrackFormWrapper
	DLVW	121
	WOOP	122	TESWordOfPower
	SHOU	123	TESShout
	EQUP	124	BGSEquipSlot
	RELA	125	BGSRelationship
	SCEN	126	BGSScene
	ASTP	127	BGSAssociationType
	OTFT	128	BGSOutfit
	ARTO	129	BGSArtObject
	MATO	130	BGSMaterialObject
	MOVT	131	BGSMovementType
	SNDR	132	BGSSoundDescriptorForm
	DUAL	133	BGSDualCastData
	SNCT	134	BGSSoundCategory
	SOPM	135	BGSSoundOutput
	COLL	136	BGSCollisionLayer
	CLFM	137	BGSColorForm
	REVB	138	BGSReverbParameters
	PKIN	139
	RFGP	140
	AMDL	141
	LAYR	142
	COBJ	143
	OMOD	144 BGSMod::Attachment::Mod
	MSWP	145 BGSMaterialSwap
	ZOOM	146
	INNR	147
	KSSM	148
	AECH	149
	SCCO	150
	AORU	151
	SCSN	152
	STAG	153
	NOCM	154
	LENS	155
	LSPR	156
	GDRY	157
	OVIS	158

	// Special types
	160
	161
	162
	163
	164
	165
*/

enum FormType
{
	kFormType_NONE = 0,
	kFormType_TES4,
	kFormType_GRUP,
	kFormType_GMST,
	kFormType_KYWD,
	kFormType_LCRT,
	kFormType_AACT,
	kFormType_TRNS,
	kFormType_CMPO,
	kFormType_TXST,
	kFormType_MICN,
	kFormType_GLOB,
	kFormType_DMGT,
	kFormType_CLAS,
	kFormType_FACT,
	kFormType_HDPT,
	kFormType_EYES,
	kFormType_RACE,
	kFormType_SOUN,
	kFormType_ASPC,
	kFormType_SKIL,
	kFormType_MGEF,
	kFormType_SCPT,
	kFormType_LTEX,
	kFormType_ENCH,
	kFormType_SPEL,
	kFormType_SCRL,
	kFormType_ACTI,
	kFormType_TACT,
	kFormType_ARMO,
	kFormType_BOOK,
	kFormType_CONT,
	kFormType_DOOR,
	kFormType_INGR,
	kFormType_LIGH,
	kFormType_MISC,
	kFormType_STAT,
	kFormType_SCOL,
	kFormType_MSTT,
	kFormType_GRAS,
	kFormType_TREE,
	kFormType_FLOR,
	kFormType_FURN,
	kFormType_WEAP,
	kFormType_AMMO,
	kFormType_NPC_,
	kFormType_LVLN,
	kFormType_KEYM,
	kFormType_ALCH,
	kFormType_IDLM,
	kFormType_NOTE,
	kFormType_PROJ,
	kFormType_HAZD,
	kFormType_BNDS,
	kFormType_SLGM,
	kFormType_TERM,
	kFormType_LVLI,
	kFormType_WTHR,
	kFormType_CLMT,
	kFormType_SPGD,
	kFormType_RFCT,
	kFormType_REGN,
	kFormType_NAVI,
	kFormType_CELL,
	kFormType_REFR,
	kFormType_ACHR,
	kFormType_PMIS,
	kFormType_PARW,
	kFormType_PGRE,
	kFormType_PBEA,
	kFormType_PFLA,
	kFormType_PCON,
	kFormType_PBAR,
	kFormType_PHZD,
	kFormType_WRLD,
	kFormType_LAND,
	kFormType_NAVM,
	kFormType_TLOD,
	kFormType_DIAL,
	kFormType_INFO,
	kFormType_QUST,
	kFormType_IDLE,
	kFormType_PACK,
	kFormType_CSTY,
	kFormType_LSCR,
	kFormType_LVSP,
	kFormType_ANIO,
	kFormType_WATR,
	kFormType_EFSH,
	kFormType_TOFT,
	kFormType_EXPL,
	kFormType_DEBR,
	kFormType_IMGS,
	kFormType_IMAD,
	kFormType_FLST,
	kFormType_PERK,
	kFormType_BPTD,
	kFormType_ADDN,
	kFormType_AVIF,
	kFormType_CAMS,
	kFormType_CPTH,
	kFormType_VTYP,
	kFormType_MATT,
	kFormType_IPCT,
	kFormType_IPDS,
	kFormType_ARMA,
	kFormType_ECZN,
	kFormType_LCTN,
	kFormType_MESG,
	kFormType_RGDL,
	kFormType_DOBJ,
	kFormType_DFOB,
	kFormType_LGTM,
	kFormType_MUSC,
	kFormType_FSTP,
	kFormType_FSTS,
	kFormType_SMBN,
	kFormType_SMQN,
	kFormType_SMEN,
	kFormType_DLBR,
	kFormType_MUST,
	kFormType_DLVW,
	kFormType_WOOP,
	kFormType_SHOU,
	kFormType_EQUP,
	kFormType_RELA,
	kFormType_SCEN,
	kFormType_ASTP,
	kFormType_OTFT,
	kFormType_ARTO,
	kFormType_MATO,
	kFormType_MOVT,
	kFormType_SNDR,
	kFormType_DUAL,
	kFormType_SNCT,
	kFormType_SOPM,
	kFormType_COLL,
	kFormType_CLFM,
	kFormType_REVB,
	kFormType_PKIN,
	kFormType_RFGP,
	kFormType_AMDL,
	kFormType_LAYR,
	kFormType_COBJ,
	kFormType_OMOD,
	kFormType_MSWP,
	kFormType_ZOOM,
	kFormType_INNR,
	kFormType_KSSM,
	kFormType_AECH,
	kFormType_SCCO,
	kFormType_AORU,
	kFormType_SCSN,
	kFormType_STAG,
	kFormType_NOCM,
	kFormType_LENS,
	kFormType_LSPR,
	kFormType_GDRY,
	kFormType_OVIS
};

// 20
class TESForm : public BaseFormComponent
{
public:
	enum { kTypeID = 0 };	// special-case

	virtual void	Unk_07();
	virtual void	Unk_08();
	virtual void	Unk_09();
	virtual void	Unk_0A();
	virtual void	Unk_0B();
	virtual void	Unk_0C();
	virtual bool	MarkChanged(UInt64 changed);
	virtual void	Unk_0E();
	virtual void	Unk_0F();
	virtual void	Unk_10();
	virtual void	Unk_11();
	virtual void	Unk_12();
	virtual void	Unk_13();
	virtual void	Unk_14();
	virtual void	Unk_15();
	virtual void	Unk_16();
	virtual void	Unk_17();
	virtual void	Unk_18();
	virtual void	Unk_19();
	virtual void	Unk_1A();
	virtual void	Unk_1B();
	virtual void	Unk_1C();
	virtual void	Unk_1D();
	virtual void	Unk_1E();
	virtual void	Unk_1F();
	virtual void	Unk_20();
	virtual void	Unk_21();
	virtual void	Unk_22();
	virtual void	Unk_23();
	virtual void	Unk_24();
	virtual void	Unk_25();
	virtual void	Unk_26();
	virtual void	Unk_27();
	virtual void	Unk_28();
	virtual void	Unk_29();
	virtual void	Unk_2A();
	virtual void	Unk_2B();
	virtual void	Unk_2C();
	virtual void	Unk_2D();
	virtual void	Unk_2E();
	virtual void	Unk_2F();
	virtual void	Unk_30();
	virtual void	Unk_31();
	virtual void	Unk_32();
	virtual void	Unk_33();
	virtual void	Unk_34();
	virtual void	Unk_35();
	virtual void	Unk_36();
	virtual void	Unk_37();
	virtual void	Unk_38();
	virtual const char *	GetEditorID(); // Only returns string for things that actually store the EDID ingame
	virtual void	Unk_3A();
	virtual void	Unk_3B();
	virtual void	Unk_3C();
	virtual void	Unk_3D();
	virtual void	Unk_3E();
	virtual void	Unk_3F();
	virtual void	Unk_40();
	virtual void	Unk_41();
	virtual void	Unk_42();
	virtual void	Unk_43();
	virtual void	Unk_44();
	virtual void	Unk_45();
	virtual void	Unk_46();
	virtual void	Unk_47();

	struct Data
	{
		struct Entry
		{
			UInt64	unk00[0x50/8];
			BSFile	* file;	// 50
			UInt64	unk58[(0x330-0x58)/8];
			UInt32	unk330;	// 330
			UInt32	unk334; // 334 (unk334 & 1) == 1 // Load external head?
			// ...
		};
		Entry ** entries;
		UInt64	size;
	};

	Data	* unk08;	// 08
	UInt32	flags;		// 10
	UInt32	formID;		// 14
	UInt16	unk18;		// 18
	UInt8	formType;	// 1A
	UInt8	unk1B;		// 1B
	UInt8	pad1C[4];	// 1C
};

// 118
class BGSInstanceNamingRules : public TESForm
{
public:
	// 30
	struct KeywordData
	{
		void			* unk00;		// 00
		BGSKeywordForm	keywordForm;	// 08
		UInt64			unk28;			// 28
	};
	UInt64				unk20;	// 20
	tArray<KeywordData>	unk28;	// 28
	tArray<KeywordData>	unk40;	// 40
	tArray<KeywordData> unk58;	// 58
	tArray<KeywordData>	unk70;	// 70
	tArray<KeywordData>	unk88;	// 88
	UInt64	unkA0[(0x118 - 0xA0) / 8];	// A0
};
STATIC_ASSERT(offsetof(BGSInstanceNamingRules, unk88) == 0x88);
STATIC_ASSERT(sizeof(BGSInstanceNamingRules) == 0x118);

class BGSKeyword : public TESForm
{
public:
	enum { kTypeID = kFormType_KYWD };

	BSFixedString	keyword;	// 020
};

// 30
class BGSSoundDescriptorForm : public TESForm
{
public:
	enum { kTypeID = kFormType_SNDR };

	BGSSoundDescriptor	soundDescriptor;	// 20
	UInt64	unk28;							// 28
};

class BGSAction : public BGSKeyword
{
public:
	enum { kTypeID = kFormType_AACT };

	UInt64			unk28; // maybe index or id?
//Actions dump 1.1.30:
// unk28					Keyword
// -----                    --------
//  0                      ActionTrick
//  1                  ActionFireEmpty
//  2               ActionWeaponHotkey
//  3                ActionFlinchStart
//  4                ActionPerkSandman
//  5               ActionPerkCannibal
//  6                   ActionGunAlert
//  7                       ActionHide
//  8           ActionCameraBToCameraA
//  9           ActionCameraAToCameraB
// 10                   ActionSwimStop
// 11                  ActionSwimStart
// 12    ActionAvailableCondition1Heal
// 13               ActionRightArmHeal
// 14                ActionLeftArmHeal
// 15         ActionInstantAttackReset
// 16                ActionJetpackStop
// 17               ActionJetpackStart
// 18            ActionUnconsciousExit
// 19           ActionUnconsciousEnter
// 20             ActionFireChargeHold
// 21             ActionCustomLaughing
// 22               ActionPropellersOn
// 23              ActionPropellersOff
// 24               ActionCustomBooing
// 25             ActionCustomCheering
// 26                   ActionGunReady
// 27               ActionDeferredKill
// 28          ActionNonSupportContact
// 29                       ActionBark
// 30   ActionEnterDialogueCameraState
// 31             ActionGunChargeStart
// 32                ActionIdlePlayful
// 33           ActionChangeAnimFlavor
// 34        ActionChangeAnimArchetype
// 35                 ActionBoltCharge
// 36               ActionAttackMissed
// 37                     ActionTunnel
// 38         ActionInteractionExitAlt
// 39             ActionLeadingArrival
// 40        ActionLeadingArrivalEmote
// 41           ActionLeadingDoneEmote
// 42           ActionLeadingDeparture
// 43                 ActionEscortWait
// 44                 ActionIdleFlavor
// 45 ActionInstantInitializeGraphToBaseState
// 46                   ActionLegsHeal
// 47                      ActionPanic
// 48                      ActionCower
// 49                  ActionAOEAttack
// 50              ActionPipboyInspect
// 51                    ActionShuffle
// 52                      ActionDodge
// 53                      ActionEvade
// 54               ActionStumbleStart
// 55                 ActionGunRelaxed
// 56                   ActionTurnStop
// 57                   ActionTurnLeft
// 58                  ActionTurnRight
// 59                   ActionMoveStop
// 60                  ActionMoveStart
// 61                       ActionLand
// 62                       ActionFall
// 63         ActionLargeMovementDelta
// 64                  ActionDeathWait
// 65                ActionDualRelease
// 66                 ActionDualAttack
// 67                 ActionStopEffect
// 68                     ActionListen
// 69                    ActionTalking
// 70                      ActionDeath
// 71              ActionSummonedStart
// 72                 ActionBumpedInto
// 73                  ActionHoverStop
// 74                 ActionHoverStart
// 75                    ActionFlyStop
// 76                   ActionFlyStart
// 77                ActionSprintStart
// 78                    ActionPathEnd
// 79                  ActionPathStart
// 80                 ActionForceEquip
// 81            ActionBlockAnticipate
// 82                   ActionIdleStop
// 83               ActionBleedoutStop
// 84              ActionBleedoutStart
// 85                ActionRecoilLarge
// 86                     ActionRecoil
// 87                   ActionBlockHit
// 88               ActionStaggerStart
// 89             ActionVoiceInterrupt
// 90                 ActionVoiceReady
// 91               ActionVoiceRelease
// 92             ActionRightInterrupt
// 93                 ActionRightReady
// 94               ActionRightRelease
// 95              ActionLeftInterrupt
// 96                  ActionLeftReady
// 97                ActionLeftRelease
// 98           ActionRightPowerAttack
// 99                       ActionDraw
//100                 ActionSprintStop
//101                       ActionLook
//102                   ActionActivate
//103                      ActionVoice
//104                      ActionSneak
//105                       ActionJump
//106                ActionRightAttack
//107                 ActionLeftAttack
//108            ActionSwimStateChange
//109                       ActionIdle
//110                    ActionWardHit
//111                  ActionPipboyTab
//112                  ActionPipboyMap
//113            ActionPipboyInventory
//114                 ActionPipboyData
//115                ActionPipboyStats
//116                 ActionPipboyZoom
//117                  ActionExitCover
//118                 ActionEnterCover
//119                 ActionPipboyOpen
//120                      ActionThrow
//121                   ActionFireAuto
//122                 ActionFireCharge
//123                 ActionFireSingle
//124                      ActionMelee
//125             ActionSightedRelease
//126                    ActionSighted
//127                     ActionReload
//128             ActionRagdollInstant
//129            ActionIdleStopInstant
//130                     ActionSheath
//131                      ActionGetUp
//132                  ActionKnockDown
//133               ActionShieldChange
//134                  ActionMoveRight
//135                   ActionMoveLeft
//136               ActionMoveBackward
//137                ActionMoveForward
//138            ActionDualPowerAttack
//139            ActionLeftPowerAttack
//140                   ActionIdleWarn
//141                    ActionGunDown
//142              ActionListenNeutral
//143             ActionListenQuestion
//144             ActionListenNegative
//145             ActionListenPositive
//146                 ActionIntimidate
//147           ActionInteractionEnter
//148    ActionInteractionEnterInstant
//149            ActionInteractionExit
//150       ActionInteractionExitQuick
//151                ActionPipboyClose
//152             ActionPipboyRadioOff
//153              ActionPipboyRadioOn
//154               ActionPipboySelect
//155          ActionPipboyTabPrevious
//156           ActionCoverSprintStart
//157         ActionActivateLoopingEnd
//158                     ActionMantle
//159             ActionLeftSyncAttack
//160            ActionRightSyncAttack
//161                  ActionFlipThrow
//162               ActionDialogueExit
//163              ActionDialogueEnter
//164         ActionPipboyLoadHolotape
//165               ActionLimbCritical
//166                 ActionCombatExit
//167                ActionCombatEnter
//168       ActionActivateLoopingBegin
//169              ActionFurnitureFull
//170 ActionInitializeGraphToBaseState
//171      ActionFurnitureNoLongerFull
//172               ActionLegsCritical
};

// 190
class ActorValueInfo : public TESForm
{
public:
	TESFullName			fullName;		// 20
	TESDescription		description;	// 30

	void	* func_impl;	// 48
	void	* func;			// 50
	void	* unk58;		// 58
	void	* func_ptr;		// 60 - address of offset 48
	const char * avName;	// 68

	UInt64	unk70[(0x190-0x70)/8];	// 70
};

// 80
class BGSMaterialType : public TESForm
{
public:
	enum { kTypeID = kFormType_MATT };

	UInt64	unk20[(0x80-0x20)/8];	// 20
};

// 38
class BGSColorForm : public TESForm
{
public:
	enum { kTypeID = kFormType_CLFM };

	TESFullName			fullName;		// 20
	union
	{
		struct
		{
			UInt8 r;
			UInt8 g;
			UInt8 b;
			UInt8 unknown;
		} channels;
		UInt32	rgb;
	} color;

	enum Flags
	{
		kFlags_Playable = 1,
		kFlags_HairColor = 2
	};
	UInt32				flags;			// 30
};

// 6C8
class TESRace : public TESForm
{
public:
	enum { kTypeID = kFormType_RACE };

	TESFullName			fullName;		// 20
	TESDescription		description;	// 30
	TESSpellList		spellList;		// 48
	BGSSkinForm			skinForm;		// 58
	BGSBipedObjectForm	bipedObjects;	// 68
	BGSKeywordForm		keywordForm;	// 78
	BGSAttackDataForm	attackDataForm;	// 98
	BGSPropertySheet	propertySheet;	// A8
	BGSPreloadable		preloadable;	// B8

	TESModel			models[2];		 // C0
	TESModel			unk120[2];		 // 120
	UInt64				unk170[(0x288-0x180)/8]; // 180
	BGSTextureModel		textureModel[2]; // 288
	BGSBehaviorGraphModel behaviorGraph[2]; // 2E8
	BSFixedString		unk348[2]; // 348
	BSFixedString		unk358[2]; // 358
	BGSVoiceType		* voiceType[2];	// 368
	BGSBodyPartData		* bodyPartData;	// 378
	BGSSoundTagComponent	unk380;	// 380
	BGSAttachParentArray	unk388;	// 388
	BSFixedString		editorId; // 3A0
	BGSMaterialType		* materialType;	// 3A8
	void				* unk3B0;		// 3B0
	BGSTextureSet		* textureSets[2];	// 3B8
	BGSSoundDescriptorForm * soundDescriptors[2]; // 3C8
	BSFixedString		bipedObjectNames[0x20]; // 3D8

	// 48+
	struct CharGenData
	{
		tArray<CharacterCreation::TintData*>		* tintData;			// 00
		tArray<BGSTextureSet*>						* textureSets;		// 08
		BGSTextureSet								* defaultTexture;	// 10
		tArray<TESNPC*>								* presets;			// 18
		tArray<BGSColorForm*>						* colors;			// 20
		BGSColorForm								* defaultColor;		// 28
		tArray<BGSHeadPart*>						* headParts;		// 30
		tArray<CharacterCreation::MorphGroup*>		* morphGroups;		// 38
		tArray<CharacterCreation::FaceMorphRegion*>	* faceMorphs;		// 40

		BGSCharacterTint::Template::Entry * GetTemplateByIndex(UInt16 index);
	};

	// 10
	template<int T>
	struct BoneScale // (BSMB/BSMS) pair
	{
		BSFixedString	bone;		// 00
		float			* value;	// 08

		bool operator==(const BSFixedString a_key) const	{ return bone.data == a_key.data; }
		static inline UInt32 GetHash(const BSFixedString * key)
		{
			UInt32 hash;
			CalculateCRC32_64(&hash, (UInt64)key->data->Get<char>(), 0);
			return hash;
		}

		void Dump(void)
		{
			_MESSAGE("\t\tkey: %s", bone.data ? bone.data->Get<char>() : "");
			for(UInt32 i = 0; i < T; i++)
				_MESSAGE("\t\tdata: %f", value[i]);
		}
	};

	struct MorphSlider
	{
		UInt32	key;		// 00
		UInt32	pad04;		// 04

		struct Morphs
		{
			BSFixedString lower;	// 00
			BSFixedString upper;	// 08
		};
		Morphs * morphs;	// 08

		bool operator==(const UInt32 a_key) const	{ return key == a_key; }
		static inline UInt32 GetHash(const UInt32 * key)
		{
			UInt32 hash;
			CalculateCRC32_32(&hash, *key, 0);
			return hash;
		}

		void Dump(void)
		{
			_MESSAGE("\t\tkey: %08X", key);
			if(morphs)
			{
				_MESSAGE("\t\tLower: %s", morphs->lower.data->Get<char>());
				_MESSAGE("\t\tUpper: %s", morphs->upper.data->Get<char>());
			}
		}
	};

	struct BoneScaleMap
	{
		tHashSet<BoneScale<8>, BSFixedString>	weightMap1;	// value array length 8
		tHashSet<BoneScale<4>, BSFixedString>	weightMap2;	// value array length 4
	};

	UInt64				unk4C0[(0x648-0x4D8)/8];	// 4D8 - 654, 670, 660 table?
	tHashSet<MorphSlider, UInt32> morphSliders;		// 648
	UInt64				unk678[(0x698-0x678)/8];	// 678
	CharGenData			* chargenData[2];			// 698
	BoneScaleMap		* boneScaleMap[2];			// 6A8
	TESTexture			unk6B8;						// 6B8
};

STATIC_ASSERT(offsetof(TESRace, chargenData) == 0x698);
STATIC_ASSERT(sizeof(TESRace) == 0x6C8);

// 48
class BGSListForm : public TESForm
{
public:
	enum { kTypeID = kFormType_FLST };

	tArray<TESForm*>	forms;		// 20
	UInt64				unk38;		// 38
	UInt64				unk40;		// 40
};
STATIC_ASSERT(sizeof(BGSListForm) == 0x48);

// 178
class BGSHeadPart : public TESForm
{
public:
	enum { kTypeID = kFormType_HDPT };

	TESFullName				fullName;		// 20
	BGSModelMaterialSwap	materialSwap;	// 30

	enum 
	{
		kFlagPlayable	= 1 << 0,
		kFlagMale		= 1 << 1,
		kFlagFemale		= 1 << 2,
		kFlagExtraPart	= 1 << 3,
		kFlagSolidTint	= 1 << 4,
		kFlagUnk1		= 1 << 5 // only appears on Head Rear types
	};
	UInt32					partFlags;		// 70

	enum {
		kTypeMisc = 0,
		kTypeFace,
		kTypeEyes,
		kTypeHair,
		kTypeFacialHair,
		kTypeScar,
		kTypeBrows,
		kType7,
		kType8,
		kTypeHeadRear,
		kNumTypes
	};
	UInt32					type;			// 74

	tArray<BGSHeadPart*>	extraParts;		// 78
	BGSTextureSet			* textureSet;	// 90
	TESModel				model;			// 98
	TESModelTri				morphs[3];		// C8
	UInt64					unk158;			// 158
	BGSListForm				* validRaces;	// 160
	Condition				* conditions;	// 168 - Condition most likely
	BSFixedString			partName;		// 170

	bool IsExtraPart() { return (partFlags & kFlagExtraPart) == kFlagExtraPart; }
};

// 1B0
class EffectSetting : public TESForm
{
public:
	enum { kTypeID = kFormType_MGEF };

	TESFullName				fullName;		// 20
	BGSMenuDisplayObject	menuObject;		// 30
	BGSKeywordForm			keywordForm;	// 40
	UInt64					unk060[2]; // 60
	UInt32					unk070; // 70
	float					unk074;
	TESForm*				unk078;	// primary object? (SpellItem, TESObjectLIGH, BGSDamageType, BGSHazard)
	UInt64					unk080;
	ActorValueInfo*			actorValInfo88; // 088
	UInt8					unk090;
	UInt8					pad092[3];
	TESObjectLIGH*			light98;
	float					unkA0;
	UInt32					padA4;
	TESEffectShader*		effectShaderA8;
	UInt64					unkB0;
	UInt64					unkB8;
	float					unkC0;
	float					unkC4;
	float					unkC8;
	float					unkCC;
	UInt32					unk0D0; 
	UInt32					pad0D4;
	ActorValueInfo*			actorValInfoD8;
	BGSProjectile*			projectileE0;
	BGSExplosion*			explosionE8;
	UInt32					unkF0; // init to 3 cast type?
	UInt32					unkF4; // init to 5 delivery type?
	ActorValueInfo*			actorValInfoF8;
	UInt64					unk100;
	BGSArtObject*			art108;
	BGSImpactDataSet*		impact110;
	UInt32					unk118;
	UInt32					pad11C;
	UInt64					unk120;
	float					unk128; // initialized to  3F800000 dual casting scale?
	UInt32					pad12C;
	UInt64					unk130[4];
	TESImageSpaceModifier*	spaceModifier150; // 150
	BGSPerk*				perk158;
	UInt64					unk160;	// initialized to 1		
	UInt64					unk168[3];
	UInt64					unk180;
	UInt32					unk188;
	UInt32					unk18C;
	UInt64					unk190;
	void*					unk198;	// pointer to something
	UInt64					unk1A0;
	void*					unk1A8;
};
STATIC_ASSERT(offsetof(EffectSetting, unk160) == 0x160);
STATIC_ASSERT(sizeof(EffectSetting) == 0x1B0);

// 50
// MSWP
class BGSMaterialSwap : public TESForm
{
public:
	enum { kTypeID = kFormType_MSWP };
							// 20
	UInt32					unk20;
	UInt32					unk24;
	UInt32					unk28;
	UInt32					unk2C;	// strange - written to in ctor as UInt64 as 0, but can't line up that way
	UInt32					unk30;
	UInt32					unk34;
	UInt64					unk38; // init to a char[5]
	UInt64					unk40;
	UInt64					unk48;
};
STATIC_ASSERT(offsetof(BGSMaterialSwap, unk38) == 0x38);
STATIC_ASSERT(sizeof(BGSMaterialSwap) == 0x50);

class BGSMod
{
public:
	class Container
	{
	public:

	};

	class Template
	{
	public:
		// 20
		class Items : public BaseFormComponent
		{
		public:
			virtual ~Items();

			virtual void	Unk_07(void);
			virtual void	Unk_08(void);

			void	* unk08;	// 08
			void	* unk10;	// 10
			void	* unk18;	// 18
		};

		// 38
		class Item : public TESFullName
		{
		public:
			virtual ~Item();

			virtual void	Unk_07(void);
			virtual void	Unk_08(void);

			void	* unk08;	// 08
			void	* unk10;	// 10
			UInt32	unk18;		// 18
			UInt32	unk1C;		// 1C
			void	* unk20;		// 20
			UInt64	unk28;		// 28
			UInt32	unk30;		// 30
			UInt8	unk34[4];	// 34
		};
	};

	class Attachment {
	public:
		// C8
		class Mod : public TESForm
		{
		public:
			enum { kTypeID = kFormType_OMOD };

			TESFullName									fullName;	// 20
			TESDescription								description; // 30
			BGSModelMaterialSwap						materialSwap; // 48
			BGSMod::Container							modContainer; // 88
			//BSTDataBuffer<2, BSDataBufferHeapAllocator> dataBuffer;
			UInt64										unk90;			// 90
			BGSAttachParentArray						unk98;			// 98
			UInt64										unkB0;			// B0
			UInt64										unkB8;			// B8
			UInt64										unkC0;			// C0
		};
	};
};
STATIC_ASSERT(offsetof(BGSMod::Attachment::Mod, modContainer) == 0x88);
STATIC_ASSERT(sizeof(BGSMod::Attachment::Mod) == 0xC8);

// 48
class BGSTransform : public TESForm
{
public:
	enum { kTypeID = kFormType_TRNS };

	float				matrix[9];
	UInt32				pad44;
};
STATIC_ASSERT(offsetof(BGSTransform, pad44) == 0x44);
STATIC_ASSERT(sizeof(BGSTransform) == 0x48);

class BGSOpenCloseForm
{
public:
	//	void	** _vtbl;	// 00
};

class TESMagicTargetForm
{
public:
};

class TESMagicCasterForm
{
public:
};


class BGSLocationRefType : public BGSKeyword
{
public:
	enum { kTypeID = kFormType_LCRT };
};


// 140
class BGSLocation : public TESForm
{
public:
	enum { kTypeID = kFormType_LCTN };

	TESFullName				fullName;		// 020
	BGSKeywordForm			keywordForm;	// 030

	BGSLocation*			location50;		// 050
	UInt64					unk58;
	BGSMusicType*			music60;		// 060 
	BGSEncounterZone*		encounterZone68;// 068 
	UInt32					unk70;
	float					unk74;
	float					unk78;	// init to 1.0
	UInt32					unk7C;

	struct arr80Data {
		BGSLocationRefType*	refType0;
		UInt64	unk8;
		UInt64	unk10;
	};
	tArray<arr80Data>	arr80;
	//UInt64					unk80;	// maybe tArray<>
	//UInt32					unk88;
	//UInt32					unk8C;
	//UInt64					unk90;
	UnkArray				arr98;
	//UInt64					unk98;
	//UInt32					unkA0;
	//UInt32					unkA4;
	//UInt32					unkA8;
	//UInt32					unkAC;
	UInt64					unkB0;
	UInt64					unkB8;
	UInt32					unkC0;
	UInt32					unkC4;
	UInt32					unkC8;
	UInt32					unkCC;
	UInt64					unkD0;
	UInt32					unkD8;
	float					unkDC;
	UInt32					unkE0;
	UInt32					unkE4;
	UInt64					unkE8;
	UInt64					unkF0;
	UInt32					unkF8;
	float					unkFC;
	UInt32					unk100;
	UInt32					unk104;
	UInt32					unk108;
	float					unk10C;
	UInt64					unk110;
	UInt32					unk118;
	float					unk11C;
	UInt32					unk120;
	UInt32					unk124;
	UInt32					unk128;
	UInt32					unk12C;
	UInt32					unk130;
	UInt32					unk134;
	UInt32					unk138;
	UInt32					unk13C;
};
STATIC_ASSERT(offsetof(BGSLocation, unkFC) == 0xFC);
STATIC_ASSERT(sizeof(BGSLocation) == 0x140);

// 48
class BGSEncounterZone : public TESForm
{
public:
	enum { kTypeID = kFormType_ECZN };

	UInt64					unk20;		// 20
	BGSLocation*			location;	// 28
	UInt64					unk30;		// 30
	UInt64					unk38;		// 38
	UInt64					unk40;		// 40
};

// 38
class BGSOutfit : public TESForm
{
public:
	tArray<TESForm*>	forms;	// 20
};
