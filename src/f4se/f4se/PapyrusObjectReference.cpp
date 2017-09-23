#include "f4se/PapyrusObjectReference.h"

#include "f4se/PapyrusVM.h"
#include "f4se/PapyrusNativeFunctions.h"
#include "f4se/PapyrusUtilities.h"

#include "f4se/GameReferences.h"
#include "f4se/GameObjects.h"
#include "f4se/GameExtraData.h"
#include "f4se/GameRTTI.h"
#include "f4se/GameData.h"
#include "f4se/GameWorkshop.h"

#include "f4se/NiExtraData.h"
#include "f4se/NiObjects.h"
#include "f4se/NiNodes.h"
#include "f4se/bhkWorld.h"

#include "f4se/Serialization.h"

#include "f4se/PapyrusDelayFunctors.h"

#include <set>

RelocAddr<_PlaceAtMe_Native> PlaceAtMe_Native(0x01409120);

DECLARE_STRUCT(ConnectPoint, "ObjectReference");

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
			BGSDefaultObject * splineDefault = (*g_defaultObjectMap)->GetDefaultObject("WorkshopSplineObject");
			if(splineDefault) {
				splineForm = splineDefault->form;
			}
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

		BGSKeyword * keyword = nullptr;
		BGSDefaultObject * workshopItemDefault = (*g_defaultObjectMap)->GetDefaultObject("WorkshopItem");
		if(workshopItemDefault) {
			keyword = DYNAMIC_CAST(workshopItemDefault->form, TESForm, BGSKeyword);
		}

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

	BSFixedString GetDisplayName(VMRefOrInventoryObj * thisObj)
	{
		TESForm * baseForm = nullptr;
		ExtraDataList * extraDataList = nullptr;
		thisObj->GetExtraData(&baseForm, &extraDataList);

		if(baseForm)
		{
			if(extraDataList)
			{
				BSExtraData * extraData = extraDataList->GetByType(ExtraDataType::kExtraData_TextDisplayData);
				if(extraData)
				{
					ExtraTextDisplayData * displayText = DYNAMIC_CAST(extraData, BSExtraData, ExtraTextDisplayData);
					if(displayText)
					{
						return *CALL_MEMBER_FN(displayText, GetReferenceName)(baseForm);
					}
				}
			}

			TESFullName* pFullName = DYNAMIC_CAST(baseForm, TESForm, TESFullName);
			if (pFullName)
				return pFullName->name;
		}

		return BSFixedString();
	}


	VMArray<TESForm*> GetInventoryItemsLatent(UInt32 stackId, TESObjectREFR * refr)
	{
		VMArray<TESForm*> results;
		if(!refr)
			return results;

		auto inventory = refr->inventoryList;
		if(inventory) {
			inventory->inventoryLock.Lock();

			for(int i = 0; i < inventory->items.count; i++) {
				BGSInventoryItem item;
				inventory->items.GetNthItem(i, item);
				
				results.Push(&item.form);
			}

			inventory->inventoryLock.Release();
		}

		return results;
	}

	float GetInventoryWeight(TESObjectREFR * refr)
	{
		return refr ? CALL_MEMBER_FN(refr, GetInventoryWeight)() : 0.0f;
	}

	DECLARE_DELAY_FUNCTOR(F4SEInventoryFunctor, 0, GetInventoryItemsLatent, TESObjectREFR, VMArray<TESForm*>);

	bool GetInventoryItems(VirtualMachine * vm, UInt32 stackId, TESObjectREFR* refr)
	{
		if(!refr)
			return false;

		F4SEDelayFunctorManagerInstance().Enqueue(new F4SEInventoryFunctor(GetInventoryItemsLatent, vm, stackId, refr));
		return true;
	}

	VMArray<ConnectPoint> GetConnectPointsLatent(UInt32 stackId, TESObjectREFR * refr)
	{
		VMArray<ConnectPoint> results;
		if(!refr)
			return results;

		NiNode * root = refr->GetObjectRootNode();
		if(!root)
			return results;

		BSConnectPoint::Parents * extraData = (BSConnectPoint::Parents *)Runtime_DynamicCast(root->GetExtraData("CPA"), RTTI_NiExtraData, RTTI_BSConnectPoint__Parents);
		if(extraData)
		{
			for(UInt32 i = 0; i < extraData->points.count; i++)
			{
				BSConnectPoint::Parents::ConnectPoint * connectPoint = extraData->points[i];
				if(connectPoint)
				{
					ConnectPoint point;

					point.Set<BSFixedString>("parent", connectPoint->parent);
					point.Set<BSFixedString>("name", connectPoint->name);

					float yaw, pitch, roll;
					connectPoint->rot.GetEulerAngles(roll, pitch, yaw);
					yaw *= 180.0 / MATH_PI;
					pitch *= 180.0 / MATH_PI;
					roll *= 180.0 / MATH_PI;

					point.Set<float>("roll", roll);
					point.Set<float>("pitch", pitch);
					point.Set<float>("yaw", yaw);

					NiPoint3 localPos = connectPoint->pos;

					NiAVObject * parent = nullptr;
					if(connectPoint->parent == BSFixedString(""))
					{
						parent = root;
					}
					else
					{
						NiAVObject * child = root->GetObjectByName(&connectPoint->parent);
						if(child)
							parent = child;
					}

					NiPoint3 worldPos = localPos;
					if(parent) {
						worldPos = parent->m_worldTransform.rot.Transpose() * localPos + parent->m_worldTransform.pos;
						point.Set<float>("x", worldPos.x);
						point.Set<float>("y", worldPos.y);
						point.Set<float>("z", worldPos.z);
					} else {
						point.Set<float>("x", 0.0f);
						point.Set<float>("y", 0.0f);
						point.Set<float>("z", 0.0f);
					}

					point.Set<float>("scale", connectPoint->scale);

					point.Set<TESObjectREFR*>("object", nullptr);

					if(parent != root && refr->parentCell) {
						bhkWorld * world = CALL_MEMBER_FN(refr->parentCell, GetHavokWorld)();
						if(world) {
							TESObjectREFR * connected = GetObjectAtConnectPoint(refr, &worldPos, world, 8.0f);
							if(connected) {
								point.Set<TESObjectREFR*>("object", connected);
							}
						}
					}

					results.Push(&point);
				}
			}
		}		
		
		return results;
	}

	DECLARE_DELAY_FUNCTOR(F4SEConnectPointsFunctor, 0, GetConnectPointsLatent, TESObjectREFR, VMArray<ConnectPoint>);

	bool GetConnectPoints(VirtualMachine * vm, UInt32 stackId, TESObjectREFR* refr)
	{
		if(!refr)
			return false;

		F4SEDelayFunctorManagerInstance().Enqueue(new F4SEConnectPointsFunctor(GetConnectPointsLatent, vm, stackId, refr));
		return true;
	}

	bool TransmitConnectedPowerLatent(UInt32 stackId, TESObjectREFR * refr)
	{
		if(!refr)
			return false;

		NiNode * root = refr->GetObjectRootNode();
		if(!root) {
			return false;
		}

		BGSKeyword * keyword = nullptr;
		BGSDefaultObject * workshopItemDefault = (*g_defaultObjectMap)->GetDefaultObject("WorkshopItem");
		if(workshopItemDefault) {
			keyword = DYNAMIC_CAST(workshopItemDefault->form, TESForm, BGSKeyword);
		}
		
		// No workshop keyword is bad
		if(!keyword) {
			return false;
		}

		// Get the workshop by keyword
		TESObjectREFR * workshopRef = GetLinkedRef_Native(refr, keyword);
		if(!workshopRef) {
			return false;
		}

		// Workshop ref isn't a workshop!
		BSExtraData* extraDataWorkshop = workshopRef->extraDataList->GetByType(ExtraDataType::kExtraData_WorkshopExtraData);
		if(!extraDataWorkshop) {
			return false;
		}

		BSConnectPoint::Parents * extraData = (BSConnectPoint::Parents *)Runtime_DynamicCast(root->GetExtraData("CPA"), RTTI_NiExtraData, RTTI_BSConnectPoint__Parents);
		if(!extraData) {
			return false;
		}
		
		for(UInt32 i = 0; i < extraData->points.count; i++)
		{
			BSConnectPoint::Parents::ConnectPoint * connectPoint = extraData->points[i];
			if(!connectPoint)
				continue;

			NiPoint3 localPos = connectPoint->pos;
			NiAVObject * parent = nullptr;
			if(connectPoint->parent == "")
				parent = root;
			else
			{
				NiAVObject * child = root->GetObjectByName(&connectPoint->parent);
				if(child)
					parent = child;
			}

			NiPoint3 worldPos = localPos;
			if(parent) {
				worldPos = parent->m_worldTransform.rot.Transpose() * localPos + parent->m_worldTransform.pos;
			}

			float scale = connectPoint->scale;
			if(parent != root && refr->parentCell) {
				bhkWorld * world = CALL_MEMBER_FN(refr->parentCell, GetHavokWorld)();
				if(world) {
					TESObjectREFR * connected = GetObjectAtConnectPoint(refr, &worldPos, world, 8.0f);
					if(connected) {
						try // Probably wont make a difference but doesnt hurt to try
						{
							LinkPower_Internal(extraDataWorkshop, refr, connected, nullptr);
							LinkPower2_Internal(connected, extraDataWorkshop);
						}
						catch (...)
						{
							_MESSAGE("Power link error!");
						}
					}
				}
			}
		}

		LinkPower2_Internal(refr, extraDataWorkshop);
		return true;
	}

	DECLARE_DELAY_FUNCTOR(F4SETransmitConnectedPowerFunctor, 0, TransmitConnectedPowerLatent, TESObjectREFR, bool);

	bool TransmitConnectedPower(VirtualMachine * vm, UInt32 stackId, TESObjectREFR* refr)
	{
		if(!refr)
			return false;

		F4SEDelayFunctorManagerInstance().Enqueue(new F4SETransmitConnectedPowerFunctor(TransmitConnectedPowerLatent, vm, stackId, refr));
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
	f4seObjRegistry.RegisterClass<F4SEConnectPointsFunctor>();
	f4seObjRegistry.RegisterClass<F4SETransmitConnectedPowerFunctor>();

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
		new NativeFunction0<VMRefOrInventoryObj, BSFixedString>("GetDisplayName", "ObjectReference", papyrusObjectReference::GetDisplayName, vm));

	vm->RegisterFunction(
		new LatentNativeFunction0<TESObjectREFR, VMArray<TESForm*>>("GetInventoryItems", "ObjectReference", papyrusObjectReference::GetInventoryItems, vm));

	vm->RegisterFunction(
		new NativeFunction0<TESObjectREFR, float>("GetInventoryWeight", "ObjectReference", papyrusObjectReference::GetInventoryWeight, vm));

	vm->RegisterFunction(
		new LatentNativeFunction0<TESObjectREFR, VMArray<ConnectPoint>>("GetConnectPoints", "ObjectReference", papyrusObjectReference::GetConnectPoints, vm));

	vm->RegisterFunction(
		new LatentNativeFunction0<TESObjectREFR, bool>("TransmitConnectedPower", "ObjectReference", papyrusObjectReference::TransmitConnectedPower, vm));

	vm->SetFunctionFlags("ObjectReference", "AttachWire", IFunction::kFunctionFlag_NoWait);
	vm->SetFunctionFlags("ObjectReference", "GetInventoryItems", IFunction::kFunctionFlag_NoWait);
	vm->SetFunctionFlags("ObjectReference", "GetConnectPoints", IFunction::kFunctionFlag_NoWait);
	vm->SetFunctionFlags("ObjectReference", "TransmitConnectedPower", IFunction::kFunctionFlag_NoWait);

#ifdef _DEBUG
	vm->RegisterFunction(
		new LatentNativeFunction0<TESObjectREFR, void>("Scrap", "ObjectReference", papyrusObjectReference::Scrap, vm));

	vm->SetFunctionFlags("ObjectReference", "Scrap", IFunction::kFunctionFlag_NoWait);
#endif
}
