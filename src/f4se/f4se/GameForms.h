#pragma once

#include "f4se/GameFormComponents.h"
#include "f4se_common/Relocation.h"

class TESForm;

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
	TERM	55
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
	OMOD	144
	MSWP	145
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
*/



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
	virtual void	Unk_0D();
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
	virtual void	Unk_39();
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

	void	* unk08;	// 08
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
	BSFixedString	keyword;	// 020
};

class BGSAction : public BGSKeyword
{
public:
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
