#include "f4se/ScaleformState.h"

void SKSEGFxLogger::LogMessageVarg(UInt32 messageType, const char* fmt, va_list args)
{
	gLog.Log(IDebugLog::kLevel_Message, fmt, args);
}