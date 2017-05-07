#include "f4se/PapyrusUtilities.h"
#include "f4se/PapyrusVM.h"

UInt64 GetHandleFromObject(void * src, UInt32 typeID)
{
	VirtualMachine		* registry =	(*g_gameVM)->m_virtualMachine;
	IObjectHandlePolicy	* policy =		registry->GetHandlePolicy();

	return policy->Create(typeID, (void*)src);
}

void * GetObjectFromHandle(UInt64 handle, UInt32 typeID)
{
	VirtualMachine		* registry =	(*g_gameVM)->m_virtualMachine;
	IObjectHandlePolicy	* policy =		registry->GetHandlePolicy();

	if(handle == policy->GetInvalidHandle()) {
		return NULL;
	}

	return policy->Resolve(typeID, handle);
}
