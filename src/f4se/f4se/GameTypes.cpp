#include "f4se/GameTypes.h"

const char * BSString::Get(void)
{
	return m_data ? m_data : "";
}
