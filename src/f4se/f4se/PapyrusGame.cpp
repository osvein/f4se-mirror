#include "f4se/PapyrusGame.h"

#include "f4se/PapyrusVM.h"
#include "f4se/PapyrusNativeFunctions.h"

#include "f4se/GameAPI.h"
#include "f4se/GameReferences.h"
#include "f4se/GameData.h"

DECLARE_STRUCT(PluginInfo, "Game");

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

	VMArray<PluginInfo> GetInstalledPlugins(StaticFunctionTag * base)
	{
		VMArray<PluginInfo> result;
		UInt8 modCount = (*g_dataHandler)->modList.loadedModCount;
		for (UInt32 i = 0; i < modCount; i++)
		{
			ModInfo * modInfo = (*g_dataHandler)->modList.loadedMods[i];
			
			PluginInfo info;
			info.Set<UInt32>("index", modInfo->modIndex);
			info.Set<BSFixedString>("name", modInfo->name);
			info.Set<BSFixedString>("author", modInfo->author.Get());
			info.Set<BSFixedString>("description", modInfo->description.Get());
			result.Push(&info);
		}

		return result;
	}

	VMArray<BSFixedString> GetPluginDependencies(StaticFunctionTag * base, BSFixedString plugin)
	{
		VMArray<BSFixedString> result;
		const ModInfo* pluginInfo = (*g_dataHandler)->LookupLoadedModByName(plugin);
		if(pluginInfo) {

			for(UInt32 i = 0; i < pluginInfo->numRefMods; i++)
			{
				ModInfo * modInfo = pluginInfo->refModInfo[i];
				if(modInfo) {
					BSFixedString modName(modInfo->name);
					result.Push(&modName);
				}
			}
		}

		return result;
	}
}

void papyrusGame::RegisterFuncs(VirtualMachine* vm)
{
	vm->RegisterFunction(
		new NativeFunction0 <StaticFunctionTag, TESObjectREFR*>("GetCurrentConsoleRef", "Game", papyrusGame::GetCurrentConsoleRef, vm));

	vm->RegisterFunction(
		new NativeFunction0 <StaticFunctionTag, VMArray<PluginInfo>>("GetInstalledPlugins", "Game", papyrusGame::GetInstalledPlugins, vm));

	vm->RegisterFunction(
		new NativeFunction1 <StaticFunctionTag, VMArray<BSFixedString>, BSFixedString>("GetPluginDependencies", "Game", papyrusGame::GetPluginDependencies, vm));
}
