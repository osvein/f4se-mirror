#include "f4se/PapyrusActor.h"

#include "f4se/PapyrusVM.h"
#include "f4se/PapyrusNativeFunctions.h"
#include "f4se/PapyrusArgs.h"
#include "f4se/PapyrusStruct.h"

#include "f4se/GameForms.h"
#include "f4se/GameReferences.h"
#include "f4se/GameRTTI.h"
#include "f4se/GameObjects.h"
#include "f4se/GameExtraData.h"
	
DECLARE_STRUCT(WornItem, "Actor", 5, TESForm*, TESForm*, BSFixedString, BGSMaterialSwap*, BGSTextureSet*)

namespace papyrusActor
{
	WornItem GetWornItem(Actor* actor, UInt32 slotIndex, bool bFirstPerson)
	{
		WornItem result;
		result.Set<0, TESForm*>(nullptr);
		result.Set<1, TESForm*>(nullptr);
		result.Set<2, BSFixedString>("");
		result.Set<3, TESForm*>(nullptr);
		result.Set<4, BGSTextureSet*>(nullptr);
		if(slotIndex >= ActorEquipData::kMaxSlots) {
			result.SetNone(true);
			return result;
		}

		ActorEquipData * equipData = actor->equipData;
		PlayerCharacter * pPC = DYNAMIC_CAST(actor, Actor, PlayerCharacter);
		if(pPC && bFirstPerson)
			equipData = pPC->playerEquipData;

		if(equipData) {
			auto materialSwap = equipData->slots[slotIndex].modelMatSwap;
			result.Set<0, TESForm*>(equipData->slots[slotIndex].item);
			result.Set<1, TESForm*>(equipData->slots[slotIndex].model);
			if(materialSwap) {
				result.Set<2, BSFixedString>(materialSwap->GetModelName());
				result.Set<3, TESForm*>(materialSwap->materialSwap);
			}
			result.Set<4, BGSTextureSet*>(equipData->slots[slotIndex].textureSet);
		}

		return result;
	}

	VMArray<BGSMod::Attachment::Mod*> GetWornItemMods(Actor* actor, UInt32 slotIndex)
	{
		VMArray<BGSMod::Attachment::Mod*> result;
		result.SetNone(true);

		// Invalid slot id
		if(slotIndex >= ActorEquipData::kMaxSlots)
			return result;

		// This should be possible but check anyway
		ActorEquipData * equipData = actor->equipData;
		if(!equipData)
			return result;

		// Make sure there is an item in this slot
		auto item = equipData->slots[slotIndex].item;
		if(!item)
			return result;

		// Array is valid after this point, just means there are no mods if the following are false
		result.SetNone(false);

		auto extraData = equipData->slots[slotIndex].extraData;
		if(!extraData)
			return result;
		auto data = extraData->data;
		if(!data || !data->forms)
			return result;

		for(UInt32 i = 0; i < data->blockSize / sizeof(BGSObjectInstanceExtra::Data::Form); i++)
		{
			BGSMod::Attachment::Mod * objectMod = (BGSMod::Attachment::Mod *)Runtime_DynamicCast(LookupFormByID(data->forms[i].formId), RTTI_TESForm, RTTI_BGSMod__Attachment__Mod);
			result.Push(&objectMod);
		}

		return result;
	}
}

void papyrusActor::RegisterFuncs(VirtualMachine* vm)
{
	vm->RegisterFunction(
		new NativeFunction2<Actor, WornItem, UInt32, bool>("GetWornItem", "Actor", papyrusActor::GetWornItem, vm));

	vm->RegisterFunction(
		new NativeFunction1<Actor, VMArray<BGSMod::Attachment::Mod*>, UInt32>("GetWornItemMods", "Actor", papyrusActor::GetWornItemMods, vm));

	vm->SetFunctionFlags("Actor", "GetWornItem", IFunction::kFunctionFlag_NoWait);
}
