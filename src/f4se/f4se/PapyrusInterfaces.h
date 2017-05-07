#pragma once

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
