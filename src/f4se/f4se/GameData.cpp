#include "f4se/GameData.h"

// 856197F11173AF60E35EBF54A88E7BF43AFC3588+305
RelocPtr <DataHandler*> g_dataHandler(0x05715000);

// C5B21010DCF340FCDDDC7866C50C3D78AEF34CB5+6B
RelocPtr <bool> g_isGameDataReady(0x0589EE34);

class LoadedModFinder
{
	const char * m_stringToFind;

public:
	LoadedModFinder(const char * str) : m_stringToFind(str) { }

	bool Accept(ModInfo* modInfo)
	{
		return _stricmp(modInfo->name, m_stringToFind) == 0;
	}
};

const ModInfo * DataHandler::LookupModByName(const char * modName)
{
	return modList.modInfoList.Find(LoadedModFinder(modName));
}

UInt8 DataHandler::GetModIndex(const char* modName)
{
	return modList.modInfoList.GetIndexOf(LoadedModFinder(modName));
}
