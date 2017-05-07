#pragma once

#include "f4se_common/Utilities.h"

#include "f4se/GameFormComponents.h"
#include "f4se/GameForms.h"
#include "f4se/GameEvents.h"
#include "f4se/GameCustomization.h"
#include "f4se/GameUtilities.h"
#include "f4se/NiTextures.h"

class TESClass;
class TESCombatStyle;
class TESFaction;
class BGSOutfit;
class BGSHeadPart;
class BGSColorForm;
class BGSFootstepSet;
class SpellItem;

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
	BGSAttackDataForm			attackData;				// 178
	BGSPerkRankArray			perkRankArray;			// 188
	BGSPropertySheet			propertySheet;			// 1A0
};
STATIC_ASSERT(sizeof(TESActorBase) == 0x1B0);

// 308
class TESNPC : public TESActorBase
{
public:
	enum { kTypeID = kFormType_NPC_ };

	// parents
	TESRaceForm					race;					// 1B0
	BGSOverridePackCollection	overridePackCollection;	// 1C0
	BGSForcedLocRefType			forcedLocRefType;		// 1F8
	BGSNativeTerminalForm		nativeTerminalForm;		// 208
	BSTEventSink<MenuOpenCloseEvent>	menuOpenCloseEvent;		// 210
	BGSAttachParentArray		attachParentArray;		// 220

	struct HeadData
	{
		HeadData() : hairColor(nullptr), unk08(nullptr) { }

		BGSColorForm	* hairColor;	// 00
		void			* unk08;		// 08

		DEFINE_STATIC_HEAP(Heap_Allocate, Heap_Free)
	};

	UInt32						unk238;					// 238
	UInt16						unk23C;					// 23C
	UInt8						unk23E;					// 23E
	UInt8						pad23F;					// 23F
	TESClass					* npcClass;				// 240
	HeadData					* headData;				// 248
	UInt64						unk250;					// 250
	TESCombatStyle				* combatStyle;			// 258
	UInt64						unk260;					// 260
	UInt64						unk268;					// 268
	TESNPC						* templateNPC;			// 270
	float						weightThin;				// 278
	float						weightMuscular;			// 27C
	float						weightLarge;			// 280
	float						unk284;					// 284
	float						unk288;					// 288
	UInt32						unk28C;					// 28C
	UInt64						unk290;					// 290
	void						* unk298;				// 298
	UInt64						unk2A0;					// 2A0
	UInt64						unk2A8;					// 2A8
	BGSOutfit					* outfit[2];			// 2B0
	UInt64						unk2C0;					// 2C0
	TESFaction					* unk2C8;				// 2C8
	BGSHeadPart					** headParts;			// 2D0
	tArray<float>				* morphSetValue;		// 2D8 - 5 elements (MRSV)

	// 08
	struct MorphSetData // (MSDK/MSDV) pair
	{
		UInt32	key;		// 00
		float	value;		// 04

		bool operator==(const UInt32 a_key) const	{ return key == a_key; }
		operator UInt32() const						{ return key; }
		static inline UInt32 GetHash(const UInt32 * key)
		{
			UInt32 hash;
			CalculateCRC32_32(&hash, *key, 0);
			return hash;
		}

		void Dump(void)
		{
			_MESSAGE("\t\tkey: %08X ", key);
			_MESSAGE("\t\tdata: %f", value);
		}
	};

	// 28
	struct FaceMorphRegion	// (FMRI/FMRS) pair
	{
		UInt32	index;		// 00
		float	value[8];	// 04

		bool operator==(const UInt32 a_key) const	{ return index == a_key; }
		operator UInt32() const						{ return index; }
		static inline UInt32 GetHash(const UInt32 * key)
		{
			UInt32 hash;
			CalculateCRC32_32(&hash, *key, 0);
			return hash;
		}

		void Dump(void)
		{
			_MESSAGE("\t\tkey: %08X ", index);
			for(UInt32 i = 0; i < 8; i++)
				_MESSAGE("\t\tdata: %f", value[i]);
		}
	};

	tHashSet<FaceMorphRegion, UInt32>	* morphRegionData;	// 2E0 - (key links to CharacterCreation::FaceMorphRegion::index)
	UInt8								numHeadParts;		// 2E8
	UInt8								unk2E9;				// 2E9
	UInt8								unk2EA;				// 2EA
	UInt8								unk2EB;				// 2EB
	UInt8								unk2EC;				// 2EC
	UInt8								unk2ED;				// 2ED
	UInt8								unk2EE;				// 2EE
	UInt8								unk2EF;				// 2EF
	UInt64								unk2F0;				// 2F0
	tHashSet<MorphSetData, UInt32>		* morphSetData;		// 2F8 - (key links to CharacterCreation::MorphGroup::Preset::index)
	tArray<BGSCharacterTint::Entry*>	* tints;			// 300

	MEMBER_FN_PREFIX(TESNPC);
	DEFINE_MEMBER_FN(ctor, TESNPC*, 0x00598A50);
	DEFINE_MEMBER_FN(HasOverlays, bool, 0x005AA240);
	DEFINE_MEMBER_FN(GetOverlayHeadParts, BGSHeadPart**, 0x005AA350);
	DEFINE_MEMBER_FN(GetNumOverlayHeadParts, int, 0x005AA3E0);
	DEFINE_MEMBER_FN(GetSex, SInt64, 0x0058CD00); // npc->actorData.unk08 & 1
	DEFINE_MEMBER_FN(ChangeHeadPartRemovePart, void, 0x0059F720, BGSHeadPart *, bool bRemoveExtraParts);
	DEFINE_MEMBER_FN(ChangeHeadPart, void, 0x005A3CA0, BGSHeadPart *);

	void ChangeHeadPart(BGSHeadPart * headPart, bool bRemovePart, bool bRemoveExtraParts);
	BGSHeadPart * GetHeadPartByType(UInt32 type, bool bOverlays = false);
};
STATIC_ASSERT(offsetof(TESNPC, npcClass) == 0x240);
STATIC_ASSERT(offsetof(TESNPC, combatStyle) == 0x258);
STATIC_ASSERT(offsetof(TESNPC, outfit) == 0x2B0);
STATIC_ASSERT(offsetof(TESNPC, tints) == 0x300);
STATIC_ASSERT(sizeof(TESNPC) == 0x308);

// 300
class TESObjectWEAP : public TESBoundObject
{
public:
	enum { kTypeID = kFormType_WEAP };

	// 138
	struct InstanceData : public TBO_InstanceData
	{
	public:
		BGSSoundDescriptorForm * unk10;		// 10 BGSSoundDescriptorForm *
		UInt64 unk18;						// 18
		UInt64 unk20;						// 20
		BGSSoundDescriptorForm *unk28;		// 28 BGSSoundDescriptorForm *
		BGSSoundDescriptorForm * unk30;		// 30 BGSSoundDescriptorForm *
		BGSSoundDescriptorForm *unk38;		// 38 BGSSoundDescriptorForm *
		BGSSoundDescriptorForm* unk40;		// 40 BGSSoundDescriptorForm * 
		BGSSoundDescriptorForm * unk48;		// 48 BGSSoundDescriptorForm *
		UInt64 unk50;						// 50
		BGSImpactDataSet* unk58;			// 58 BGSImpactDataSet*
		TESLevItem * unk60;					// 60 TESLevItem *
		TESAmmo* unk68;						// 68 TESAmmo *
		BGSEquipSlot* unk70;				// 70 BGSEquipSlot*
		SpellItem* unk78;					// 78 SpellItem*
		UInt64 unk80;						// 80
		BGSAimModel *unk88;					// 88 BGSAimModel *
		BGSZoomData* unk90;					// 90 BGSZoomData*
		void* unk98;						// 98
		UInt64 unkA0;						// A0
		UInt64 unkA8;						// A8
		UInt64 unkB0;						// B0
		UInt64 unkB8;						// B8
		float unkC0[(0xF0-0xC0)/4];			// C0
		UInt64 unkF0;						// F0
		UInt64 unkF8;						// F8
		UInt64 unk100;						// 100
		UInt32 unk108;						// 108
		UInt32 unk10C;						// 10C
		UInt32 unk110;						// 110
		UInt32 unk114;						// 114
		UInt64 unk118[(0x138-0x118) / 8];	// 118
	};

	// 150
	struct Data : public InstanceData
	{
	public:
		BGSModelMaterialSwap*	swap138;	// 138
		UInt64	unk140;	// 140
		BGSMod::Attachment::Mod*	unk148;	// 148
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
	BGSKeywordForm				keyword;			// 150
	TESDescription				description;		// 170 TESDescription
	BGSInstanceNamingRulesForm	namingRules;		// 188 BGSInstanceNamingRulesForm
	Data						weapData;			// 198 TESObjectWeap::Data
	BGSAttachParentArray		attachParentArray;	// 2E8 BGSAttachParentArray
};
STATIC_ASSERT(offsetof(TESObjectWEAP, previewTransform) == 0x50);
STATIC_ASSERT(offsetof(TESObjectWEAP, destructible) == 0x0E0);
STATIC_ASSERT(offsetof(TESObjectWEAP::InstanceData, unk114) == 0x114);
STATIC_ASSERT(sizeof(TESObjectWEAP::InstanceData) == 0x138);
STATIC_ASSERT(sizeof(TESObjectWEAP) == 0x300);


// 2E0
class TESObjectARMO : public TESBoundObject
{
public:
	enum { kTypeID = kFormType_ARMO };

	TESFullName					fullName;		// 068
	TESRaceForm					raceForm;		// 078
	TESEnchantableForm			enchantable;	// 088
	BGSDestructibleObjectForm	destructible;	// 0A0
	BGSPickupPutdownSounds		pickupPutdown;	// 0B0
	TESBipedModelForm			bipedModel;		// 0C8
	BGSEquipType				equipType;		// 1D0
	BGSBipedObjectForm			bipedObject;	// 1E0
	BGSBlockBashData			blockBash;		// 1F0
	BGSKeywordForm				keywordForm;	// 208
	TESDescription				description;	// 228
	BGSInstanceNamingRulesForm	namingRules;	// 240
	// 58
	struct InstanceData : public TBO_InstanceData
	{
	public:
		UInt64 unk10;
		UInt64 unk18;
		UInt64 unk20;
		UInt64 unk28;
		UInt64 unk30;
		UInt64 unk38;
		UInt32 unk40;
		UInt32 pad44;
		float unk48; // init to 0x7f7fffff
		UInt64 unk50;
	};
	InstanceData				instanceData;	// 250 - 2A8 ( 592 - 680)
	UInt64						unk2A8;
	UInt32						unk2B0;
	UInt32						pad2B4;
	UInt32						unk2B8;
	UInt32						pad2BC;
	UInt64						unk2C0;
	BGSAttachParentArray		parentArray; // 2C8

};
STATIC_ASSERT(sizeof(TESObjectARMO::InstanceData) == 0x58);
STATIC_ASSERT(offsetof(TESObjectARMO, parentArray) == 0x2C8);
STATIC_ASSERT(sizeof(TESObjectARMO) == 0x2E0);

// 228
class TESObjectARMA : public TESObject
{
public:
	enum { kTypeID = kFormType_ARMA };

	TESRaceForm					raceForm;		// 20
	BGSBipedObjectForm			bipedObject;	// 30
	UInt64						unk040;			// 40
	UInt64						unk048;			// 48
	BGSModelMaterialSwap		swap50[2];		// 50
	BGSModelMaterialSwap		swapD0[2];		// D0
	BGSModelMaterialSwap		swap150[2];		// 150
	BGSTextureSet*				unk1D0;			// 1D0 
	BGSTextureSet*				unk1D8;			// 1D8 
	BGSListForm*				unk1E0;			// 1E0 
	UInt64						unk1E8;
	void*						unk1F0;
	UInt32						unk1F8;
	UInt32						pad1FC;
	UInt32						unk200;
	UInt32						pad204;
	BGSFootstepSet*				footstepSet208; // 208
	BGSArtObject*				art210;			// 210
	void*						unk218;
	void*						unk220;

	// Constructs a node name from the specified armor and actor
	bool GetNodeName(char * dest, TESNPC * refr, TESObjectARMO * armor);
};
STATIC_ASSERT(offsetof(TESObjectARMA, unk220) == 0x220);
STATIC_ASSERT(sizeof(TESObjectARMA) == 0x228);


// 350
class BGSTextureSet : public TESBoundObject
{
public:
	enum { kTypeID = kFormType_TXST };

	BSTextureSet textureSet; // 68

	void		* unk78;				// 78
	TESTexture	texture[8];				// 80
	UInt64		unk100[(0x350-0x100)/8]; // 100
};
STATIC_ASSERT(sizeof(BGSTextureSet) == 0x350);


class MagicItem : public TESBoundObject
{
public:
	TESFullName		name;			// 68
	BGSKeywordForm	keywordForm;	// 78
	UnkArray		effectItemsProbably; // 98
	UInt64			unk0B0[4];		// B0
};
STATIC_ASSERT(offsetof(MagicItem, unk0B0) == 0x0B0);
STATIC_ASSERT(sizeof(MagicItem) == 0x0D0);



// 1E0
class AlchemyItem : public MagicItem
{
public:
	enum { kTypeID = kFormType_ALCH };

	BGSModelMaterialSwap	materialSwap; // 0D0
	TESIcon					icon;			// 110
	BGSMessageIcon			msgIcon;		// 120
	TESWeightForm			weightForm;		// 138
	BGSEquipType			equipType;		// 148
	BGSDestructibleObjectForm destructible;	// 158
	BGSPickupPutdownSounds	pickupPutdown;	// 168
	BGSCraftingUseSound		craftingSounds;	// 180
	TESDescription			description;	// 190
	UInt32					unk1A8;			// 1A8
	UInt32					unk1AC;			// 1AC
	UInt64					unk1B0[4];		// 1B0
	TESIcon					icon1D0;		// 1D0
};
STATIC_ASSERT(offsetof(AlchemyItem, icon1D0) == 0x1D0);
STATIC_ASSERT(sizeof(AlchemyItem) == 0x1E0);

// 100
class EnchantmentItem : public MagicItem
{
public:
	enum { kTypeID = kFormType_ENCH };

	UInt64					unk0D0[6];
};
STATIC_ASSERT(offsetof(EnchantmentItem, unk0D0) == 0x0D0);
STATIC_ASSERT(sizeof(EnchantmentItem) == 0x100);


class SpellItem : public MagicItem
{
public:
	enum { kTypeID = kFormType_SPEL };

	BGSEquipType				equipType;		// 0D0
	BGSMenuDisplayObject		displayObject;	// 0E0
	TESDescription				description;	// 0F0
	UInt64						unk108[5];		// 108
};
STATIC_ASSERT(offsetof(SpellItem, description) == 0x0F0);
STATIC_ASSERT(offsetof(SpellItem, unk108) == 0x108);
STATIC_ASSERT(sizeof(SpellItem) == 0x130);

// Seemingly unused in the game. No entries in the DataHandler
// 1B8
class ScrollItem : public SpellItem
{
public:
	enum { kTypeID = kFormType_SCRL };

	BGSModelMaterialSwap		materialSwap;	// 130
	BGSDestructibleObjectForm	destructible;
	BGSPickupPutdownSounds		pickupPutdown;
	TESWeightForm				weight;
	TESValueForm				value;
};

// 188 - only one it seems (Copper Pipe)
class IngredientItem : public MagicItem
{
public:
	enum { kTypeID = kFormType_INGR };

	BGSModelMaterialSwap		materialSwap;	// 0D0
	TESIcon						icon;			// 110
	TESWeightForm				weight;			// 120
	BGSEquipType				equipType;		// 130
	BGSDestructibleObjectForm	destructible;	// 140
	BGSPickupPutdownSounds		pickupPutdown;	// 150
	TESValueForm				value;			// 168
	UInt64						unk178;			// 178
	UInt64						unk180;			// 180
};
STATIC_ASSERT(offsetof(IngredientItem, unk180) == 0x180);
STATIC_ASSERT(sizeof(IngredientItem) == 0x188);


// 170
class TESObjectCONT : public TESBoundAnimObject
{
public:
	enum { kTypeID = kFormType_CONT };

	TESContainer				container;			// 68
	TESFullName					fullName;			// 80
	BGSModelMaterialSwap		materialSwap;		// 90
	TESWeightForm				weightForm;			// D0
//	TESMagicCasterForm			magicCaster;
//	TESMagicTargetForm			magicTarget;
	BGSDestructibleObjectForm	destructible;		// E0
	BGSOpenCloseForm			openClose;			// F0
	BGSKeywordForm				keywordForm;		// F8
	BGSForcedLocRefType			forcedLockRefType;	// 118
	BGSPropertySheet			propertySheet;		// 128
	BGSNativeTerminalForm		nativeTerminal;		// 138
	UInt8						unk148;
	UInt8						unk149;
	UInt8						pad14A[2];
	BGSSoundDescriptorForm*		sound150;
	BGSSoundDescriptorForm*		sound158;
	BGSSoundDescriptorForm*		sound160;
	UInt64						unk168;
};
STATIC_ASSERT(offsetof(TESObjectCONT, pad14A) == 0x14A);
STATIC_ASSERT(sizeof(TESObjectCONT) == 0x170);


// 140
class TESObjectACTI : public TESBoundAnimObject
{
public:
	enum { kTypeID = kFormType_ACTI };

	TESFullName					fullName;			// 68
	BGSModelMaterialSwap		materialSwap;		// 78
	// TESMagicTargetForm		magicTarget;
	BGSDestructibleObjectForm	destructible;		// B8
	BGSOpenCloseForm			openClose;			// C8
	BGSKeywordForm				keywordForm;		// D0
	BGSPropertySheet			propertySheet;		// F0
	BGSForcedLocRefType			forcedLocRefType;	// 100
	BGSNativeTerminalForm		nativeTerminalForm;	// 110
	UInt64						unk120;				// 120
	UInt64						unk128;				// 128
	UInt64						unk130;
	UInt8						unk138;
	UInt8						pad13C[3];		
};
STATIC_ASSERT(sizeof(TESObjectACTI) == 0x140);

// 1A0
class TESFurniture : public TESObjectACTI
{
public:
	enum { kTypeID = kFormType_FURN };

//	BGSNavmeshableObject		navMeshableObject;
	UInt64						unk140;				// 140

	struct Data {
		UInt32 unk00;
		UInt32 unk04;
	};

	tArray<Data>				arr148;
	//UInt64						unk148;
	//UInt32						unk150;
	//UInt32						unk154;
	//UInt32						unk158;
	//UInt32						unk15C;
	BGSAttachParentArray		unk160;
	UInt8						unk178;
	float						unk17C;
	UInt64						unk180;

	struct Data2
	{
		UInt64 unk00[4];
	};

	tArray<Data2>				arr188; // struct { UInt64 data[4]; }
	//void*						unk188;
	//UInt32						unk190;
	//UInt32						unk194;
	//UInt32						unk198;
	//UInt32						unk19C;
};
STATIC_ASSERT(offsetof(TESFurniture, arr188) == 0x188);
STATIC_ASSERT(sizeof(TESFurniture) == 0x1A0);

// 1E0
class BGSTerminal : public TESFurniture
{
public:
	enum { kTypeID = kFormType_TERM };

	UnkArray					arr1A0;
	//void*						unk1A0;	/// 1A0
	//UInt32						unk1A8;
	//UInt32						unk1AC;
	//UInt32						unk1B0;
	//UInt32						unk1B4;
	UnkArray					arr1B8;
	//void*						unk1B8;
	//UInt32						unk1C0;
	//UInt32						unk1C4;
	//UInt32						unk1C8;
	//UInt32						unk1CC;
	void*						unk1D0;
	void*						unk1D8;
};
STATIC_ASSERT(offsetof(BGSTerminal, arr1B8) == 0x1B8);
STATIC_ASSERT(sizeof(BGSTerminal) == 0x1E0);
