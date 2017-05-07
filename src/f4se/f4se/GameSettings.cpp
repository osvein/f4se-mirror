#include "f4se/GameSettings.h"
#include "f4se/GameTypes.h"

// 5B1FD95B3A1729A1781BED06D47E1A47EB6D89F2+91
RelocPtr <INISettingCollection *> g_iniSettings(0x05E5C4A8);
// 239A2F4B85F2D36A7E4E77D681108A197210AE0B+1C3
RelocPtr <INIPrefSettingCollection*> g_iniPrefSettings(0x05AE7258);
// ??_7RegSettingCollection@@6B@
RelocPtr <RegSettingCollection *> g_regSettings(0x0601CD40);

UInt32 Setting::GetType(void) const
{
	if(!name || !name[0]) return kType_Unknown;

	switch(name[0])
	{
		case 'b':	return kType_Bool;
		case 'c':	return kType_Unknown;
		case 'h':	return kType_Unknown;
		case 'i':	return kType_Integer;
		case 'u':	return kType_Unknown;
		case 'f':	return kType_Float;
		case 'S':	return kType_String;	// dynamically allocated string
		case 's':	return kType_String;	// statically allocated string
		case 'r':	return kType_ID6;
		case 'a':	return kType_ID;
	}

	return kType_Unknown;
}

Setting * GetINISetting(const char * name)
{
	Setting	* setting = (*g_iniSettings)->Get(name);
	if(!setting)
		setting = (*g_iniPrefSettings)->Get(name);

	return setting;
}

Setting * SettingCollectionList::Get(const char * name)
{
	Node * node = data;
	do
	{
		Setting * setting = node->data;
		if(setting) {
			BSAutoFixedString searchName(name);
			BSAutoFixedString settingName(setting->name);
			if(searchName == settingName) {
				return setting;
			}
		}

		node = node->next;
	} while(node);

	return nullptr;
}
