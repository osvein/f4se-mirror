#include "f4se/GameMenus.h"

// 2CA5233612B3158658DB6DB9C90FD0258F1836E2+AD
RelocPtr <UI*> g_ui(0x058EEC98);

RelocAddr <_HasHUDContext> HasHUDContext(0x00A4F200);

bool UI::IsMenuOpen(BSFixedString * menuName)
{
	return CALL_MEMBER_FN(this, IsMenuOpen)(menuName);
}

IMenu * UI::GetMenu(BSFixedString * menuName)
{
	if (!menuName || !menuName->data->Get<char>())
		return NULL;

	MenuTableItem * item = menuTable.Find(menuName);

	if (!item)
		return NULL;

	IMenu * menu = item->menuInstance;
	if(!menu)
		return NULL;

	return menu;
}

IMenu * UI::GetMenuByMovie(GFxMovieView * movie)
{
	if (!movie)
		return NULL;

	IMenu * menu = NULL;
	menuTable.ForEach([movie, &menu](MenuTableItem * item)
	{
		IMenu * itemMenu = item->menuInstance;
		if(itemMenu) {
			GFxMovieView * view = itemMenu->movie;
			if(view) {
				if(movie == view) {
					menu = itemMenu;
					return false;
				}
			}
		}
		return true;
	});

	return menu;
}

HUDComponentBase::HUDComponentBase(GFxValue * parent, const char * componentName, HUDContextArray<BSFixedString> * contextList)
{
	CALL_MEMBER_FN(this, Impl_ctor)(parent, componentName, contextList);
}

HUDComponentBase::~HUDComponentBase()
{
	for(UInt32 i = 0; i < contexts.count; i++)
	{
		contexts.entries[i].Release();
	}

	Heap_Free(contexts.entries);
	contexts.count = 0;
}

void HUDComponentBase::UpdateVisibilityContext(void * unk1)
{
	HasHUDContext(&contexts, unk1);
	bool bVisible = IsVisible();
	double alpha = 0.0;
	if(bVisible) {
		alpha = 100.0;
	}

	BSGFxDisplayObject::BSDisplayInfo dInfo;
	void * unk2 = GetExtDisplayInfo(&dInfo, this);
	SetExtDisplayInfoAlpha(unk2, alpha);
	SetExtDisplayInfo(&dInfo);

	unkEC = bVisible == false;
}

void HUDComponentBase::ColorizeComponent()
{
	SetFilterColor(isWarning);
}
