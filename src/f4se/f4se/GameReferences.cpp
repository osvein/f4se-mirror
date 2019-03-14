#include "f4se/GameReferences.h"
#include "f4se/GameExtraData.h"
#include "f4se/GameRTTI.h"

// 1FA931E3C3B406454210A0EDC37BDD0C84C8C04A+6B
RelocPtr <PlayerCharacter*> g_player(0x05AA4358);

// 0BE70664D4DF11A3F88748D9CB45B23D0B4FD50C+2F
RelocAddr <_LookupREFRByHandle> LookupREFRByHandle(0x0000AB60);

// 4369DFCC9BCC88536EEB89E5A107B60941016295+26
RelocAddr <_CreateHandleByREFR> CreateHandleByREFR(0x0000A8A0);

// 3A53807E195FFAEA7AA0EF7FD42D84E4EA0B755A+D0
RelocPtr <UInt32> g_invalidRefHandle(0x038CCE04);

RelocAddr <_HasDetectionLOS> HasDetectionLOS(0x0135B560);

RelocAddr <_GetLinkedRef_Native> GetLinkedRef_Native(0x00480EE0);

RelocAddr <_SetLinkedRef_Native> SetLinkedRef_Native(0x00480F00);

RelocAddr <_MoveRefrToPosition> MoveRefrToPosition(0x013FE6C0);

UInt32 TESObjectREFR::CreateRefHandle(void)
{
	if (handleRefObject.GetRefCount() > 0)
	{
		UInt32 refHandle = 0;
		CreateHandleByREFR(&refHandle, this);
		return refHandle;
	}
	else
	{
		return *g_invalidRefHandle;
	}
}

bool Actor::GetEquippedExtraData(UInt32 slotIndex, ExtraDataList ** extraData)
{
	// Invalid slot id
	if (slotIndex >= ActorEquipData::kMaxSlots)
		return false;

	// This should be possible but check anyway
	if (!equipData)
		return false;

	// Make sure there is an item in this slot
	auto item = equipData->slots[slotIndex].item;
	if (!item)
		return false;

	if (!inventoryList)
		return false;

	// Find the equipped form from the inventory
	for (UInt32 i = 0; i < inventoryList->items.count; i++)
	{
		BGSInventoryItem inventoryItem;
		inventoryList->items.GetNthItem(i, inventoryItem);
		if (inventoryItem.form != item || !inventoryItem.stack)
			continue;

		// Search stacks for the equipped stack
		bool ret = inventoryItem.stack->Visit([&](BGSInventoryItem::Stack * stack)
		{
			if (stack->flags & BGSInventoryItem::Stack::kFlagEquipped)
			{
				ExtraDataList * stackDataList = stack->extraData;
				if (stackDataList) {
					(*extraData) = stackDataList;
				}

				return false;
			}

			return true;
		});
		if (!ret) // Stack found
			break;
	}

	return (*extraData) != nullptr;
}