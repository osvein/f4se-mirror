#include "Hooks_Papyrus.h"
#include "f4se/GameThreads.h"
#include "f4se_common/Relocation.h"
#include "f4se_common/SafeWrite.h"
#include "xbyak/xbyak.h"
#include "f4se/PluginManager.h"

typedef UInt64 (* _InitGameDataThread_Run_Original)(InitGameDataThread * thread);
RelocAddr <_InitGameDataThread_Run_Original> InitGameDataThread_Run_Original(0x00D03220);

UInt64 InitGameDataRun_Hook(InitGameDataThread * thread)
{
	UInt64 res = InitGameDataThread_Run_Original(thread);
	PluginManager::Dispatch_Message(0, F4SEMessagingInterface::kMessage_DataLoaded, (void*)NULL, 0, NULL);
	return res;
}

void Hooks_Threads_Init()
{

}

void Hooks_Threads_Commit()
{
	RelocAddr <uintptr_t> InitGameDataThread_Run(0x02BED868 + 8); // InitGameDataThread vtable func1

	SafeWrite64(InitGameDataThread_Run.GetUIntPtr(), (UInt64)InitGameDataRun_Hook);
}
