#pragma once

#include "f4se_common/Utilities.h"
#include "f4se_common/Relocation.h"

#include "f4se/GameTypes.h"
#include "f4se/GameUtilities.h"
#include "f4se/ScaleformCallbacks.h"
#include "f4se/ScaleformValue.h"

// 70
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
	UInt64			unk60;			// 60	init'd as DWord then Byte
	UInt32			unk68;			// 68	init'd in IMenu::IMenu
	UInt32			pad6C;			// 6C
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

	tArray<BSGFxDisplayObject*>		subcomponents;					// 70
	BSGFxShaderFXTarget				* shaderTarget;					// 88
	UInt64							unk90[(0xE0 - 0x90)>>3];		// 90
};
STATIC_ASSERT(offsetof(GameMenuBase, shaderTarget) == 0x88);

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
	UInt64	unk158[(0x1E0-0x158)/8];
	UInt32	unk1E0;				// 1E0
	UInt32	unk1E4;				// 1E4
	UInt64	unk1E8[(0x218-0x1E8)/8];


	MEMBER_FN_PREFIX(LooksMenu);
	DEFINE_MEMBER_FN(LoadCharacterParameters, void, 0x00B413D0); // This function updates all the internals from the current character
																 // It's followed by a call to onCommitCharacterPresetChange
};
STATIC_ASSERT(offsetof(LooksMenu, nextBoneID) == 0x150);

// 20
template <class T>
class HUDContextArray
{
public:
	T			* entries;	// 00
	UInt32		count;		// 08
	UInt32		unk0C;		// 0C
	UInt32		flags;		// 10
	UInt32		unk14;		// 14
	UInt32		unk18;		// 18
	bool		unk1C;		// 1C
};

// F8
class HUDComponentBase : public BSGFxShaderFXTarget
{
public:
	HUDComponentBase(GFxValue * parent, const char * componentName, HUDContextArray<BSFixedString> * contextList);
	virtual ~HUDComponentBase();

	virtual bool Unk_02() { return false; }
	virtual void Unk_03() { }
	virtual void UpdateComponent() { CALL_MEMBER_FN(this, Impl_UpdateComponent)(); } // Does stuff
	virtual void UpdateVisibilityContext(void * unk1);
	virtual void ColorizeComponent();
	virtual bool IsVisible() { return CALL_MEMBER_FN(this, Impl_IsVisible)(); }
	virtual bool Unk_08() { return contexts.unk1C; }

	UInt64							unkB0;			// B0
	UInt64							unkB8;			// B8
	UInt64							unkC0;			// C0
	HUDContextArray<BSFixedString>	contexts;		// C8
	UInt32							unkE8;			// E8
	UInt32							unkEC;			// EC
	UInt8							unkF0;			// F0
	UInt8							unkF1;			// F1
	bool							isWarning;		// F2 - This chooses the warning color over the default color
	UInt8							padF3[5];		// F3

	MEMBER_FN_PREFIX(HUDComponentBase);
	DEFINE_MEMBER_FN(Impl_ctor, HUDComponentBase *, 0x00A228C0, GFxValue * parent, const char * componentName, HUDContextArray<BSFixedString> * contextList);
	DEFINE_MEMBER_FN(Impl_IsVisible, bool, 0x00A22C00);
	DEFINE_MEMBER_FN(Impl_UpdateComponent, void, 0x00A22960);
	
};
STATIC_ASSERT(offsetof(HUDComponentBase, contexts) == 0xC8);
STATIC_ASSERT(offsetof(HUDComponentBase, unkE8) == 0xE8);
STATIC_ASSERT(sizeof(HUDComponentBase) == 0xF8);

typedef bool (* _HasHUDContext)(HUDContextArray<BSFixedString> * contexts, void * unk1);
extern RelocAddr <_HasHUDContext> HasHUDContext;


// 110
class HUDComponents
{
public:
	UInt64								unk00;					// 00
	HUDComponentBase					* components[0x1E];		// 08
	UInt64								unk98;					// 98
	UInt64								unk100;					// 100
	UInt32								numComponents;			// 108 - 0x1E

	MEMBER_FN_PREFIX(HUDComponents);
	DEFINE_MEMBER_FN(Impl_Destroy, void, 0x01280C60);	// 3DD133AB9DDB89D138FB8958EB3A68CBF2F15DD9+FE
};

// 220
class HUDMenu : public GameMenuBase
{
public:
	BSTEventSink<UserEventEnabledEvent> inputEnabledSink;		// E0
	BSTEventSink<RequestHUDModesEvent>	requestHudModesSink;	// E8
	HUDComponents						children;				// F0
	UInt64								unk200;					// 200
	UInt64								unk208;					// 208
	UInt64								unk210;					// 210
	UInt64								unk218;					// 218
};
STATIC_ASSERT(offsetof(HUDMenu, unk200) == 0x200);

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

	template<typename T>
	void ForEachMenu(T & menuFunc)
	{
		menuTable.ForEach(menuFunc);
	}

protected:
	MEMBER_FN_PREFIX(UI);
	DEFINE_MEMBER_FN(RegisterMenu, void, 0x02042250, const char * name, CreateFunc creator, UInt64 unk1);
	DEFINE_MEMBER_FN(IsMenuOpen, bool, 0x020406C0, BSFixedString * name);

	UInt64	unk08[(0x190-0x08)/8];	// 458
	tArray<IMenu*>	menuStack;		// 190
	MenuTable		menuTable;		// 1A8
	// ...
};

extern RelocPtr <UI*> g_ui;
