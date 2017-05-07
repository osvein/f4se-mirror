#include "Hooks_SaveLoad.h"

#include "f4se_common/BranchTrampoline.h"
#include "f4se_common/Relocation.h"
#include "f4se_common/SafeWrite.h"
#include "xbyak/xbyak.h"
#include "f4se/PluginManager.h"

class BGSSaveLoadGame;

typedef void (* _SaveGame)(BGSSaveLoadGame * saveLoadMgr, const char * name, UInt8 unk1);
RelocAddr <_SaveGame> SaveGame(0x00C91A30);
_SaveGame SaveGame_Original = nullptr;

typedef bool (* _LoadGame)(BGSSaveLoadGame * saveLoadMgr, const char * name, UInt8 unk1);
RelocAddr <_LoadGame> LoadGame(0x00C91F30);
_LoadGame LoadGame_Original = nullptr;

void SaveGame_Hook(BGSSaveLoadGame * saveLoadMgr, const char * name, UInt8 unk1)
{
#ifdef _DEBUG
	_MESSAGE("Executing BGSSaveLoadGame::SaveGame_Hook. saveName: %s", name);
#endif

	PluginManager::Dispatch_Message(0, F4SEMessagingInterface::kMessage_PreSaveGame, (void*)name, strlen(name), NULL);
	SaveGame_Original(saveLoadMgr, name, unk1);
	PluginManager::Dispatch_Message(0, F4SEMessagingInterface::kMessage_PostSaveGame, (void*)name, strlen(name), NULL);
}

bool LoadGame_Hook(BGSSaveLoadGame * saveLoadMgr, const char * name, UInt8 unk1)
{
#ifdef _DEBUG
	_MESSAGE("Executing BGSSaveLoadGame::LoadGame_Hook. saveName: %s", name);
#endif

	PluginManager::Dispatch_Message(0, F4SEMessagingInterface::kMessage_PreLoadGame, (void*)name, strlen(name), NULL);
	bool result = LoadGame_Original(saveLoadMgr, name, unk1);
	PluginManager::Dispatch_Message(0, F4SEMessagingInterface::kMessage_PostLoadGame, (void*)result, 1, NULL);
	return result;
}

void Hooks_SaveLoad_Init()
{

}

void Hooks_SaveLoad_Commit()
{
	// hook save game
	{
		struct SaveGame_Code : Xbyak::CodeGenerator {
			SaveGame_Code(void * buf) : Xbyak::CodeGenerator(4096, buf)
			{
				Xbyak::Label retnLabel;

				mov(rax, rsp);
				mov(ptr[rax+0x18], r8b);

				jmp(ptr [rip + retnLabel]);

				L(retnLabel);
				dq(SaveGame.GetUIntPtr() + 7);
			}
		};

		void * codeBuf = g_localTrampoline.StartAlloc();
		SaveGame_Code code(codeBuf);
		g_localTrampoline.EndAlloc(code.getCurr());

		SaveGame_Original = (_SaveGame)codeBuf;

		g_branchTrampoline.Write6Branch(SaveGame.GetUIntPtr(), (uintptr_t)SaveGame_Hook);
	}

	// hook load game
	{
		struct LoadGame_Code : Xbyak::CodeGenerator {
			LoadGame_Code(void * buf) : Xbyak::CodeGenerator(4096, buf)
			{
				Xbyak::Label retnLabel;

				mov(ptr[rsp+0x18], rbx);

				jmp(ptr [rip + retnLabel]);

				L(retnLabel);
				dq(LoadGame.GetUIntPtr() + 5);
			}
		};

		void * codeBuf = g_localTrampoline.StartAlloc();
		LoadGame_Code code(codeBuf);
		g_localTrampoline.EndAlloc(code.getCurr());

		LoadGame_Original = (_LoadGame)codeBuf;

		g_branchTrampoline.Write5Branch(LoadGame.GetUIntPtr(), (uintptr_t)LoadGame_Hook);
	}
}
