#pragma once

#include "f4se/NiObjects.h"

// 180
class bhkWorld : public NiObject
{
public:
	UInt64	unk10[(0x180 - 0x10) >> 3];
};

// 1B0
class bhkWorldM : public bhkWorld
{
public:
	UInt64	unk180[(0x1B0 - 0x180) >> 3];
};