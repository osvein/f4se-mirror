#include "f4se/PapyrusInterfaces.h"

// 3534F6C030F53F763010A91A605BE8A09C452C54+26
RelocPtr <IObjectHandlePolicy *> g_objectHandlePolicy(0x066577E8);

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
