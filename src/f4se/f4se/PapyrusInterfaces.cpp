#include "f4se/PapyrusInterfaces.h"

// 909CA8A64F56E1A25E97D036B719034B5D045E46+28
RelocPtr <IObjectHandlePolicy *> g_objectHandlePolicy(0x066A3100);

void IComplexType::AddRef(void)
{
	InterlockedIncrement(&m_refCount);
}

void IComplexType::Release(void)
{
	if(!InterlockedDecrement(&m_refCount))
	{
		delete this;
	}
}
