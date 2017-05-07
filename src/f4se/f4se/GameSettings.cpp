#include "f4se/GameSettings.h"

RelocPtr <INISettingCollection *> g_iniSettings(0x05BC1908);
RelocPtr <INIPrefSettingCollection*> g_iniPrefSettings(0x05A8FFB8);
RelocPtr <RegSettingCollection *> g_regSettings(0x05FC5C10);

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
