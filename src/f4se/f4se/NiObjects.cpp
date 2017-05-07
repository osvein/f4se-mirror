#include "f4se/NiObjects.h"
#include "f4se/NiExtraData.h"

void NiRefObject::IncRef(void)
{
	InterlockedIncrement(&m_uiRefCount);
}

bool NiRefObject::Release(void)
{
	return InterlockedDecrement(&m_uiRefCount) == 0;
}

void NiRefObject::DecRef(void)
{
	if(Release())
		DeleteThis();
}

bool NiObjectNET::HasExtraData(const BSFixedString & name)
{
	if(!m_extraData)
		return false;

	SimpleLocker locker(&m_extraData->lock);
	for(UInt32 i = 0; i < m_extraData->count; i++)
	{
		NiExtraData * data = m_extraData->entries[i];
		if(data->m_name == name)
			return true;
	}

	return false;
}

bool NiObjectNET::AddExtraData(NiExtraData * extraData)
{
	return CALL_MEMBER_FN(this, Internal_AddExtraData)(extraData);
}
