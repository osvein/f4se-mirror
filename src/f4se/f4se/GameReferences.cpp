#include "f4se/GameReferences.h"

// 1FA931E3C3B406454210A0EDC37BDD0C84C8C04A+6B
RelocPtr <PlayerCharacter*> g_player(0x05AC26F8);

// 0BE70664D4DF11A3F88748D9CB45B23D0B4FD50C+2F
RelocAddr <_LookupREFRByHandle> LookupREFRByHandle(0x0000AB60);

RelocAddr <_CreateHandleByREFR> CreateHandleByREFR(0x0000A8A0);

// 3A53807E195FFAEA7AA0EF7FD42D84E4EA0B755A+D0
RelocPtr <UInt32> g_invalidRefHandle(0x038EB204);

RelocAddr <_HasDetectionLOS> HasDetectionLOS(0x013596C0);

RelocAddr <_GetLinkedRef_Native> GetLinkedRef_Native(0x00480E60);

RelocAddr <_SetLinkedRef_Native> SetLinkedRef_Native(0x00480E80);

RelocAddr <_MoveRefrToPosition> MoveRefrToPosition(0x013FC820);

UInt32 TESObjectREFR::CreateRefHandle(void)
{
	if (handleRefObject.GetRefCount() > 0)
	{
		UInt32 refHandle = 0;
		CreateHandleByREFR(&refHandle, this);
		return refHandle;
	}
	else
	{
		return *g_invalidRefHandle;
	}
}
