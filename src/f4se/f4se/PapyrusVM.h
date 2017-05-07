#pragma once

#include "f4se/PapyrusInterfaces.h"

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
	virtual void	RegisterFunction(IFunction * fn);
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

private:

//	void	** _vtbl;					// 00
	UInt64	pad08[(0xC0 - 0x08) >> 3];	// 08
	Lock	m_lockC0;					// C0
	UInt64	padC8[(0xE8 - 0xC8) >> 3];	// C8
	UInt64	m_unkE8;					// E8
	// F0
};

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

	// ...
};
