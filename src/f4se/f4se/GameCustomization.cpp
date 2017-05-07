#include "f4se/GameCustomization.h"
#include "f4se/GameAPI.h"

// 6E6D6B9C5754133F46724CAD540B520D846299B9+B5
RelocPtr <CharacterCreation*> g_characterCreation(0x058AB4E0);	// array
// 6E6D6B9C5754133F46724CAD540B520D846299B9+AF
RelocPtr <UInt32> g_characterIndex(0x058AB518);

RelocAddr<_CreateCharacterTintEntry> CreateCharacterTintEntry(0x00298F70);
RelocAddr<_CopyCharacterTints> CopyCharacterTints(0x00297F60);
RelocAddr<_ClearCharacterTints> ClearCharacterTints(0x0029E1B0);

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
