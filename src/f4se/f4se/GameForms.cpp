#include "f4se/GameForms.h"
#include "f4se/GameUtilities.h"

RelocAddr <_LookupFormByID> LookupFormByID(0x0014C5E0);

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
