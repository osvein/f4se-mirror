#include <map>
#include <algorithm>
#include <string>

#include "common/IFileStream.h"

#include "f4se/PluginAPI.h"
#include "f4se/GameData.h"
#include "f4se/InternalSerialization.h"
#include "f4se/Serialization.h"

// Internal

static UInt8	s_savefileIndexMap[0xFF];
static UInt8	s_numSavefileMods = 0;

void LoadModList(const F4SESerializationInterface * intfc)
{
	_MESSAGE("Loading mod list:");

	char name[0x104] = { 0 };
	UInt16 nameLen = 0;

	intfc->ReadRecordData(&s_numSavefileMods, sizeof(s_numSavefileMods));
	for (UInt32 i = 0; i < s_numSavefileMods; i++)
	{
		intfc->ReadRecordData(&nameLen, sizeof(nameLen));
		intfc->ReadRecordData(&name, nameLen);
		name[nameLen] = 0;

		UInt8 newIndex = (*g_dataHandler)->GetLoadedModIndex(name);
		s_savefileIndexMap[i] = newIndex;
		_MESSAGE("\t(%d -> %d)\t%s", i, newIndex, &name);
	}
}

void SaveModList(const F4SESerializationInterface * intfc)
{
	UInt8 modCount = (*g_dataHandler)->modList.loadedModCount;

	intfc->OpenRecord('MODS', 0);
	intfc->WriteRecordData(&modCount, sizeof(modCount));

	_MESSAGE("Saving mod list:");

	for (UInt32 i = 0; i < modCount; i++)
	{
		ModInfo * modInfo = (*g_dataHandler)->modList.loadedMods[i];
		UInt16 nameLen = strlen(modInfo->name);
		intfc->WriteRecordData(&nameLen, sizeof(nameLen));
		intfc->WriteRecordData(modInfo->name, nameLen);
		_MESSAGE("\t(%d)\t%s", i, &modInfo->name);
	}
}

UInt8 ResolveModIndex(UInt8 modIndex)
{
	return (modIndex < s_numSavefileMods) ? s_savefileIndexMap[modIndex] : 0xFF;
}

//// Callbacks

void Core_RevertCallback(const F4SESerializationInterface * intfc)
{
	
}

void Core_SaveCallback(const F4SESerializationInterface * intfc)
{
	SaveModList(intfc);
}

void Core_LoadCallback(const F4SESerializationInterface * intfc)
{
	UInt32 type, version, length;

	while (intfc->GetNextRecordInfo(&type, &version, &length))
	{
		switch (type)
		{
		// Mod list
		case 'MODS':
			LoadModList(intfc);
			break;

		default:
			_MESSAGE("Unhandled chunk type in Core_LoadCallback: %08X (%.4s)", type, &type);
			continue;
		}
	}
}

void Init_CoreSerialization_Callbacks()
{
	Serialization::SetUniqueID(0, 0);
	Serialization::SetRevertCallback(0, Core_RevertCallback);
	Serialization::SetSaveCallback(0, Core_SaveCallback);
	Serialization::SetLoadCallback(0, Core_LoadCallback);
}
