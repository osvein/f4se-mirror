#pragma once

#include "f4se/GameTypes.h"
#include "f4se/NiObjects.h"
#include "f4se/GameEvents.h"

class BGSEquipSlot;
class EnchantmentItem;
class BGSKeyword;
class BGSSoundDescriptorForm;
class BGSVoiceType;
class TESForm;
class TESObjectARMO;
class TESRace;
class BGSInstanceNamingRules;
class BGSImpactDataSet;
class BGSMaterialType;
class TESLevItem;
class TESAmmo;
class BGSAimModel;
class BGSZoomData;
class BGSBodyPartData;
class BGSTextureSet;
class BGSMaterialSwap;
class BGSTerminal;
class BGSObjectInstanceExtra;
class TESObjectARMA;
class IAnimationGraphManagerHolder;
class ExtraDataList;
class ActorValueInfo;
class Condition;
class TESObjectREFR;

typedef bool (* _EvaluationConditions)(Condition * condition, TESObjectREFR * ref1, TESObjectREFR * ref2);
extern RelocAddr <_EvaluationConditions> EvaluationConditions; // Evaluates whole condition LinkedList

// 10
class TBO_InstanceData : public BSIntrusiveRefCounted
{
public:
	virtual ~TBO_InstanceData();

	virtual void	Unk_01(void);
	virtual void	Unk_02(void);
	virtual void	Unk_03(void);
	virtual void	Unk_04(void);
	virtual void	Unk_05(void);
	virtual void	Unk_06(void);
	virtual void	Unk_07(void);
	virtual void	Unk_08(void);
	virtual void	Unk_09(void);
	virtual void	Unk_0A(void);
	virtual void	Unk_0B(void);
	virtual void	Unk_0C(void);
	virtual void	Unk_0D(void);
	virtual void	Unk_0E(void);
	virtual void	Unk_0F(void);
	virtual void	Unk_10(void);
	virtual void	Unk_11(void);
	virtual void	Unk_12(void);

//	void	** _vtbl;	// 00
//  BSIntrusiveRefCounted refCount; // 08
};

// 08
class BaseFormComponent
{
public:
	BaseFormComponent();
	virtual ~BaseFormComponent();

	virtual void	Unk_01(void);
	virtual void	Unk_02(void);
	virtual void	Unk_03(void);
	virtual void	Unk_04(void);
	virtual void	Unk_05(void);
	virtual void	Unk_06(void);

//	void	** _vtbl;	// 00
};

// 08
class IAnimationGraphManagerHolder
{
public:
	virtual ~IAnimationGraphManagerHolder();

	virtual void	Unk_01(void);
	virtual void	Unk_02(void);
	virtual void	Unk_03(void);
	virtual void	Unk_04(void);
	virtual void	Unk_05(void);
	virtual void	Unk_06(void);
	virtual void	Unk_07(void);
	virtual void	Unk_08(void);
	virtual void	Unk_09(void);
	virtual void	Unk_0A(void);
	virtual void	Unk_0B(void);
	virtual void	Unk_0C(void);
	virtual void	Unk_0D(void);
	virtual void	Unk_0E(void);
	virtual void	Unk_0F(void);
	virtual void	Unk_10(void);
	virtual void	Unk_11(void);
	virtual void	Unk_12(void);
	virtual void	Unk_13(void);
	virtual void	Unk_14(void);
	virtual void	Unk_15(void);
	virtual void	Unk_16(void);
	virtual void	Unk_17(void);
	virtual void	Unk_18(void);

//	void	** _vtbl;
};

// 08
class IKeywordFormBase
{
public:
	virtual ~IKeywordFormBase();

	virtual void	Unk_01(void);
	virtual void	Unk_02(void);

//	void	** _vtbl;
};

// 08
class ActorValueOwner
{
public:
	virtual ~ActorValueOwner();

	virtual float	GetValue(ActorValueInfo * actorValueInfo);
	virtual float	GetMaximum(ActorValueInfo * actorValueInfo);
	virtual void	Unk_03(void);
	virtual void	Unk_04(void);
	virtual void	Unk_05(void);
	virtual void	Unk_06(void);
	virtual void	Unk_07(void);
	virtual void	Unk_08(void);
	virtual void	Unk_09(void);
	virtual void	Unk_0A(void);

//	void	** _vtbl;	// 00
};

// 10
class TESFullName : public BaseFormComponent
{
public:
	virtual ~TESFullName();

	virtual void	Unk_07(void);
	virtual void	Unk_08(void);

	BSFixedString name;	// 08
};

// 10
class BGSPreviewTransform : public BaseFormComponent
{
public:
	virtual ~BGSPreviewTransform();

	void	* unk08;	// 08
};

// 08
class BGSSoundTagComponent : public BaseFormComponent
{
public:
	virtual ~BGSSoundTagComponent();
};


// 68
class TESActorBaseData : public BaseFormComponent
{
public:
	virtual ~TESActorBaseData();

	virtual void	Unk_07(void);
	virtual void	Unk_08(void);
	virtual void	Unk_09(void);

	enum
	{
		kFlagFemale = 0x01,
		kFlagEssential = 0x02,
		kFlagIsPreset = 0x04,
		kFlagRespawn = 0x08,
		kFlagAutoCalcStats = 0x10,
		kFlagUnique = 0x20,
		kFlagDoesntAffectStealthMeter = 0x40,
		kFlagPCLevelMult = 0x80,
		kFlagProtected = 0x800
	};

	UInt64			flags;			// 08
	UInt64			unk10;			// 10
	UInt64			unk18;			// 18
	UInt64			unk20;			// 20
	BGSVoiceType	* voiceType;	// 28
	UInt64			unk30[7];		// 30

	MEMBER_FN_PREFIX(TESActorBaseData);
	DEFINE_MEMBER_FN(SetSex, void, 0x001480A0, UInt32 unk1, bool isFemale, UInt32 unk2); // unk1 = 1, unk2 = 1
};
STATIC_ASSERT(sizeof(TESActorBaseData) == 0x68);

// 18
class TESContainer : public BaseFormComponent
{
public:
	struct Entry
	{
		struct Data
		{
			UInt32	unk00;
			UInt32	unk04;
			float	unk08;
		};

		UInt32	count;	// 00
		UInt32	pad04;	// 04
		TESForm	* form;	// 08
		Data	* data; // 10 - extra data?
	};

	Entry	** entries;	// 08
	UInt32	numEntries;	// 10
	UInt32	pad14;		// 14
};

// 28
class TESAIForm : public BaseFormComponent
{
public:
	UInt64	unk08[(0x28 - 0x08) / 8];	// 08
};

// 10
class BGSSkinForm : public BaseFormComponent
{
public:
	TESObjectARMO	* skin;	// 08
};

// 10
class TESSpellList : public BaseFormComponent
{
public:
	void	* unk08;	// 08
};

// 30
class TESModel : public BaseFormComponent
{
public:
	virtual const char *	GetModelName(void);
	virtual void			SetModelName(const char * name);
	virtual UInt32			Unk_07(void);

	BSFixedString		name;	// 08 StringCache::Ref

	UInt32				unk0C;	// 0C
	UInt32				unk10;	// 10
	UInt16				unk14;	// 14
	UInt8				unk16;	// 16
	UInt8				unk17;	// 17
	UInt32				unk18;	// 18
	void				* unk20;	// 20
	UInt32				unk28;		// 28

	enum
	{
		kFlag_Dynamic = (1 << 0),
		kFlag_Unknown = (1 << 1)
	};

	UInt8				flags;		// 2C
	UInt8				unk2D;		// 2D
	UInt16				unk2E;		// 2E
};

// 30
class BGSBehaviorGraphModel : public TESModel
{
public:
	virtual ~BGSBehaviorGraphModel();
};

// 30
class BGSTextureModel : public TESModel
{
public:
	virtual ~BGSTextureModel();
};

// 30
class TESModelTri : public TESModel
{
public:
	virtual ~TESModelTri();
};

// 40
class BGSModelMaterialSwap : public TESModel
{
public:
	virtual void			Unk_08(void);
	virtual void			Unk_09(void);

	BGSMaterialSwap	* materialSwap;	// 30
	float	unk38;		// 34
	UInt32	pad3C;		// 38
};
STATIC_ASSERT(sizeof(BGSModelMaterialSwap) == 0x40);


// 10
class TESTexture : public BaseFormComponent
{
public:
	virtual UInt32			Unk_07(void);
	virtual void			Unk_08(void); 	//virtual void			GetNormalMapName(BSString * out);	// might have const char * retn type
	virtual void			Unk_09(void);	//virtual const char *	GetSearchDir(void);	

	BSFixedString	str;	// 08 StringCache::Ref
};

// 10
class TESIcon : public TESTexture
{
public:
	virtual ~TESIcon();
};

// 08
class BGSPreloadable : public BaseFormComponent
{
public:
	virtual void			Unk_07(void);
};

// 18
class BGSMessageIcon : public BaseFormComponent
{
public:
	TESIcon	unk08;	// 08
};
STATIC_ASSERT(sizeof(BGSMessageIcon) == 0x18);

// 18
class BGSBlockBashData : public BaseFormComponent
{
public:
	BGSImpactDataSet	* impactDataSet;	// 08	BGSImpactDataSet*
	BGSMaterialType	* materialType;	// 10	BGSMaterialType *
};

// 20
class BGSKeywordForm : public BaseFormComponent
{
public:
	virtual bool	HasKeyword(void* keyword); //BGSKeyword
	virtual UInt32	GetDefaultKeyword(void);

	IKeywordFormBase keywordBase;	// 08
	BGSKeyword	** keywords;		// 10 BGSKeyword
	UInt32		numKeywords;		// 18
	UInt32		unk14;				// 1C
};

// 18
class BGSPickupPutdownSounds : public BaseFormComponent
{
public:
	BGSSoundDescriptorForm	* pickUp;		// 08 BGSSoundDescriptorForm
	BGSSoundDescriptorForm	* putDown;	// 10 BGSSoundDescriptorForm
};

// 18
class TESEnchantableForm : public BaseFormComponent
{
public:
	virtual UInt16	Unk_07(void);		// return unk10

	EnchantmentItem		* enchantment;	// 08 EnchantmentItem
	UInt16				unk10;			// 10
	UInt16				maxCharge;		// 12
	UInt16				pad14[2];		// 14
};

// 10
class BGSDestructibleObjectForm : public BaseFormComponent
{
public:
	void	* data;	// 08
};

// 10
class BGSEquipType : public BaseFormComponent
{
public:
	virtual	BGSEquipSlot *	GetEquipSlot(void);
	virtual void			SetEquipSlot(BGSEquipSlot * type);

	BGSEquipSlot * equipSlot;	// 08
};

// 18
class TESDescription : public BaseFormComponent
{
public:
	void	* unk08;	// 08
	void	* unk10;	// 10

	MEMBER_FN_PREFIX(TESDescription);
	DEFINE_MEMBER_FN(Get, void, 0x0014E470, BSString * out, TESForm * parent);
};

// 10
class BGSInstanceNamingRulesForm : public BaseFormComponent
{
public:
	BGSInstanceNamingRules	* rules;	// 08
};

// 10
class BGSTypedKeywordValueArray
{
public:
	void	* unk00;	// 00
	void	* unk08;	// 08
};

// 18
class BGSAttachParentArray : public BaseFormComponent
{
public:
	BGSTypedKeywordValueArray	unk08;
};

// 10
class BGSAttackDataForm : public BaseFormComponent
{
public:
	void	* unk08; // 08
};

// 18
class BGSPerkRankArray : public BaseFormComponent
{
public:
	void	* unk08;	// 08
	UInt32	unk10;		// 10
	UInt32	pad14;		// 14
};


// 10
class BGSPropertySheet : public BaseFormComponent
{
public:

	struct AVIFProperty
	{
		ActorValueInfo * actorValue;	// 00
		float			value;			// 08
		UInt32			pad0C;			// 0C
	};

	tArray<AVIFProperty>	* sheet;	// 08
};

// 10
class TESRaceForm : public BaseFormComponent
{
public:
	TESRace	* race;	// 08
};

// 38
class BGSOverridePackCollection : public BaseFormComponent
{
public:
	UInt64	unk08;	// 08
	UInt64	unk10;	// 08
	UInt64	unk18;	// 08
	UInt64	unk20;	// 08
	UInt64	unk28;	// 08
	UInt64	unk30;	// 08
};

// 10
class BGSForcedLocRefType : public BaseFormComponent
{
public:
	void	* unk08;	// 08
};

// 10
class BGSNativeTerminalForm : public BaseFormComponent
{
public:
	BGSTerminal	* terminal;	// 08
};

// 10
class BGSBipedObjectForm : public BaseFormComponent
{
public:
	// applicable to DefaultRace
	enum
	{
		kPart_Head =		1 << 0,
		kPart_Hair =		1 << 1,
		kPart_Body =		1 << 2,
		kPart_Hands =		1 << 3,
		kPart_Forearms =	1 << 4,
		kPart_Amulet =		1 << 5,
		kPart_Ring =		1 << 6,
		kPart_Feet =		1 << 7,
		kPart_Calves =		1 << 8,
		kPart_Shield =		1 << 9,
		kPart_Unnamed10 =	1 << 10,
		kPart_LongHair =	1 << 11,
		kPart_Circlet =		1 << 12,
		kPart_Ears =		1 << 13,
		kPart_Unnamed14 =	1 << 14,
		kPart_Unnamed15 =	1 << 15,
		kPart_Unnamed16 =	1 << 16,
		kPart_Unnamed17 =	1 << 17,
		kPart_Unnamed18 =	1 << 18,
		kPart_Unnamed19 =	1 << 19,
		kPart_Unnamed20 =	1 << 20,
		kPart_Unnamed21 =	1 << 21,
		kPart_Unnamed22 =	1 << 22,
		kPart_Unnamed23 =	1 << 23,
		kPart_Unnamed24 =	1 << 24,
		kPart_Unnamed25 =	1 << 25,
		kPart_Unnamed26 =	1 << 26,
		kPart_Unnamed27 =	1 << 27,
		kPart_Unnamed28 =	1 << 28,
		kPart_Unnamed29 =	1 << 29,
		kPart_Unnamed30 =	1 << 30,
		kPart_FX01 =		1 << 31,
	};

	enum
	{
		kWeight_Light =	0,
		kWeight_Heavy,
		kWeight_None,
	};

	struct Data
	{
		UInt32	parts;			// 00 - init'd to 0
		UInt32	weightClass;	// 04 - init'd to 2 (none)
	};

	Data	data;	// 08
};

// 08
class BSISoundDescriptor
{
public:
	virtual ~BSISoundDescriptor();

	virtual void	Unk_01(void) = 0;
	virtual void	Unk_02(void) = 0;
	virtual void	Unk_03(void) = 0;
	virtual void	Unk_04(void) = 0;

	//	void	** _vtbl;	// 00
};

// 08
class BGSSoundDescriptor : public BSISoundDescriptor
{
public:
	virtual void	Unk_01(void);
	virtual void	Unk_02(void);
	virtual void	Unk_03(void);
	virtual void	Unk_04(void);

	//	void	** _vtbl;	// 00
};

// 10
class TESWeightForm : public BaseFormComponent
{
public:
	float	weight;	// 08
	UInt32	pad0C;	// 0C
};

// 10
class BGSCraftingUseSound : public BaseFormComponent
{
public:
	UInt64	unk08;	// 08
};

// 10
class BGSMenuDisplayObject : public BaseFormComponent
{
public:
	UInt64	unk08;	// 08
};

// 10
class TESValueForm : public BaseFormComponent
{
public:
	UInt32	value;	// 08
	UInt32	unk0C;	// 0C
};

// 108
class TESBipedModelForm : public BaseFormComponent
{
public:
	UInt64 unk[(0x108-0x8)/8];
};
STATIC_ASSERT(sizeof(TESBipedModelForm) == 0x108);

// 10
class BGSFeaturedItemMessage : public BaseFormComponent
{
public:
	UInt64	unk08;	// 08
};

// 18
class MagicTarget
{
public:
	virtual ~MagicTarget();

	virtual void	Unk_01(void);
	virtual void	Unk_02(void);
	virtual void	Unk_03(void);
	virtual void	Unk_04(void);
	virtual void	Unk_05(void);
	virtual void	Unk_06(void);
	virtual void	Unk_07(void);
	virtual void	Unk_08(void);
	virtual void	Unk_09(void);
	virtual void	Unk_0A(void);
	virtual void	Unk_0B(void);
	virtual void	Unk_0C(void);

	void * unk08;	// 08
	void * unk10;	// 10
};

// 08
struct IMovementInterface
{
public:
	virtual ~IMovementInterface();
};

// 08
class IMovementState : public IMovementInterface
{
public:
	virtual void	Unk_01() = 0;
	virtual void	Unk_02() = 0;
	virtual void	Unk_03() = 0;
	virtual void	Unk_04() = 0;
	virtual void	Unk_05() = 0;
	virtual void	Unk_06() = 0;
	virtual void	Unk_07() = 0;
	virtual void	Unk_08() = 0;
	virtual void	Unk_09() = 0;
	virtual void	Unk_0A() = 0;
	virtual void	Unk_0B() = 0;
	virtual void	Unk_0C() = 0;
	virtual void	Unk_0D() = 0;
	virtual void	Unk_0E() = 0;
	virtual void	Unk_0F() = 0;
	virtual void	Unk_10() = 0;
	virtual void	Unk_11() = 0;
	virtual void	Unk_12() = 0;
	virtual void	Unk_13() = 0;
	virtual void	Unk_14() = 0;
	virtual void	Unk_15() = 0;
	virtual void	Unk_16() = 0;
	virtual void	Unk_17() = 0;
	virtual void	Unk_18() = 0;
	virtual void	Unk_19() = 0;
	virtual void	Unk_1A() = 0;
	virtual void	Unk_1B() = 0;
	virtual void	Unk_1C() = 0;
	virtual void	Unk_1D() = 0;
	virtual void	Unk_1E() = 0;
	virtual void	Unk_1F() = 0;
	virtual void	Unk_20() = 0;
};

// 10
class ActorState : public IMovementState
{
public:
	virtual void	Unk_01();
	virtual void	Unk_02();
	virtual void	Unk_03();
	virtual void	Unk_04();
	virtual void	Unk_05();
	virtual void	Unk_06();
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

	void * unk08;	// 08
};

// 08
class IPostAnimationChannelUpdateFunctor
{
	virtual ~IPostAnimationChannelUpdateFunctor();

	virtual void	Unk_01();
};

// 38
class Condition
{
public:
	enum CompareFlags {
		kCompareFlag_And = 0x00,
		kCompareFlag_Or = 0x01,
		kCompareFlag_Equal = 0x00,
		kCompareFlag_UseAliases = 0x02,
		kCompareFlag_Global = 0x04,
		kCompareFlag_UsePackData = 0x08,
		kCompareFlag_SwapTarget = 0x10,
	};

	enum CompareOperators {
		kCompareOp_NotEqual = 0,
		kCompareOp_Greater,
		kCompareOp_GreaterEqual,
		kCompareOp_Less,
		kCompareOp_LessEqual
	};

	enum ReferenceTypes {
		kReferenceType_Subject = 0,
		kReferenceType_Target,
		kReferenceType_Reference,
		kReferenceType_CombatTarget,
		kReferenceType_LinkedRef,
		kReferenceType_Alias,
		kReferenceType_PackageData,
		kReferenceType_EventData
	};

	union Param
	{
		float	f32;
		UInt32	u32;
		SInt32	s32;
		TESForm	* form;
	};

	enum Functions
	{
		kFunction_GetSex = 70,
		kFunction_GetBaseValue = 277,
		kFunction_GetPermanentValue = 494
	};

	Condition	* next;					// 00
	float		compareValue;			// 08
	UInt32		unk0C;					// 0C
	UInt32		unk10;					// 10
	UInt32		unk14;					// 14 - FFFFFFFF
	UInt16		functionId;				// 18
	UInt8		unk1A;					// 1A
	UInt8		unk1B;					// 1B
	UInt32		unk1C;					// 1C
	Param		param1;					// 20
	Param		param2;					// 28

	struct CompareType
	{
		unsigned char flags : 5;
		unsigned char op : 3;
	};

	CompareType		comparisonType;			// 30
	UInt8			referenceType;			// 31
	UInt8			unk32[6];				// 32

	// 78
	class Evaluator
	{
	public:
		Evaluator(TESForm * a1, TESForm * a2)
		{
			CALL_MEMBER_FN(this, ctor)(a1, a2, 0);
		}

		TESForm * a1;	// 00
		TESForm * a2;	// 08
		UInt64	unk10[(0x78 - 0x08) >> 3];

		MEMBER_FN_PREFIX(Evaluator);
		DEFINE_MEMBER_FN(ctor, void, 0x007284E0, TESForm * a1, TESForm * a2, UInt64 unk1); // a1 might be player or subject, not sure yet
	};

	MEMBER_FN_PREFIX(Condition);
	DEFINE_MEMBER_FN(Evaluate, bool, 0x0072A2A0, Evaluator * eval); // Evaluates only a single condition
};
STATIC_ASSERT(offsetof(Condition, referenceType) == 0x31);
STATIC_ASSERT(sizeof(Condition) == 0x38);

// ??
struct IMovementPlayerControlsFilter : public IMovementInterface
{
public:
	virtual void	Unk_01();
	virtual void	Unk_02();
	virtual void	Unk_03();
	virtual void	Unk_04();
	virtual void	Unk_05();
	virtual void	Unk_06();
	virtual void	Unk_07();
	virtual void	Unk_08();
	virtual void	Unk_09();
};

// ??
class ActorEquipData
{
public:
	UInt64	unk00;					// 00
	NiNode	* flattenedBoneTree;	// 08

	enum
	{
		kMaxSlots = 44
	};

	// 58
	struct SlotData
	{
		TESForm							* item;			// 00
		TBO_InstanceData				* instanceData;	// 08
		BGSObjectInstanceExtra			* extraData;	// 10
		TESForm							* model;		// 18 - ARMA for ARMO and WEAP for WEAP
		BGSModelMaterialSwap			* modelMatSwap;	// 20
		BGSTextureSet					* textureSet;	// 28
		NiAVObject						* node;			// 30
		void							* unk38;		// 38
		IAnimationGraphManagerHolder	* unk40;		// 40
		UInt64							unk48;			// 48
		UInt32							unk50;			// 50
		UInt32							unk54;			// 54
	};

	SlotData	slots[kMaxSlots];
};

// 08
class EquippedItemData : public NiRefObject
{
public:
	virtual ~EquippedItemData();
};

// 38
class EquippedWeaponData : public EquippedItemData
{
public:
	virtual ~EquippedWeaponData();

	TESAmmo		* ammo;		// 10
	UInt64		unk18;		// 18
	void		* unk20;	// 20
	UInt64		unk28;		// 28
	NiAVObject	* object;	// 30
};

// 10
struct BGSInventoryItem
{
	TESForm * form;	// 00

	// 28
	class Stack : public BSIntrusiveRefCounted
	{
	public:
		virtual ~Stack();

		Stack	* next;		// 10
		ExtraDataList	* extraData;	// 18
		UInt32	unk20;		// 20

		enum
		{
			kFlagEquipped = 7
		};

		UInt16	flags;		// 24

#ifdef _DEBUG
		void Dump();
#endif
		template<typename T>
		bool Visit(T & f)
		{
			if(f(this) && next)
				return next->Visit(f);
			return true; // Continue
		}
	};

#ifdef _DEBUG
	void Dump();
#endif

	Stack * stack;	// 08
};

// ??
class BGSInventoryList
{
public:
	UInt64	unk00;	// 00
	tArray<BSTEventSink<BGSInventoryListEvent::Event>> eventSinks;	// 08
	UInt64	unk20[(0x58-0x20)/8];
	tArray<BGSInventoryItem> items;
};

// 08
class BGSPerkEntry
{
public:
	virtual ~BGSPerkEntry();

	void	* unk08;	// 08
};
