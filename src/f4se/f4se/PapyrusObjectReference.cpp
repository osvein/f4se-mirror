#include "f4se/PapyrusObjectReference.h"

#include "f4se/PapyrusVM.h"
#include "f4se/PapyrusNativeFunctions.h"

#include "f4se/GameReferences.h"
#include "f4se/GameExtraData.h"
#include "f4se/GameRTTI.h"

namespace papyrusObjectReference {

	VMArray<BGSMod::Attachment::Mod*> GetAllMods(TESObjectREFR * thisObj)
	{
		VMArray<BGSMod::Attachment::Mod*> result;
		if(thisObj->extraDataList)
		{
			BSExtraData * extraData = thisObj->extraDataList->GetByType(ExtraDataType::kExtraData_ObjectInstance);
			if(extraData)
			{
				BGSObjectInstanceExtra * objectModData = DYNAMIC_CAST(extraData, BSExtraData, BGSObjectInstanceExtra);
				if(objectModData)
				{
					auto data = objectModData->data;
					if(!data || !data->forms)
						return result;

					for(UInt32 i = 0; i < data->blockSize / sizeof(BGSObjectInstanceExtra::Data::Form); i++)
					{
						BGSMod::Attachment::Mod * objectMod = (BGSMod::Attachment::Mod *)Runtime_DynamicCast(LookupFormByID(data->forms[i].formId), RTTI_TESForm, RTTI_BGSMod__Attachment__Mod);
						result.Push(&objectMod);
					}
				}
			}
		}
		return result;
	}
}

void papyrusObjectReference::RegisterFuncs(VirtualMachine* vm)
{
	vm->RegisterFunction(
		new NativeFunction0<TESObjectREFR, VMArray<BGSMod::Attachment::Mod*>>("GetAllMods", "ObjectReference", papyrusObjectReference::GetAllMods, vm));
}
