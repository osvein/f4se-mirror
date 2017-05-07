#include "Hooks_Papyrus.h"
#include "f4se_common/Relocation.h"
#include "f4se_common/BranchTrampoline.h"
#include "xbyak/xbyak.h"

class VMClassRegistry;

void Hooks_Papyrus_Init()
{

}

void RegisterPapyrusFunctions_Hook(VMClassRegistry ** registryPtr)
{
	_MESSAGE("RegisterPapyrusFunctions_Hook");
}

void Hooks_Papyrus_Commit()
{
	RelocAddr <uintptr_t> RegisterPapyrusFunctions_Start(0x0132D050 + 0x449);

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
