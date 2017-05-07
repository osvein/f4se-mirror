#pragma once

#include "f4se_common/Utilities.h"

class VMState;
class VMValue;

// VMState+38: UInt32 numArgs

class VMArgList
{
public:
	MEMBER_FN_PREFIX(VMArgList);
	DEFINE_MEMBER_FN(GetOffset, UInt32, 0x025CE0E0, VMState * state);
	DEFINE_MEMBER_FN(Get, VMValue *, 0x0025CE140, VMState * state, UInt32 idx, UInt32 offset);
};
