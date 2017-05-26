#include "f4se/PapyrusObjectReference.h"

#include "f4se/PapyrusVM.h"
#include "f4se/PapyrusNativeFunctions.h"
#include "f4se/PapyrusUtilities.h"

#include "f4se/GameReferences.h"
#include "f4se/GameObjects.h"
#include "f4se/GameExtraData.h"
#include "f4se/GameRTTI.h"
#include "f4se/GameData.h"

#include "f4se/Serialization.h"

#include "f4se/PapyrusDelayFunctors.h"

#include <set>

typedef void(*_LinkPower)(BSExtraData* workshopExtraData, TESObjectREFR* akRef1, TESObjectREFR* akRef2, TESObjectREFR* akWireRef);
RelocAddr <_LinkPower> LinkPower_Internal(0x001F4FE0);

typedef void(*_LinkPower2)(TESObjectREFR* akRef, BSExtraData* workshopExtraData);
RelocAddr <_LinkPower2> LinkPower2_Internal(0x001FFCD0);

typedef void(*_LinkPower3)(BSExtraData* workshopExtraData, TESObjectREFR* akWireRef);
RelocAddr <_LinkPower3> LinkPower3_Internal(0x001F4A50);

typedef void(*_LinkPower4)(TESObjectREFR* akWireRef);
RelocAddr <_LinkPower4> LinkPower4_Internal(0x002027D0);

typedef void(*_SetWireEndpoints)(TESObjectREFR* akRef1, SInt32 unk2, TESObjectREFR* akRef2, SInt32 unk4, TESObjectREFR* akWireRef);	// unk2 and unk4 always 0 - Adds the ExtraData
RelocAddr <_SetWireEndpoints> SetWireEndpoints_Internal(0x001FF010);

typedef void(*_FinalizeWireLink)(LocationData* locationData, TESObjectREFR* akWireRef, TESObjectREFR* akRef1, int unk4, TESObjectREFR* akRef2, int unk6);	// unk4 and unk6 always 0
RelocAddr <_FinalizeWireLink> FinalizeWireLink(0x001FED10);

RelocAddr<_PlaceAtMe_Native> PlaceAtMe_Native(0x0013ED4D0);

struct MaterialsReturned
{
	TESForm	* form;
	UInt32	amount;
};

typedef void(*_ScrapReference)(LocationData* locationData, TESObjectREFR** akRef, tArray<MaterialsReturned> * materials);
RelocAddr <_ScrapReference> ScrapReference(0x00206640);


namespace papyrusObjectReference {

	VMArray<BGSMod::Attachment::Mod*> GetAllMods(VMRefOrInventoryObj * thisObj)
	{
		TESForm * baseForm = nullptr;
		ExtraDataList * extraDataList = nullptr;
		thisObj->GetExtraData(&baseForm, &extraDataList);

		VMArray<BGSMod::Attachment::Mod*> result;
		if(extraDataList)
		{
			BSExtraData * extraData = extraDataList->GetByType(ExtraDataType::kExtraData_ObjectInstance);
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

	TESObjectREFR* AttachWireLatent(UInt32 stackId, TESObjectREFR* refA, TESObjectREFR* refB, TESForm* splineForm)
	{
		TESObjectREFR * wireRef = nullptr;
		VirtualMachine* vm = (*g_gameVM)->m_virtualMachine;

		if(!splineForm) {
			splineForm = LookupFormByID(0x0001D971);
		}

		// No specified spline, no refs, refs are same item, or no 3D loaded
		if(!splineForm || !refA || !refB || refA == refB || !refA->GetObjectRootNode() || !refB->GetObjectRootNode()) {
			return nullptr;
		}

		// See if the two references are already linked by the same wire i.e. they have the same entry in their PowerLinks listing
		std::set<UInt64> linkedWires;
		ExtraDataList * extraDataRefA = refA->extraDataList;
		ExtraDataList * extraDataRefB = refB->extraDataList;
		if(extraDataRefA && extraDataRefB)
		{
			ExtraPowerLinks * powerLinksA = (ExtraPowerLinks*)extraDataRefA->GetByType(kExtraData_PowerLinks);
			ExtraPowerLinks * powerLinksB = (ExtraPowerLinks*)extraDataRefB->GetByType(kExtraData_PowerLinks);
			if(powerLinksA && powerLinksB) // Both items must have power links to check
			{
				tArray<UInt64> * connectionSearch;
				tArray<UInt64> * connectionPopulate;
				if(powerLinksA->connections.count < powerLinksB->connections.count) // Pick the smaller list to be the set
				{
					connectionPopulate = &powerLinksA->connections;
					connectionSearch = &powerLinksB->connections;
				}
				else
				{
					connectionPopulate = &powerLinksB->connections;
					connectionSearch = &powerLinksA->connections;
				}

				// Add the items from the smaller list to the set
				for(int i = 0; i < connectionPopulate->count; i++)
				{
					UInt64 formID = 0;
					connectionPopulate->GetNthItem(i, formID);
					linkedWires.insert(formID);
				}

				// Search the other listing for items that exist in the set
				for(int i = 0; i < connectionSearch->count; i++)
				{
					UInt64 formID = 0;
					connectionSearch->GetNthItem(i, formID);

					// This wire exists in the other list, it is invalid to wire the same objects twice
					if(linkedWires.find(formID) != linkedWires.end()) {
						return nullptr;
					}
				}
			}
		}

		BGSBendableSpline * spline = DYNAMIC_CAST(splineForm, TESForm, BGSBendableSpline);
		BGSBendableSpline * splineA = DYNAMIC_CAST(refA->baseForm, TESForm, BGSBendableSpline);
		BGSBendableSpline * splineB = DYNAMIC_CAST(refB->baseForm, TESForm, BGSBendableSpline);

		BGSKeyword * keyword = DYNAMIC_CAST(LookupFormByID(0x00054BA6), TESForm, BGSKeyword);
		// No workshop keyword is bad
		// Connecting a wire to another wire or connecting a non-wire is invalid
		if(!keyword || !spline || splineA || splineB) {
			return nullptr;
		}

		// Get the workshop by keyword
		TESObjectREFR * workshopRef = GetLinkedRef_Native(refA, keyword);
		if(!workshopRef) {
			return nullptr;
		}

		// Workshop ref isn't a workshop!
		BSExtraData* extraDataWorkshop = workshopRef->extraDataList->GetByType(ExtraDataType::kExtraData_WorkshopExtraData);
		if(!extraDataWorkshop) {
			return nullptr;
		}

		// Create our wire instance
		wireRef = PlaceAtMe_Native(vm, stackId, &refA, spline, 1, true, true, false);
		if(!wireRef) {
			return nullptr;
		}

		UInt32 nullHandle = *g_invalidRefHandle;
		TESObjectCELL* parentCell = wireRef->parentCell;
		TESWorldSpace* worldspace = CALL_MEMBER_FN(wireRef,GetWorldspace)();

		NiPoint3 rot;
		MoveRefrToPosition(wireRef, &nullHandle, parentCell, worldspace, &refA->pos, &rot);

		// Set the wire's linked ref to the workshop
		SetLinkedRef_Native(wireRef, workshopRef, keyword);

		LocationData locData(*g_player);
		FinalizeWireLink(&locData, wireRef, refB, 0, refA, 0);
		SetWireEndpoints_Internal(refA, 0, refB, 0, wireRef);

		ExtraBendableSplineParams * splineParams = (ExtraBendableSplineParams*)wireRef->extraDataList->GetByType(kExtraData_BendableSplineParams);
		if(splineParams) {
			splineParams->thickness = 1.5f;
		}

		LinkPower3_Internal(extraDataWorkshop, wireRef);
		LinkPower_Internal(extraDataWorkshop, refA, refB, wireRef);
		LinkPower2_Internal(refA, extraDataWorkshop);
		LinkPower2_Internal(refB, extraDataWorkshop);
		LinkPower4_Internal(wireRef);
		return wireRef;
	}

	DECLARE_DELAY_FUNCTOR(F4SEAttachWireFunctor, 2, AttachWireLatent, TESObjectREFR, TESObjectREFR*, TESObjectREFR*, TESForm*);


	bool AttachWire(VirtualMachine * vm, UInt32 stackId, TESObjectREFR* refA, TESObjectREFR* refB, TESForm* baseSpline)
	{
		if(!refA || !refB)
			return false;

		F4SEDelayFunctorManagerInstance().Enqueue(new F4SEAttachWireFunctor(AttachWireLatent, vm, stackId, refA, refB, baseSpline));
		return true;
	}

	// If this object is a BendableSpline it will link to the two ObjectReferences, otherwise it will link to other BendableSplines
	VMArray<TESObjectREFR*> GetConnectedObjects(TESObjectREFR* thisRef)
	{
		VMArray<TESObjectREFR*> result;
		if(!thisRef)
			return result;

		ExtraDataList * extraDataList = thisRef->extraDataList;
		if(extraDataList)
		{
			if(extraDataList->HasType(kExtraData_PowerLinks))
			{
				ExtraPowerLinks * powerLinks = (ExtraPowerLinks*)extraDataList->GetByType(kExtraData_PowerLinks);
				if(powerLinks)
				{
					for(int i = 0; i < powerLinks->connections.count; i++)
					{
						UInt64 formID = 0;
						powerLinks->connections.GetNthItem(i, formID);

						TESForm * form = LookupFormByID(formID);
						if(form)
						{
							TESObjectREFR * refr = DYNAMIC_CAST(form, TESForm, TESObjectREFR);
							if(refr)
								result.Push(&refr);
						}
					}
				}
			}
		}

		return result;
	}

	BSFixedString GetDisplayName(TESObjectREFR* thisRef)
	{
		if(!thisRef)
			return BSFixedString();

		return CALL_MEMBER_FN(thisRef, GetReferenceName)();
	}


	VMArray<TESForm*> GetInventoryItemsLatent(UInt32 stackId, TESObjectREFR * refr)
	{
		VMArray<TESForm*> results;
		if(!refr)
			return results;

		auto inventory = refr->inventoryList;
		if(inventory) {
			for(int i = 0; i < inventory->items.count; i++) {
				BGSInventoryItem item;
				inventory->items.GetNthItem(i, item);
				
				results.Push(&item.form);
			}
		}

		return results;
	}

	DECLARE_DELAY_FUNCTOR(F4SEInventoryFunctor, 0, GetInventoryItemsLatent, TESObjectREFR, VMArray<TESForm*>);

	bool GetInventoryItems(VirtualMachine * vm, UInt32 stackId, TESObjectREFR* refr)
	{
		if(!refr)
			return false;

		F4SEDelayFunctorManagerInstance().Enqueue(new F4SEInventoryFunctor(GetInventoryItemsLatent, vm, stackId, refr));
		return true;
	}

#ifdef _DEBUG
	void ScrapLatent(UInt32 stackId, TESObjectREFR * refr)
	{
		LocationData locData(*g_player);
		ScrapReference(&locData, &refr, nullptr);
	}

	DECLARE_DELAY_FUNCTOR(F4SEScrapFunctor, 0, ScrapLatent, TESObjectREFR, void);

	bool Scrap(VirtualMachine * vm, UInt32 stackId, TESObjectREFR* refr)
	{
		if(!refr)
			return false;

		F4SEDelayFunctorManagerInstance().Enqueue(new F4SEScrapFunctor(ScrapLatent, vm, stackId, refr));
		return true;
	}
#endif
}

void papyrusObjectReference::RegisterFuncs(VirtualMachine* vm)
{
	F4SEObjectRegistry& f4seObjRegistry = F4SEObjectRegistryInstance();
	f4seObjRegistry.RegisterClass<F4SEAttachWireFunctor>();
	f4seObjRegistry.RegisterClass<F4SEInventoryFunctor>();


#ifdef _DEBUG
	f4seObjRegistry.RegisterClass<F4SEScrapFunctor>();
#endif

	vm->RegisterFunction(
		new NativeFunction0<VMRefOrInventoryObj, VMArray<BGSMod::Attachment::Mod*>>("GetAllMods", "ObjectReference", papyrusObjectReference::GetAllMods, vm));

	vm->RegisterFunction(
		new NativeFunction0<TESObjectREFR, VMArray<TESObjectREFR*>>("GetConnectedObjects", "ObjectReference", papyrusObjectReference::GetConnectedObjects, vm));

	vm->RegisterFunction(
		new LatentNativeFunction2<TESObjectREFR, TESObjectREFR*, TESObjectREFR*, TESForm*>("AttachWire", "ObjectReference", papyrusObjectReference::AttachWire, vm));

	vm->RegisterFunction(
		new NativeFunction0<TESObjectREFR, BSFixedString>("GetDisplayName", "ObjectReference", papyrusObjectReference::GetDisplayName, vm));

	vm->RegisterFunction(
		new LatentNativeFunction0<TESObjectREFR, VMArray<TESForm*>>("GetInventoryItems", "ObjectReference", papyrusObjectReference::GetInventoryItems, vm));

	vm->SetFunctionFlags("ObjectReference", "AttachWire", IFunction::kFunctionFlag_NoWait);
	vm->SetFunctionFlags("ObjectReference", "GetInventoryItems", IFunction::kFunctionFlag_NoWait);

#ifdef _DEBUG
	vm->RegisterFunction(
		new LatentNativeFunction0<TESObjectREFR, void>("Scrap", "ObjectReference", papyrusObjectReference::Scrap, vm));

	vm->SetFunctionFlags("ObjectReference", "Scrap", IFunction::kFunctionFlag_NoWait);
#endif
}
