#pragma once

#include "f4se/NiTypes.h"

class NiRTTI;
class NiExtraData;
class NiNode;
class NiSwitchNode;
class TESObjectREFR;
class NiGeometry;
class BSGeometry;
class BSTriShape;

// 10
class NiRefObject
{
public:
	NiRefObject();
	virtual ~NiRefObject();

	virtual void	DeleteThis(void);	// calls virtual dtor

	void	IncRef(void);
	void	DecRef(void);
	bool	Release(void);

//	void	** _vtbl;		// 00
	volatile SInt32	m_uiRefCount;	// 08
};

// 10
class NiObject : public NiRefObject
{
public:
	virtual NiRTTI			* GetRTTI(void);
	virtual NiNode			* GetAsNiNode(void);
	virtual NiSwitchNode	* GetAsNiSwitchNode(void);
	virtual void Unk_05();
	virtual void Unk_06();
	virtual BSGeometry		* GetAsBSGeometry(void);
	virtual void Unk_08();
	virtual void Unk_09();
	virtual BSTriShape		* GetAsBSTriShape(void);
	virtual void Unk_0B();
	virtual void Unk_0C();
	virtual NiGeometry		* GetAsNiGeometry(void);
	virtual void Unk_0E();
	virtual void Unk_0F();
	virtual void Unk_10();
	virtual void Unk_11();
	virtual void Unk_12();
	virtual void Unk_13();
	virtual void Unk_14();
	virtual void Unk_15();
	virtual void Unk_16();
	virtual void Unk_17();
	virtual void Unk_18();
	virtual void Unk_19();
	virtual void Unk_1A();
	virtual void Unk_1B();
	virtual void Unk_1C();
	virtual void Unk_1D();
	virtual void Unk_1E();
	virtual void Unk_1F();
	virtual void Unk_20();
	virtual void Unk_21();
	virtual void Unk_22();
	virtual void Unk_23();
	virtual void Unk_24();
	virtual void Unk_25();
	virtual void Unk_26();
	virtual void Unk_27();
};

// 18
class NiExtraDataList
{
public:
	NiExtraData	** m_extraData;			// 00
	UInt32		m_extraDataCapacity;	// 08
	UInt32		unk0C;
	UInt32		m_extraDataLength;		// 10
	UInt32		unk14;
};

// 28
class NiObjectNET : public NiObject
{
public:
	void			* m_name;			// 10
	void			* unk10;			// 18 - Controller?
	NiExtraDataList * m_extraDataList;	// 20
};

// 120
class NiAVObject : public NiObjectNET
{
public:

	struct ControllerUpdateContext
	{
		enum
		{
			kDirty =	1 << 0,
		};

		float	delta;
		UInt32	flags;
	};

	virtual void Unk_28();
	virtual void Unk_29();
	virtual void Unk_2A();
	virtual void Unk_2B();
	virtual void Unk_2C();
	virtual void Unk_2D();
	virtual NiAVObject * GetObjectByName(void * nodeName);
	virtual void Unk_2F();
	virtual void Unk_30();
	virtual void Unk_31();
	virtual void Unk_32();
	virtual void Unk_33();
	virtual void UpdateWorldData(ControllerUpdateContext * ctx);
	virtual void Unk_35();
	virtual void Unk_36();
	virtual void Unk_37();
	virtual void Unk_38();

	NiNode			* m_parent;			// 28
	NiTransform		m_localTransform;	// 30
	NiTransform		m_worldTransform;	// 70
	NiPoint3		unkB0;				// B0
	float			unkBC;				// BC
	NiTransform		unkC0;				// C0
	UInt64			unk100;				// 100
	UInt64			unk108;				// 108
	TESObjectREFR	* m_reference;		// 110
	float			unk118;				// 118
	UInt32			unk11C;				// 11C
};
STATIC_ASSERT(offsetof(NiAVObject, m_reference) == 0x110);
STATIC_ASSERT(sizeof(NiAVObject) == 0x120);