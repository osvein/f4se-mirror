#include "f4se/GameMenus.h"

// 2CA5233612B3158658DB6DB9C90FD0258F1836E2+AD
RelocPtr <UI*> g_ui(0x057167E8);

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
			if(movie == itemMenu->movie) {
				menu = itemMenu;
				return false;
			}
		}

		return true;
	});

	return menu;
}
