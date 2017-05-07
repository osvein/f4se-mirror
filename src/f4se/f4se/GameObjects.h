#pragma once

#include "f4se/GameFormComponents.h"
#include "f4se/GameForms.h"
#include "f4se/GameEvents.h"

class TESClass;
class TESCombatStyle;
class BGSOutfit;

// 20+
class TESObject : public TESForm
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
};

// 68
class TESBoundObject : public TESForm
{
public:
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

	struct Bound
	{
		UInt16	x;
		UInt16	y;
		UInt16	z;
	};
	Bound bounds1;								// 20
	Bound bounds2;								// 26
	BGSMod::Template::Items templateItems;		// 30
	BGSPreviewTransform		previewTransform;	// 50
	BGSSoundTagComponent	soundTagComponent;	// 60
};
STATIC_ASSERT(offsetof(TESBoundObject, templateItems) == 0x30);
STATIC_ASSERT(offsetof(TESBoundObject, previewTransform) == 0x50);
STATIC_ASSERT(offsetof(TESBoundObject, soundTagComponent) == 0x60);
STATIC_ASSERT(sizeof(TESBoundObject) == 0x68);

// 30
class TESBoundAnimObject : public TESBoundObject
{
public:

};

// 1B0
class TESActorBase : public TESBoundAnimObject
{
public:
	virtual void	Unk_65();
	virtual void	Unk_66();
	virtual void	Unk_67();
	virtual void	Unk_68();

	// parents
	TESActorBaseData			actorData;				// 68
	TESContainer				container;				// D0
	TESSpellList				spellList;				// E8
	TESAIForm					aiForm;					// F8
	TESFullName					fullName;				// 120
	ActorValueOwner				actorValueOwner;		// 130
	BGSDestructibleObjectForm	destructibleObjectForm;	// 138
	BGSSkinForm					skinForm;				// 148
	BGSKeywordForm				keywords;				// 158
	IKeywordFormBase			iKeywordBase;			// 160
	BGSAttackDataForm			attackData;				// 178
	BGSPerkRankArray			perkRankArray;			// 188
	BGSPropertySheet			propertySheet;			// 1A0
};
STATIC_ASSERT(sizeof(TESActorBase) == 0x1B0);

// 308
class TESNPC : public TESActorBase
{
public:
	// parents
	TESRaceForm					race;					// 1B0
	BGSOverridePackCollection	overridePackCollection;	// 1C0
	BGSForcedLocRefType			forcedLocRefType;		// 1F8
	BGSNativeTerminalForm		nativeTerminalForm;		// 208
	BSTEventSink<MenuOpenCloseEvent>	menuOpenCloseEvent;		// 210
	BGSAttachParentArray		attachParentArray;		// 220

	UInt32						unk238;					// 238
	UInt16						unk23C;					// 23C
	UInt8						unk23E;					// 23E
	UInt8						pad23F;					// 23F
	TESClass					* npcClass;				// *
	void						* unk248;				// 248
	UInt64						unk250;					// 250
	TESCombatStyle				* combatStyle;			// 258
	UInt64						unk260;					// 260
	UInt64						unk268;					// 268
	UInt64						unk270;					// 270
	float						unk278;					// 278
	float						unk27C;					// 27C
	float						unk280;					// 280
	float						unk284;					// 284
	float						unk288;					// 288
	UInt32						unk28C;					// 28C
	UInt64						unk290;					// 290
	void						* unk298;				// 298
	UInt64						unk2A0;					// 2A0
	UInt64						unk2A8;					// 2A8
	BGSOutfit					* outfit;				// 2B0
	UInt64						unk2B8;					// 2B8
	UInt64						unk2C0;					// 2C0
	UInt64						unk2C8;					// 2C8
	void						* unk2D0;				// 2D0
	UInt64						unk2D8;					// 2D8
	void						* unk2E0;				// 2E0
	UInt32						unk2E8;					// 2E8
	float						unk2EC;					// 2EC
	UInt64						unk2F0;					// 2F0
	void						* unk2F8;				// 2F8
	void						* unk300;				// 300
};
STATIC_ASSERT(offsetof(TESNPC, npcClass) == 0x240);
STATIC_ASSERT(offsetof(TESNPC, combatStyle) == 0x258);
STATIC_ASSERT(offsetof(TESNPC, outfit) == 0x2B0);
STATIC_ASSERT(sizeof(TESNPC) == 0x308);

// 300
class TESObjectWEAP : public TESBoundObject
{
public:
	// 138
	struct InstanceData : public TBO_InstanceData
	{
	public:
		UInt64 unk10;						// 10
		UInt64 unk18;						// 18
		UInt64 unk20;						// 20
		BGSSoundDescriptorForm *unk28;		// 28 BGSSoundDescriptorForm *
		UInt64 unk30;						// 30
		BGSSoundDescriptorForm *unk38;		// 38 BGSSoundDescriptorForm *
		BGSSoundDescriptorForm* unk40;		// 40 BGSSoundDescriptorForm * 
		UInt64 unk48;						// 48
		UInt64 unk50;						// 50
		BGSImpactDataSet* unk58;			// 58 BGSImpactDataSet*
		TESLevItem * unk60;					// 60 TESLevItem *
		TESAmmo* unk68;						// 68 TESAmmo *
		BGSEquipSlot* unk70;				// 70 BGSEquipSlot*
		UInt64 unk78;						// 78
		UInt64 unk80;						// 80
		BGSAimModel *unk88;					// 88 BGSAimModel *
		BGSZoomData* unk90;					// 90 BGSZoomData*
		void* unk98;						// 98
		UInt64 unkA0;						// A0
		UInt64 unkA8;						// A8
		UInt64 unkB0;						// B0
		UInt64 unkB8;						// B8
		float unkC0[(0xF0-0xC0)/4];		// C0
		UInt64 unkF0[(0x138 - 0xF0) / 8];	// 10
	};

	// 150
	struct Data : public InstanceData
	{
	public:
		UInt64	unk138;	// 138
		UInt64	unk140;	// 140
		UInt64	unk148;	// 148
	};

	TESFullName					fullName;			// 068
	BGSModelMaterialSwap		materialSwap;		// 078	BGSModelMaterialSwap
	TESIcon						icon;				// 0B8
	TESEnchantableForm			enchantable;		// 0C8 TESEnchantableForm
	BGSDestructibleObjectForm	destructible;		// 0E0 BGSDestructibleObjectForm
	BGSEquipType				equipType;			// 0F0 BGSEquipType
	BGSPreloadable				preloadable;		// 100 BGSPreloadable
	BGSMessageIcon				messageIcon;		// 108 BGSMessageIcon
	BGSPickupPutdownSounds		pickupSounds;		// 120
	BGSBlockBashData			blockBash;			// 128
	IKeywordFormBase			iKeywordBase;		// 150 IKeywordBase
	BGSKeywordForm				keyword;			// 158
	TESDescription				description;		// 170 TESDescription
	BGSInstanceNamingRulesForm	namingRules;		// 188 BGSInstanceNamingRulesForm
	Data						weapData;			// 198 TESObjectWeap::Data
	BGSAttachParentArray		attachParentArray;	// 2E8 BGSAttachParentArray
};
STATIC_ASSERT(offsetof(TESObjectWEAP, previewTransform) == 0x50);
STATIC_ASSERT(offsetof(TESObjectWEAP, destructible) == 0x0E0);
STATIC_ASSERT(offsetof(TESObjectWEAP::InstanceData, unk30) == 0x030);
STATIC_ASSERT(sizeof(TESObjectWEAP::InstanceData) == 0x138);
STATIC_ASSERT(sizeof(TESObjectWEAP) == 0x300);