#include "Hooks_Papyrus.h"
#include "f4se_common/Relocation.h"
#include "f4se_common/BranchTrampoline.h"
#include "xbyak/xbyak.h"
#include "f4se/PapyrusVM.h"

RelocAddr <uintptr_t> RegisterPapyrusFunctions_Start(0x013870A0 + 0x461);

typedef std::list <F4SEPapyrusInterface::RegisterFunctions> PapyrusPluginList;
static PapyrusPluginList s_pap_plugins;

bool RegisterPapyrusPlugin(F4SEPapyrusInterface::RegisterFunctions callback)
{
	s_pap_plugins.push_back(callback);
	return true;
}

void Hooks_Papyrus_Init()
{

}

void RegisterPapyrusFunctions_Hook(VirtualMachine ** vmPtr)
{
	_MESSAGE("RegisterPapyrusFunctions_Hook");

	VirtualMachine * vm = (*vmPtr);

	// F4SE Registrations first

#if 0
	// Plugins
	for(PapyrusPluginList::iterator iter = s_pap_plugins.begin(); iter != s_pap_plugins.end(); ++iter)
	{
		(*iter)(vm);
	}
#endif
}

void Hooks_Papyrus_Commit()
{
	struct RegisterPapyrusFunctions_Code : Xbyak::CodeGenerator {
		RegisterPapyrusFunctions_Code(void * buf) : Xbyak::CodeGenerator(4096, buf)
		{
			call((void *)&RegisterPapyrusFunctions_Hook);
			mov(rcx, rbx);
			add(rsp, 0x20);
			pop(rbx);
			ret();
		}
	};

	void * codeBuf = g_localTrampoline.StartAlloc();
	RegisterPapyrusFunctions_Code code(codeBuf);
	g_localTrampoline.EndAlloc(code.getCurr());

	g_branchTrampoline.Write6Branch(RegisterPapyrusFunctions_Start, uintptr_t(code.getCode()));
}
