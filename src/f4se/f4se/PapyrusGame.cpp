#include "f4se/PapyrusGame.h"

#include "f4se/PapyrusVM.h"
#include "f4se/PapyrusNativeFunctions.h"

#include "f4se/GameAPI.h"
#include "f4se/GameReferences.h"

namespace papyrusGame {

	TESObjectREFR * GetCurrentConsoleRef(StaticFunctionTag * base)
	{
		UInt32 handle = (*g_consoleHandle);
		TESObjectREFR * refr = NULL;
		if(handle != 0 && handle != (*g_invalidRefHandle)) {
			LookupREFRByHandle(&handle, &refr);
			return refr;
		}

		return nullptr;
	}
}

void papyrusGame::RegisterFuncs(VirtualMachine* vm)
{
	vm->RegisterFunction(
		new NativeFunction0 <StaticFunctionTag, TESObjectREFR*>("GetCurrentConsoleRef", "Game", papyrusGame::GetCurrentConsoleRef, vm));
}
