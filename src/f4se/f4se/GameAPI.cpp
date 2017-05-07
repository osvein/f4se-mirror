#include "f4se/GameAPI.h"

// B53CEF7AA7FC153E48CDE9DBD36CD8242577E27F+11D
RelocPtr <Heap> g_mainHeap(0x03710800);

void * Heap_Allocate(size_t size)
{
	return CALL_MEMBER_FN(g_mainHeap, Allocate)(size, 0, false);
}

void Heap_Free(void * ptr)
{
	CALL_MEMBER_FN(g_mainHeap, Free)(ptr, false);
}

// CF40EA3DCB94FC3927A17CCA60198108D4742CA7+68
RelocPtr <ConsoleManager *> g_console(0x05724EB0);

void Console_Print(const char * fmt, ...)
{
	ConsoleManager * mgr = *g_console;
	if(mgr)
	{
		va_list args;
		va_start(args, fmt);

		CALL_MEMBER_FN(mgr, VPrint)(fmt, args);

		va_end(args);
	}
}
