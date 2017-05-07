#include "f4se/GameObjects.h"
#include "f4se/GameReferences.h"
#include "f4se/GameUtilities.h"

bool TESObjectARMA::GetNodeName(char * dstBuff, TESNPC * npc, TESObjectARMO * armor)
{
	if(npc) {
		UInt32 sex = npc ? CALL_MEMBER_FN(npc, GetSex)() : 0;
		sprintf_s(dstBuff, MAX_PATH, " (%08X)[%d]/ (%08X)", formID, sex, armor->formID);
		return true;
	}

	return false;
}

UInt32 TESNPC::FaceMorphRegion::GetHash(const UInt32 * key)
{
	UInt32 hash;
	CalculateCRC32_32(&hash, *key, 0);
	return hash;
}

UInt32 TESNPC::MorphSetData::GetHash(const UInt32 * key)
{
	UInt32 hash;
	CalculateCRC32_32(&hash, *key, 0);
	return hash;
}