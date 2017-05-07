#pragma once

#include "f4se/GameForms.h"
#include "f4se/GameEvents.h"
#include "f4se/GameCustomization.h"
#include "f4se/NiObjects.h"

class BSActiveGraphIfInactiveEvent;
class BSAnimationGraphEvent;

class TESObjectCELL;
class NiNode;
class ExtraDataList;

typedef bool (* _CreateHandleByREFR)(UInt32 * handle, TESObjectREFR * ref);
extern RelocAddr <_CreateHandleByREFR> CreateHandleByREFR;

typedef bool (* _LookupREFRByHandle)(UInt32 * handle, TESObjectREFR ** ref);
extern RelocAddr <_LookupREFRByHandle> LookupREFRByHandle;

extern RelocPtr <UInt32> g_invalidRefHandle;

typedef bool (* _HasDetectionLOS)(Actor* source, TESObjectREFR* target, UInt8 * unk1);
extern RelocAddr<_HasDetectionLOS> HasDetectionLOS;

// 10
class BSHandleRefObject : public NiRefObject
{
public:
	enum
	{
		kMask_RefCount = 0x3FF
	};

	UInt32 GetRefCount() const
	{
		return m_uiRefCount & kMask_RefCount;
	}

	void DecRefHandle()
	{
		if((InterlockedDecrement(&m_uiRefCount) & kMask_RefCount) == 0)
			DeleteThis();
	}
};

// 110
class TESObjectREFR : public TESForm
{
public:
	virtual void	Unk_48();
	virtual void	Unk_49();
	virtual void	Unk_4A();
	virtual void	Unk_4B();
	virtual void	Unk_4C();
	virtual void	Unk_4D();
	virtual void	Unk_4E();
	virtual void	Unk_4F();
	virtual void	Unk_50();
	virtual void	Unk_51();
	virtual void	Unk_52();
	virtual void	Unk_53();
	virtual void	Unk_54();
	virtual void	Unk_55();
	virtual void	Unk_56();
	virtual void	Unk_57();
	virtual void	Unk_58();
	virtual void	Unk_59();
	virtual void	Unk_5A();
	virtual void	Unk_5B();
	virtual void	Unk_5C();
	virtual void	Unk_5D();
	virtual void	Unk_5E();
	virtual void	Unk_5F();
	virtual void	Unk_60();
	virtual void	Unk_61();
	virtual void	Unk_62();
	virtual void	Unk_63();
	virtual void	Unk_64();
	virtual void	Unk_65();
	virtual void	Unk_66();
	virtual void	Unk_67();
	virtual void	Unk_68();
	virtual void	Unk_69();
	virtual void	Unk_6A();
	virtual void	Unk_6B();
	virtual void	Unk_6C();
	virtual void	Unk_6D();
	virtual void	Unk_6E();
	virtual void	Unk_6F();
	virtual void	Unk_70();
	virtual void	Unk_71();
	virtual void	Unk_72();
	virtual void	Unk_73();
	virtual void	Unk_74();
	virtual void	Unk_75();
	virtual void	Unk_76();
	virtual void	Unk_77();
	virtual void	Unk_78();
	virtual void	Unk_79();
	virtual void	Unk_7A();
	virtual void	GetMarkerPosition(NiPoint3 * pos);
	virtual void	Unk_7C();
	virtual void	Unk_7D();
	virtual void	Unk_7E();
	virtual void	Unk_7F();
	virtual void	Unk_80();
	virtual void	Unk_81();
	virtual void	Unk_82();
	virtual void	Unk_83();
	virtual void	Unk_84();
	virtual void	Unk_85();
	virtual void	Unk_86();
	virtual void	Unk_87();
	virtual void	Unk_88();
	virtual void	Unk_89();
	virtual void	Unk_8A();
	virtual NiNode *	GetActorRootNode();	// 8B - Returns either first person or third person, possibly the active skeleton
	virtual NiNode *	GetObjectRootNode(); // 8C - Returns the 3rd person skeleton
	virtual void	Unk_8D();
	virtual void	Unk_8E();
	virtual void	Unk_8F();
	virtual void	Unk_90();
	virtual void	Unk_91();
	virtual void	Unk_92();
	virtual void	Unk_93();
	virtual void	Unk_94();
	virtual void	Unk_95();
	virtual void	Unk_96();
	virtual void	Unk_97();
	virtual void	Unk_98();
	virtual void	Unk_99();
	virtual void	Unk_9A();
	virtual void	Unk_9B();
	virtual void	Unk_9C();
	virtual void	Unk_9D();
	virtual void	Unk_9E();
	virtual void	Unk_9F();
	virtual ActorEquipData	** GetEquipData(bool bFirstPerson);
	virtual void	Unk_A1();
	virtual void	Unk_A2();
	virtual void	Unk_A3();
	virtual void	Unk_A4();
	virtual void	Unk_A5();
	virtual void	Unk_A6();
	virtual void	Unk_A7();
	virtual void	Unk_A8();
	virtual void	Unk_A9();
	virtual void	Unk_AA();
	virtual void	Unk_AB();
	virtual void	Unk_AC();
	virtual void	Unk_AD();
	virtual void	Unk_AE();
	virtual void	Unk_AF();
	virtual void	Unk_B0();
	virtual void	Unk_B1();
	virtual void	Unk_B2();
	virtual void	Unk_B3();
	virtual void	Unk_B4();
	virtual void	Unk_B5();
	virtual void	Unk_B6();
	virtual void	Unk_B7();
	virtual void	Unk_B8();
	virtual void	Unk_B9();
	virtual void	Unk_BA();
	virtual void	Unk_BB();
	virtual void	Unk_BC();
	virtual void	Unk_BD();
	virtual void	Unk_BE();
	virtual void	Unk_BF();
	virtual void	Unk_C0();
	virtual void	Unk_C1();
	virtual void	Unk_C2();
	virtual void	Unk_C3();

	enum { kTypeID = kFormType_REFR };
	
	// parents
	BSHandleRefObject							handleRefObject;		// 20
	BSTEventSink <BSActiveGraphIfInactiveEvent>	activeGraphIfInactive;	// 30
	BSTEventSink <BSAnimationGraphEvent>		animGraphEventSink;		// 38
	BSTEventSink <BGSInventoryListEvent::Event>	inventoryListSink;		// 40
	IAnimationGraphManagerHolder				animGraphHolder;		// 48
	IKeywordFormBase							keywordFormBase;		// 50
	ActorValueOwner								actorValueOwner;		// 58
	void										* unk60;				// 60
	void										* unk68;				// 68
	UInt32										unk70;					// 70
	UInt32										unk74;					// 74
	UInt32										unk78;					// 78
	UInt32										unk7C;					// 7C
	UInt64										unk80;					// 80
	UInt64										unk88;					// 88
	UInt64										unk90;					// 90
	UInt64										unk98;					// 98
	UInt64										unkA0;					// A0
	UInt64										unkA8;					// A8
	UInt64										unkB0;					// B0
	TESObjectCELL								* parentCell;			// B8
	float										unkC0[(0xE0 - 0xC0) >> 2];	// C0
	TESForm										* baseForm;				// E0
	void										* unkE8;				// E8
	void										* unkF0;				// F0 - Root node at 0x08
	BGSInventoryList							* inventoryList;		// F8
	ExtraDataList								* extraDataList;		// 100 - ExtraData?
	UInt32										unk104;					// 104
	UInt32										unk108;					// 108

	UInt32 CreateRefHandle(void);

	MEMBER_FN_PREFIX(TESObjectREFR);
	DEFINE_MEMBER_FN(GetReferenceName, const char *, 0x004095A0);
};
STATIC_ASSERT(offsetof(TESObjectREFR, parentCell) == 0xB8);
STATIC_ASSERT(offsetof(TESObjectREFR, baseForm) == 0xE0);
STATIC_ASSERT(sizeof(TESObjectREFR) == 0x110);

// 490
class Actor : public TESObjectREFR
{
public:
	virtual void	Unk_C4();
	virtual void	Unk_C5();
	virtual void	Unk_C6();
	virtual void	Unk_C7();
	virtual void	Unk_C8();
	virtual void	Unk_C9();
	virtual void	Unk_CA();
	virtual void	Unk_CB();
	virtual void	Unk_CC();
	virtual void	Unk_CD();
	virtual void	Unk_CE();
	virtual void	Unk_CF();
	virtual void	Unk_D0();
	virtual void	Unk_D1();
	virtual void	Unk_D2();
	virtual void	Unk_D3();
	virtual void	Unk_D4();
	virtual void	Unk_D5();
	virtual void	Unk_D6();
	virtual void	Unk_D7();
	virtual void	Unk_D8();
	virtual void	Unk_D9();
	virtual void	Unk_DA();
	virtual void	Unk_DB();
	virtual void	Unk_DC();
	virtual void	Unk_DD();
	virtual void	Unk_DE();
	virtual void	Unk_DF();
	virtual void	Unk_E0();
	virtual void	Unk_E1();
	virtual void	Unk_E2();
	virtual void	Unk_E3();
	virtual void	Unk_E4();
	virtual void	Unk_E5();
	virtual void	Unk_E6();
	virtual void	Unk_E7();
	virtual void	Unk_E8();
	virtual void	Unk_E9();
	virtual void	Unk_EA();
	virtual void	Unk_EB();
	virtual void	Unk_EC();
	virtual void	Unk_ED();
	virtual void	Unk_EE();
	virtual void	Unk_EF();
	virtual void	Unk_F0();
	virtual void	Unk_F1();
	virtual void	Unk_F2();
	virtual void	Unk_F3();
	virtual void	Unk_F4();
	virtual void	Unk_F5();
	virtual void	Unk_F6();
	virtual void	Unk_F7();
	virtual void	Unk_F8();
	virtual void	Unk_F9();
	virtual void	Unk_FA();
	virtual void	Unk_FB();
	virtual void	Unk_FC();
	virtual void	Unk_FD();
	virtual void	Unk_FE();
	virtual void	Unk_FF();
	virtual void	Unk_100();
	virtual void	Unk_101();
	virtual void	Unk_102();
	virtual void	Unk_103();
	virtual void	Unk_104();
	virtual void	Unk_105();
	virtual void	Unk_106();
	virtual void	Unk_107();
	virtual void	Unk_108();
	virtual void	Unk_109();
	virtual void	Unk_10A();
	virtual void	Unk_10B();
	virtual void	Unk_10C();
	virtual void	Unk_10D();
	virtual void	Unk_10E();
	virtual void	Unk_10F();
	virtual void	Unk_110();
	virtual void	Unk_111();
	virtual void	Unk_112();
	virtual void	Unk_113();
	virtual void	Unk_114();
	virtual void	Unk_115();
	virtual void	Unk_116();
	virtual void	Unk_117();
	virtual void	Unk_118();
	virtual void	Unk_119();
	virtual void	Unk_11A();
	virtual void	Unk_11B();
	virtual void	Unk_11C();
	virtual void	Unk_11D();
	virtual void	Unk_11E();
	virtual void	Unk_11F();
	virtual void	Unk_120();
	virtual void	Unk_121();
	virtual void	Unk_122();
	virtual void	Unk_123();
	virtual void	Unk_124();
	virtual void	Unk_125();
	virtual void	Unk_126();
	virtual void	Unk_127();
	virtual void	Unk_128();
	virtual void	Unk_129();
	virtual void	Unk_12A();
	virtual void	Unk_12B();
	virtual void	Unk_12C();
	virtual void	Unk_12D();
	virtual void	Unk_12E();
	virtual void	Unk_12F();
	virtual void	Unk_130();

	enum { kTypeID = kFormType_ACHR };

	MagicTarget	magicTarget;	// 110
	ActorState	actorState;		// 128
	BSTEventSink<BSMovementDataChangedEvent>	movementDataChanged;	// 138
	BSTEventSink<BSTransformDeltaEvent>			transformDelta;			// 140
	BSTEventSink<BSSubGraphActivationUpdate>	subGraphActivation;		// 148
	BSTEventSink<bhkCharacterMoveFinishEvent>	characterMoveFinished;	// 150
	BSTEventSink<bhkNonSupportContactEvent>		nonSupportContact;		// 158
	BSTEventSink<bhkCharacterStateChangeEvent>	characterStateChanged;	// 160

	UInt64	unk168[(0x2D0-0x168)/8];	// 168
	UInt32	actorFlags; // 2D0

	enum ActorFlags
	{
		kFlag_Teammate = (1 << 26)
	};

	UInt32	unk2D4;
	UInt64	unk2D8[(0x300-0x2D8)/8];	// 2D8

	struct Data300
	{
		void * unk00;	// 00

		struct Data08
		{
			UInt64	unk00[0x496/8];		// 000
			enum
			{
				kDirtyHeadParts	= 0x04,
				kDirtyGender	= 0x20
			};
			UInt16	unk496;				// 496 - somekind of dirty flag?
		};

		Data08 * unk08;	// 08
	};
	Data300 * unk300;					// 300
	UInt64	unk308[(0x428-0x308)/8];
	ActorEquipData	* equipData;		// 428
	UInt64	unk430[(0x490-0x430)/8];	// 430

	bool IsPlayerTeammate()
	{
		return (actorFlags & kFlag_Teammate) == kFlag_Teammate;
	}

	MEMBER_FN_PREFIX(Actor);
	DEFINE_MEMBER_FN(QueueUpdate, void, 0x00D70400, bool bDoFaceGen, UInt32 unk2, bool unk3, UInt32 unk4); // 0, 0, 1, 0
	DEFINE_MEMBER_FN(IsHostileToActor, bool, 0x00D77290, Actor * actor);
};
STATIC_ASSERT(offsetof(Actor, equipData) == 0x428);

// E10
class PlayerCharacter : public Actor
{
public:
	enum { kTypeID = kFormType_ACHR };

	virtual void	Unk_131();
	virtual void	Unk_132();
	virtual void	Unk_133();
	virtual void	Unk_134();

	BSTEventSink<MenuOpenCloseEvent>	menuOpenClose;		// 490
	BSTEventSink<MenuModeChangeEvent>	menuModeChange;		// 498
	BSTEventSink<UserEventEnabledEvent>	userEventEnabled;	// 4A0
	BSTEventSink<TESHitEvent>			hitEvent;			// 4A8
	BSTEventSink<PerkEntryUpdatedEvent::PerkValueEvents>	perkValueEvents;	// 4B0
	IMovementPlayerControlsFilter		movementControlsFilter;	// 4B8

	UInt64	unk458[(0xB70-0x4C0)/8];	// 4C0
	ActorEquipData	* playerEquipData;	// B70 - First person?
	UInt64	unkB68[(0xD00-0xB78)/8];	// B78
	tArray<BGSCharacterTint::Entry*> * tints;	// D00
	UInt64	unkC90[(0xE10-0xCF8)/8];	// CF8
};

extern RelocPtr <PlayerCharacter*> g_player;

STATIC_ASSERT(offsetof(PlayerCharacter, menuOpenClose) == 0x490);
STATIC_ASSERT(offsetof(PlayerCharacter, playerEquipData) == 0xB70);
STATIC_ASSERT(offsetof(PlayerCharacter, tints) == 0xD00);
