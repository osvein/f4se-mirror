#pragma once

#include "f4se_common/Utilities.h"

class Heap
{
public:
	MEMBER_FN_PREFIX(Heap);
	DEFINE_MEMBER_FN(Allocate, void *, 0x01A7DC90, size_t size, size_t alignment, bool aligned);
	DEFINE_MEMBER_FN(Free, void, 0x01A7DF90, void * buf, bool aligned);
};

extern RelocPtr <Heap> g_mainHeap;

void * Heap_Allocate(size_t size);
void Heap_Free(void * ptr);

class ConsoleManager
{
public:
	MEMBER_FN_PREFIX(ConsoleManager);
	DEFINE_MEMBER_FN(VPrint, void, 0x011E4CB0, const char * fmt, va_list args);
	DEFINE_MEMBER_FN(Print, void, 0x011E4D40, const char * str);
};

extern RelocPtr <ConsoleManager *> g_console;

void Console_Print(const char * fmt, ...);
