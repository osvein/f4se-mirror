#pragma once

#include "f4se_common/Utilities.h"
#include "f4se_common/Relocation.h"

#include "f4se/GameTypes.h"
#include "f4se/GameUtilities.h"
#include "f4se/ScaleformCallbacks.h"
#include "f4se/ScaleformValue.h"

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

	void			* inputUser;	// 10	BSInputEventUser
	UInt32			unk18;			// 18
	UInt32			unk1C;			// 1C
	GFxValue		stage;			// 20
	GFxMovieView	* movie;		// 40
	BSFixedString	unk48;			// 48
	BSFixedString	menuName;		// 50
	UInt64			unk58;			// 58
	UInt64			unk60;			// 60
};
STATIC_ASSERT(offsetof(IMenu, movie) == 0x40);

// E0
class GameMenuBase : public IMenu
{
public:
	virtual ~GameMenuBase();

	virtual void	Unk_10(void);
	virtual void	Unk_11(void);
	virtual void	Unk_12(void);

	UInt64 unk68[(0xE0-0x68)/8];
};

// 218
class LooksMenu : public GameMenuBase
{
public:
	BSTEventSink<ChargenCharacterUpdateEvent> eventSink; // E0
	UInt64	unkE8;	// E8
	void	* unkF0; // F0 - LooksInputRepeatHandler
	UInt64 unkF8[(0x150-0xF8)/8];
	UInt32	nextBoneID;			// 150
	UInt32	currentBoneID;		// 154
	UInt64	unk158[(0x218-0x158)/8];


	MEMBER_FN_PREFIX(LooksMenu);
	DEFINE_MEMBER_FN(LoadCharacterParameters, void, 0x00B3EB70); // This function updates all the internals from the current character
																 // It's followed by a call to onCommitCharacterPresetChange
};
STATIC_ASSERT(offsetof(LooksMenu, nextBoneID) == 0x150);

// 00C
class MenuTableItem
{
public:
	BSFixedString	name;				// 000
	IMenu			* menuInstance;		// 008	0 if the menu is not currently open
	void			* menuConstructor;	// 010
	void			* unk18;			// 018

	bool operator==(const MenuTableItem & rhs) const	{ return name == rhs.name; }
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
		_MESSAGE("\t\tinstance: %08X", menuInstance);
	}
};

// 250 ?
class UI
{
public:
	virtual ~UI();

	virtual void	Unk_01(void);

	typedef IMenu*	(*CreateFunc)(void);
	typedef tHashSet<MenuTableItem,BSFixedString> MenuTable;

	bool	IsMenuOpen(BSFixedString * menuName);
	IMenu * GetMenu(BSFixedString * menuName);
	IMenu * GetMenuByMovie(GFxMovieView * movie);
	void	Register(const char* name, CreateFunc creator)
	{
		CALL_MEMBER_FN(this, RegisterMenu)(name, creator, 0);
	}

protected:
	MEMBER_FN_PREFIX(UI);
	DEFINE_MEMBER_FN(RegisterMenu, void, 0x02017780, const char * name, CreateFunc creator, UInt64 unk1);
	DEFINE_MEMBER_FN(IsMenuOpen, bool, 0x02015BF0, BSFixedString * name);

	UInt64	unk08[(0x190-0x08)/8];	// 458
	tArray<IMenu*>	menuStack;		// 190
	MenuTable		menuTable;		// 1A8
	// ...
};

extern RelocPtr <UI*> g_ui;
