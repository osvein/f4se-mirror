#include "f4se/GameExtraData.h"

bool ExtraDataList::PresenceBitfield::HasType(UInt32 type) const
{
	UInt32 index = (type >> 3);
	UInt8 bitMask = 1 << (type % 8);
	return (bits[index] & bitMask) != 0;
}

bool ExtraDataList::HasType(UInt32 type) const
{
	return (m_presence) ? m_presence->HasType(type) : false;
}

void ExtraDataList::MarkType(UInt32 type, bool bCleared)
{
	UInt32 index = (type >> 3);
	UInt8 bitMask = 1 << (type % 8);
	UInt8& flag = m_presence->bits[index];
	if (bCleared) {
		flag &= ~bitMask;
	} else {
		flag |= bitMask;
	}
}

bool ExtraDataList::Remove(UInt8 type, BSExtraData* toRemove)
{
	if (!toRemove) return false;

	if (HasType(type)) {
		bool bRemoved = false;
		if (m_data == toRemove) {
			m_data = m_data->next;
			bRemoved = true;
		}

		for (BSExtraData* traverse = m_data; traverse; traverse = traverse->next) {
			if (traverse->next == toRemove) {
				traverse->next = toRemove->next;
				bRemoved = true;
				break;
			}
		}
		if (bRemoved) {
			MarkType(type, true);
		}
		return true;
	}

	return false;
}

bool ExtraDataList::Add(UInt8 type, BSExtraData* toAdd)
{
	if (!toAdd || HasType(type)) return false;

	BSExtraData* next = m_data;
	m_data = toAdd;
	toAdd->next = next;
	MarkType(type, false);
	return true;
}

BSExtraData* ExtraDataList::GetByType(UInt32 type) const
{
	if (!HasType(type))
		return NULL;

	for(BSExtraData * traverse = m_data; traverse; traverse = traverse->next) {
		if(traverse->type == type)
			return traverse;
	}
	return NULL;
}

#ifdef _DEBUG
#include "f4se_common\Utilities.h"

void ExtraDataList::Dump()
{
	for(BSExtraData * traverse = m_data; traverse; traverse = traverse->next)
	{
		gLog.Indent();
		_MESSAGE("%s", GetObjectClassName(traverse));
		gLog.Outdent();
	}
}
#endif
