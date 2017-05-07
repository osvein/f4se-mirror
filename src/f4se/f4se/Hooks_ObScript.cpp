#include "Hooks_ObScript.h"
#include "ObScript.h"
#include "GameAPI.h"
#include "GameObjects.h"
#include "GameReferences.h"
#include "f4se_common/SafeWrite.h"
#include "f4se_common/f4se_version.h"
#include "f4se/GameForms.h"
#include "f4se/GameData.h"

// currently ForceRSXCrash, could also use ToggleESRAM and several others
static ObScriptCommand * s_hijackedCommand = nullptr;

void Hooks_ObScript_Init()
{
	// instead of hooking the entire classic scripting system, we're just hijacking some unused commands

	for(ObScriptCommand * iter = g_firstConsoleCommand; iter->opcode < kObScript_NumConsoleCommands; ++iter)
	{
		if(!strcmp(iter->longName, "ForceRSXCrash"))
		{
			s_hijackedCommand = iter;
			break;
		}
	}
}

bool GetF4SEVersion_Execute(void * paramInfo, void * scriptData, TESObjectREFR * thisObj, void * containingObj, void * scriptObj, void * locals, double * result, void * opcodeOffsetPtr)
{
	Console_Print("F4SE version: %d.%d.%d, release idx %d, runtime %08X",
		F4SE_VERSION_INTEGER, F4SE_VERSION_INTEGER_MINOR, F4SE_VERSION_INTEGER_BETA,
		F4SE_VERSION_RELEASEIDX, RUNTIME_VERSION);


	DataHandler* theDH = *g_dataHandler;

	// walk all weapons (formtype 0x2b)
	//tArray<TESObjectWEAP*>& weapons = theDH->arrWEAP;
	//for (UInt64 n=0; n < weapons.count; n++) {
	//	TESObjectWEAP* pWeap = weapons[n];
	//	char* name = pWeap->fullName.name->Get();
	//}


	//tArray<BGSKeyword*>& keywords = theDH->arrKYWD; 
	//_MESSAGE("Keywords:");
	//for (UInt64 n=0; n < keywords.count; n++) {
	//	BGSKeyword* pForm = keywords[n];
	//	_MESSAGE("%s", pForm->keyword->Get());
	//}
	
	return true;
}









void Hooks_ObScript_Commit()
{
	ObScriptCommand cmd = *s_hijackedCommand;

	cmd.longName = "GetF4SEVersion";
	cmd.shortName = "f4se";
	cmd.helpText = "";
	cmd.needsParent = 0;
	cmd.numParams = 0;
	cmd.execute = GetF4SEVersion_Execute;
	cmd.flags = 0;

	SafeWriteBuf((uintptr_t)s_hijackedCommand, &cmd, sizeof(cmd));
}
