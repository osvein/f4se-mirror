#pragma once

class VirtualMachine;
struct StaticFunctionTag;
class TESObjectREFR;

#include "f4se/GameTypes.h"

namespace papyrusObjectReference
{
	void RegisterFuncs(VirtualMachine* vm);
}

typedef TESObjectREFR* (* _PlaceAtMe_Native)(VirtualMachine* vm, UInt32 stackId, TESObjectREFR** target, TESForm* form, SInt32 count, bool bForcePersist, bool bInitiallyDisabled, bool bDeleteWhenAble);
extern RelocAddr<_PlaceAtMe_Native> PlaceAtMe_Native;
