#pragma once

#include "f4se/GameUtilities.h"
#include "f4se/GameTypes.h"

#include "f4se/PapyrusInterfaces.h"
#include "f4se/PapyrusValue.h"

// skipping the BSScript::Internal namespace stuff

class IFunction;

// 08
class Lock
{
public:
	UInt32	m_threadID;
	UInt32	m_lockCount;
};

// BSScript::Internal::VirtualMachine: ??_7VirtualMachine@Internal@BSScript@@6B@
class VirtualMachine
{
public:
	VirtualMachine();
	virtual ~VirtualMachine();

	virtual void	Unk_01();	// take m_lockC0 and then calls this+C8
	virtual void	Unk_02(UInt64 unk);	// take m_lockC0 and then sets m_unkE8
	virtual void	Unk_03();
	virtual void	Unk_04();
	virtual void	Unk_05(UInt8 unk);	// set m_unk82BC
	virtual bool	Unk_06();	// take m_lockBDC4, return m_BDF4 & 2
	virtual void	RegisterForm(UInt32 typeID, const char * papyrusClassName);
	virtual void	Unk_08();
	virtual bool	GetObjectTypeInfo(UInt32 formType, VMObjectTypeInfo ** outTypeInfo);	// Must release outTypeInfo explicitly
	virtual void	Unk_0A();
	virtual void	Unk_0B();
	virtual bool	Unk_0C(BSFixedString * typeName0, UInt32 * unk);
	virtual void	Unk_0D();
	virtual void	Unk_0E();
	virtual void	Unk_0F();
	virtual void	Unk_10();
	virtual void	Unk_11();
	virtual void	Unk_12();
	virtual bool	GetStructTypeInfo(BSFixedString * name, VMStructTypeInfo ** outTypeInfo);	// Must release outTypeInfo explicitly
	virtual void	Unk_14();
	virtual void	Unk_15();
	virtual void	Unk_16();
	virtual bool	CreateObjectIdentifier(BSFixedString * className, VMIdentifier ** identifier);
	virtual bool	CreateStruct(BSFixedString * name, VMValue::StructData ** value);
	virtual bool	CreateArray(VMValue * value, UInt32 size, VMValue::ArrayData ** data);
	virtual void	Unk_1A();
	virtual void	RegisterFunction(IFunction * fn);
	virtual void	SetFunctionFlagsEx(const char * className, UInt32 unk0, const char * fnName, UInt32 flags);
	virtual void	SetFunctionFlags(const char * className, const char * fnName, UInt32 flags);
	virtual void	Unk_1E();
	virtual bool	GetObjectIdentifier(UInt64 handle, const char * typeName, UInt64 unk1, VMIdentifier ** identifier, UInt8 unk2);
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
	virtual IObjectHandlePolicy *	GetHandlePolicy(void);
	virtual void	Unk_34();
	virtual IObjectBindPolicy *		GetObjectBindPolicy(void);
	virtual void	Unk_36();
	virtual void	Unk_37();
	virtual void	Unk_38();
	virtual void	Unk_39();
	virtual void	Unk_3A();
	virtual void	Unk_3B();
	virtual void	Unk_3C();
	virtual void	Unk_3D();

private:

//	void	** _vtbl;					// 00
	UInt64	pad08[(0xC0 - 0x08) >> 3];	// 08
	Lock	m_lockC0;					// C0
	UInt64	padC8[(0xE8 - 0xC8) >> 3];	// C8
	UInt64	m_unkE8;					// E8
	UInt64	unkF0[(0x168 - 0xF0) >> 3];

public:
	class ComplexTypeInfoItem
	{
	public:
		BSFixedString		name;			// 00
		IComplexType		* typeInfo;		// 08

		bool operator==(const ComplexTypeInfoItem & rhs) const	{ return name == rhs.name; }
		bool operator==(const BSFixedString a_name) const	{ return name == a_name; }
		operator UInt64() const								{ return (UInt64)name.data->Get<char>(); }

		static inline UInt32 GetHash(BSFixedString * key)
		{
			UInt32 hash;
			CalculateCRC32_64(&hash, (UInt64)key->data, 0);
			return hash;
		}

		void Dump(void)
		{
			_MESSAGE("\t\tname: %s", name.data->Get<char>());
			_MESSAGE("\t\tinstance: %08X", typeInfo);
		}
	};
	tHashSet<ComplexTypeInfoItem, BSFixedString> m_objectTypes;	// 168
	tHashSet<ComplexTypeInfoItem, BSFixedString> m_structTypes;	// 198
	// 1F0 - Another hash set, don't know what this data is
};
STATIC_ASSERT(offsetof(VirtualMachine, m_objectTypes) == 0x168);
STATIC_ASSERT(offsetof(VirtualMachine, m_structTypes) == 0x198);

// 87A0?
class GameVM : public IClientVM
{
public:
	virtual ~GameVM();

	virtual void	Unk_01();
	virtual void	Unk_02();

	IStackCallbackSaveInterface m_callbackSaveInterface;	// 08

	enum
	{
		kEventSink_Stats = 0,
		kEventSink_InputEnableLayerDestroyed,
		kEventSink_PositionPlayer,
		kEventSink_FormDelete,
		kEventSink_FormIDRemap,
		kEventSink_InitScript,
		kEventSink_ResolveNPCTemplates,
		kEventSink_UniqueIDChange,
		kEventSink_NumEvents
	};

	void			* m_eventSinks[kEventSink_NumEvents];	// 10
	UInt64			unk50[(0xB0 - 0x50) >> 3];				// 50

	VirtualMachine			* m_virtualMachine;				// B0
	IVMSaveLoadInterface	* m_saveLoadInterface;			// B8
	IVMDebugInterface		* m_debugInterface;				// C0
	SimpleAllocMemoryPagePolicy	m_memoryPagePolicy;			// C8

	UInt64			unkF0[(0x1E0 - 0xF0) >> 3];				// F0
	IObjectHandlePolicy		* m_objectHandlePolicy;			// 1E0
	// ...
};

extern RelocPtr <GameVM *> g_gameVM;
