#pragma once

#include "f4se/GameForms.h"
#include "f4se/GameEvents.h"
#include "f4se/NiObjects.h"

class BSActiveGraphIfInactiveEvent;
class BSAnimationGraphEvent;

class TESObjectCELL;
class NiNode;

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
	virtual void	Unk_7B();
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
	virtual void	Unk_A0();
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
	void										* unkF8;				// F8
	void										* unk100;				// 100 - ExtraData?
	UInt32										unk104;					// 104
	UInt32										unk108;					// 108
};
STATIC_ASSERT(offsetof(TESObjectREFR, parentCell) == 0xB8);
STATIC_ASSERT(offsetof(TESObjectREFR, baseForm) == 0xE0);
STATIC_ASSERT(sizeof(TESObjectREFR) == 0x110);