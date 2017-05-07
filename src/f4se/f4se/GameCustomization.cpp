#include "f4se/GameCustomization.h"
#include "f4se/GameAPI.h"

// 6E6D6B9C5754133F46724CAD540B520D846299B9+B5
RelocPtr <CharacterCreation*> g_characterCreation(0x058AD760);	// array
// 6E6D6B9C5754133F46724CAD540B520D846299B9+AF
RelocPtr <UInt32> g_characterIndex(0x058AD798);

RelocAddr<_CreateCharacterTintEntry> CreateCharacterTintEntry(0x00298C40);
RelocAddr<_CopyCharacterTints> CopyCharacterTints(0x00297C30);
RelocAddr<_ClearCharacterTints> ClearCharacterTints(0x0029DE80);

// These aren't grabbed by RTTI script due to namespacing
const void * RTTI_BGSCharacter_Template_Entry = (void *)0x0352EDE0;
const void * RTTI_BGSCharacter_Template_Mask = (void *)0x0352EE18;
const void * RTTI_BGSCharacter_Template_Palette = (void *)0x0352EE50;
const void * RTTI_BGSCharacter_Template_TextureSet = (void *)0x0352EEC0;

// These are for creating new instances
RelocAddr<uintptr_t> s_BGSCharacterTint_Template_MaskVtbl(0x02B1EFB8);
RelocAddr<uintptr_t> s_BGSCharacterTint_Template_PaletteVtbl(0x02B1EFE8);
RelocAddr<uintptr_t> s_BGSCharacterTint_Template_TextureSetVtbl(0x02B1F018);

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

BGSCharacterTint::Template::Entry * BGSCharacterTint::Template::Entry::Create(UInt32 size, UInt64 vtbl)
{
	void* memory = Heap_Allocate(size);
	memset(memory, 0, size);
	((UInt64*)memory)[0] = vtbl;
	BGSCharacterTint::Template::Entry* xData = (BGSCharacterTint::Template::Entry*)memory;
	return xData;
}

BGSCharacterTint::Template::Mask * BGSCharacterTint::Template::Mask::Create()
{
	return (BGSCharacterTint::Template::Mask *)BGSCharacterTint::Template::Entry::Create(sizeof(BGSCharacterTint::Template::Mask), s_BGSCharacterTint_Template_MaskVtbl.GetUIntPtr());
}

BGSCharacterTint::Template::Palette * BGSCharacterTint::Template::Palette::Create()
{
	return (BGSCharacterTint::Template::Palette *)BGSCharacterTint::Template::Entry::Create(sizeof(BGSCharacterTint::Template::Palette), s_BGSCharacterTint_Template_PaletteVtbl.GetUIntPtr());
}

BGSCharacterTint::Template::TextureSet * BGSCharacterTint::Template::TextureSet::Create()
{
	return (BGSCharacterTint::Template::TextureSet *)BGSCharacterTint::Template::Entry::Create(sizeof(BGSCharacterTint::Template::TextureSet), s_BGSCharacterTint_Template_TextureSetVtbl.GetUIntPtr());
}