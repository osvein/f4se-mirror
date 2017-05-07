#include "f4se/GameForms.h"
#include "f4se/GameUtilities.h"

RelocAddr <_LookupFormByID> LookupFormByID(0x00145C60);

BGSCharacterTint::Template::Entry * TESRace::CharGenData::GetTemplateByIndex(UInt16 index)
{
	if(!tintData)
		return nullptr;

	for(UInt32 i = 0; i < tintData->count; i++)
	{
		CharacterCreation::TintData * data;
		tintData->GetNthItem(i, data);

		for(UInt32 k = 0; k < data->entry.count; k++)
		{
			BGSCharacterTint::Template::Entry* entry;
			data->entry.GetNthItem(k, entry);

			if(entry->templateIndex == index)
				return entry;
		}
	}

	return nullptr;
}

template<int T>
UInt32 TESRace::BoneScale<T>::GetHash(const BSFixedString * key)
{
	UInt32 hash;
	CalculateCRC32_64(&hash, (UInt64)(*key)->Get<char>(), 0);
	return hash;
}