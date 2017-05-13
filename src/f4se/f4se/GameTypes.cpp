#include "f4se/GameTypes.h"

const char * BSString::Get(void)
{
	return m_data ? m_data : "";
}

StringCache::Ref::Ref()
{
	CALL_MEMBER_FN(this, ctor)("");
}

StringCache::Ref::Ref(const char * buf)
{
	CALL_MEMBER_FN(this, ctor)(buf);
}

StringCache::Ref::Ref(const wchar_t * buf)
{
	CALL_MEMBER_FN(this, ctor_w)(buf);
}

void StringCache::Ref::Release()
{
	CALL_MEMBER_FN(this, Release)();
}

bool StringCache::Ref::operator==(const char * lhs) const
{
	Ref tmp(lhs);
	bool res = data == tmp.data;
	CALL_MEMBER_FN(&tmp, Release)();
	return res;
}

void SimpleLock::Lock(void)
{
	SInt32 myThreadID = GetCurrentThreadId();
	if (threadID == myThreadID) {
		lockCount++;
		return;
	}

	UInt32 spinCount = 0;
	while (InterlockedCompareExchange(&threadID, myThreadID, 0))
		Sleep(++spinCount > kFastSpinThreshold);

    lockCount = 1;
}

void SimpleLock::Release(void)
{
	if (--lockCount == 0)
		InterlockedCompareExchange(&threadID, 0, threadID);
}
