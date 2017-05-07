#include "f4se/GameCustomization.h"
#include "f4se/GameAPI.h"

RelocPtr <CharacterCreation*> g_characterCreation(0x0599AE30);	// array
RelocPtr <UInt32> g_characterIndex(0x0599AE68);

RelocAddr<_CreateCharacterTintEntry> CreateCharacterTintEntry(0x00299010);
RelocAddr<_CopyCharacterTints> CopyCharacterTints(0x00298000);
RelocAddr<_ClearCharacterTints> ClearCharacterTints(0x0029E250);

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
