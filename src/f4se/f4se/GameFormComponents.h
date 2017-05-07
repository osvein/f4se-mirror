#pragma once

#include "f4se/GameTypes.h"

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

//	void	** _vtbl;	// 00
};

// 10
class TESFullName : public BaseFormComponent
{
public:
	virtual ~TESFullName();

	virtual void	Unk_07(void);
	virtual void	Unk_08(void);

	void	* unk08;	// 08
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
	};
};

// 68
class TESActorBaseData : public BaseFormComponent
{
public:
	virtual ~TESActorBaseData();

	virtual void	Unk_07(void);
	virtual void	Unk_08(void);
	virtual void	Unk_09(void);

	UInt64			unk08;			// 08
	UInt64			unk10;			// 10
	UInt64			unk18;			// 18
	UInt64			unk20;			// 20
	BGSVoiceType	* voiceType;	// 28
	UInt64			unk30[7];		// 30
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

// 20
class TESModel : public BaseFormComponent
{
public:
	virtual const char *	GetModelName(void);
	virtual void			SetModelName(const char * name);
	virtual UInt32			Unk_07(void);

	void*				name;	// 08 StringCache::Ref

	UInt32				unk0C;	// 0C
	UInt32				unk10;	// 10
	UInt16				unk14;	// 14
	UInt8				unk16;	// 16
	UInt8				unk17;	// 17
	UInt32				unk18;	// 18
};

// 40
class BGSModelMaterialSwap : public TESModel
{
public:
	virtual void			Unk_08(void);
	virtual void			Unk_09(void);

	void	* unk20;	// 20
	UInt32	unk28;		// 28
	UInt8	unk2C;		// 2C
	UInt8	unk2D;		// 2D
	UInt16	unk2E;		// 2E
	void	* unk30;	// 30
	UInt32	unk34;		// 34
	UInt32	unk38;		// 38
};

// 10
class TESTexture : public BaseFormComponent
{
public:
	virtual UInt32			Unk_07(void);
	virtual void			Unk_08(void); 	//virtual void			GetNormalMapName(BSString * out);	// might have const char * retn type
	virtual void			Unk_09(void);	//virtual const char *	GetSearchDir(void);	

	void*	str;	// 08 StringCache::Ref
};

// 08
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

// 18
class BGSKeywordForm : public BaseFormComponent
{
public:
	virtual bool	HasKeyword(void* keyword); //BGSKeyword
	virtual UInt32	GetDefaultKeyword(void);

	BGSKeyword	** keywords;	// 08 BGSKeyword
	UInt32		numKeywords;	// 10
	UInt32		unk14;			// 14
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
	void	* unk08;	// 08
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
	void	* unk08;	// 08
};