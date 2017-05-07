#include "f4se/GameCustomization.h"
#include "f4se/GameAPI.h"

RelocPtr <CharacterCreation*> g_characterCreation(0x05964BA0);	// array
RelocPtr <UInt32> g_characterIndex(0x05964BD8);

RelocAddr<_CreateCharacterTintEntry> CreateCharacterTintEntry(0x00290FB0);
RelocAddr<_CopyCharacterTints> CopyCharacterTints(0x0028FFA0);
RelocAddr<_ClearCharacterTints> ClearCharacterTints(0x002961F0);

bool BGSCharacterTint::Entry::IsEqual(Entry * rhs)
{
	return GetType() == rhs->GetType() && tintIndex == rhs->tintIndex && percent == rhs->percent;
}

bool BGSCharacterTint::PaletteEntry::IsEqual(Entry * rhs)
{
	return __super::IsEqual(rhs) && color == ((PaletteEntry*)rhs)->color && colorID == ((PaletteEntry*)rhs)->colorID;
}

void BGSCharacterTint::Entry::Copy(Entry * rhs)
{
	if(GetType() == rhs->GetType())
	{
		percent = rhs->percent;
	}
}

void BGSCharacterTint::PaletteEntry::Copy(Entry * rhs)
{
	PaletteEntry * pRHS = (PaletteEntry*)rhs;
	if(GetType() == pRHS->GetType())
	{
		percent = pRHS->percent;
		color = pRHS->color;
		colorID = pRHS->colorID;
	}
}
