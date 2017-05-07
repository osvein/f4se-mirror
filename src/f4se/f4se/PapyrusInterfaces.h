#pragma once

#include "f4se_common/Relocation.h"
#include "f4se_common/Utilities.h"

#include "f4se/GameTypes.h"

class VMIdentifier;

// 08
class IClientVM
{
public:
	virtual void	Unk_01(void) = 0;
	virtual void	Unk_02(void) = 0;
};

// 08
class IStackCallbackSaveInterface
{
public:
	virtual ~IStackCallbackSaveInterface();

	virtual void	Unk_01(void);
	virtual void	Unk_02(void);
};

// ??
class IVMSaveLoadInterface
{
public:
	virtual ~IVMSaveLoadInterface();

	virtual void	Unk_01();
	virtual void	Unk_02();
	virtual void	Unk_03();
	virtual void	Unk_04();
	virtual void	Unk_05();
	virtual bool	Unk_06();
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
};

// ??
class IVMDebugInterface
{
public:
	virtual ~IVMDebugInterface();

	virtual void	Unk_01();
	virtual void	Unk_02();
	virtual void	Unk_03();
	virtual void	Unk_04();
	virtual void	Unk_05();
};

// 08
class IMemoryPagePolicy
{
public:
	virtual ~IMemoryPagePolicy();

	virtual void	Unk_01() = 0;
	virtual void	Unk_02() = 0;
	virtual void	Unk_03() = 0;
	virtual void	Unk_04() = 0;
	virtual void	Unk_05() = 0;
};

// 28
class SimpleAllocMemoryPagePolicy : public IMemoryPagePolicy
{
public:
	virtual void	Unk_01();
	virtual void	Unk_02();
	virtual void	Unk_03();
	virtual void	Unk_04();
	virtual void	Unk_05();

	UInt64	unk08;	// 08
	UInt64	unk10;	// 10
	UInt64	unk18;	// 18
	UInt64	unk20;	// 20
};

// ??
class Logger
{
public:
	virtual void	Unk_01();
	virtual void	Unk_02();
};

// 20
class ILoader
{
public:
	virtual void	Unk_01();
	virtual void	Unk_02();

	UInt64	unk08;	// 08
	UInt64	unk10;	// 10
	UInt64	unk18;	// 18
};

// 38
class CompiledScriptLoader : public ILoader
{
public:
	UInt64	unk20;	// 20
	UInt64	unk28;	// 28
	UInt64	unk30;	// 30
};

// 08
class IComplexType
{
public:
	virtual ~IComplexType();

	virtual UInt32	GetType() = 0;

	SInt32				m_refCount;	// 08
	UInt32				unk0C;		// 0C
	BSFixedString		m_typeName;	// 10
	IComplexType		* m_parent;	// 18

	void	AddRef(void);
	void	Release(void);
};

class IObjectHandlePolicy
{
public:
	IObjectHandlePolicy();
	virtual ~IObjectHandlePolicy();

	virtual bool	IsType(UInt32 typeID, UInt64 handle);
	virtual bool	Unk_02(UInt64 unk1, UInt32 * formType);
	virtual bool	Unk_03(UInt64 handle);
	virtual bool	Unk_04(UInt64 unk1);
	virtual bool	Unk_05(UInt64 unk1);
	virtual UInt64	GetInvalidHandle(void);
	virtual UInt64	Create(UInt32 typeID, void * srcData);
	virtual bool	IsREFR(UInt64 handle);	// return IsType(TESObjectREFR::kTypeID, handle);
	virtual UInt64	Unk_08(UInt64 unk1);
	virtual UInt32	Unk_09(UInt64 unk1);
	virtual UInt32	Unk_0A(UInt64 unk1);
	virtual void *	Resolve(UInt32 typeID, UInt64 handle);
	virtual void	AddRef(UInt64 handle);
	virtual void	Release(UInt64 handle);
	virtual void	GetName(UInt64 handle, void * outStr);
};

extern RelocPtr <IObjectHandlePolicy *> g_objectHandlePolicy;

class IObjectBindPolicy
{
public:
	IObjectBindPolicy();
	virtual ~IObjectBindPolicy();

	virtual void	Unk_01(UInt64 unk);
	virtual void	Unk_02(UInt64 unk);
	virtual void	Unk_03(UInt64 unk);
	virtual void	Unk_04(UInt64 unk);
	virtual SInt32	Unk_05(void);
	virtual UInt32	Unk_06(UInt64 unk);
	virtual UInt32	Unk_07(void);
	virtual void	Unk_08(void);
	virtual void	Unk_09(UInt64 unk0, UInt16 unk1, UInt64 unk2, UInt64 unk3);
	virtual void	* Unk_0A(void);
	virtual void	Unk_0B(UInt64 unk0, UInt64 unk1, UInt64 unk2, UInt8 unk3);
	virtual void	Unk_0C(UInt64 unk0, UInt64 unk1, UInt64 unk2, UInt8 unk3);
	virtual UInt64	Unk_0D(UInt64 unk0, UInt64 unk1, UInt8 unk2, UInt64 unk3, UInt64 unk4);
	virtual void	Unk_0E(UInt64 unk0, UInt64 unk1, UInt8 unk2, UInt64 unk3, UInt64 unk4);

	MEMBER_FN_PREFIX(IObjectBindPolicy);
	DEFINE_MEMBER_FN(BindObject, void, 0x025F9D10, VMIdentifier ** identifier, UInt64 handle);
};
