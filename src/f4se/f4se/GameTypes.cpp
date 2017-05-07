#include "f4se/GameTypes.h"

const char * BSString::Get(void)
{
	return m_data ? m_data : "";
}

StringCache::Ref::Ref(const char * buf)
{
	CALL_MEMBER_FN(this, ctor)(buf);
}

StringCache::RefW::RefW(const wchar_t * buf)
{
	CALL_MEMBER_FN(this, ctor)(buf);
}
