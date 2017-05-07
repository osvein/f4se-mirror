#pragma once

#include "f4se_common/Utilities.h"
#include "f4se_common/Relocation.h"

#include "f4se/GameTypes.h"
#include "f4se/ScaleformCallbacks.h"

// 68
class IMenu : public SWFToCodeFunctionHandler
{
public:
	virtual ~IMenu();

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

	void	* inputUser;	// 10	BSInputEventUser
	UInt32	unk18;			// 18
	UInt32	unk1C;			// 1C
	void	* unk20;		// 20
	UInt32	unk28;			// 28
	UInt32	unk2C;			// 2C
	void	* unk30;		// 30
	UInt64	unk38;			// 38
	GFxMovieView * unk40;	// 40
	BSFixedString	unk48;	// 48
	BSFixedString	menuName;	// 50
	UInt64	unk58;			// 58
	UInt64	unk60;			// 60
};

// E0
class GameMenuBase : public IMenu
{
public:
	virtual ~GameMenuBase();

	virtual void	Unk_10(void);
	virtual void	Unk_11(void);
	virtual void	Unk_12(void);

	// ...
};

// Yes, this class is literally called UI
class UI
{
public:
	virtual ~UI();

	virtual void	Unk_01(void);

	typedef IMenu*	(*CreateFunc)(void);

private:
	MEMBER_FN_PREFIX(UI);
	DEFINE_MEMBER_FN(RegisterMenu, void, 0x01F6D320, const char * name, CreateFunc creator, UInt64 unk1);

	// tArray<IMenu*> menuStack;	// 190
	// 1B0 - tHashSet
};

extern RelocPtr <UI*> g_ui;
