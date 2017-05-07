#include "Hooks_Scaleform.h"
#include "f4se_common/Relocation.h"
#include "f4se_common/BranchTrampoline.h"
#include "xbyak/xbyak.h"
#include "ScaleformMovie.h"

void Hooks_Scaleform_Init()
{
	//
}

void ScaleformInitHook_Install(GFxMovieView * view)
{
	_MESSAGE("ScaleformInitHook");
}

void Hooks_Scaleform_Commit()
{
	RelocAddr <uintptr_t> ScaleformInitHook_Start(0x0256C020 + 0x188);

	struct ScaleformInitHook_Code : Xbyak::CodeGenerator {
		ScaleformInitHook_Code(void * buf) : Xbyak::CodeGenerator(4096, buf)
		{
			mov(eax, 1);
			lock(); xadd(ptr [rcx + 8], eax);
			jmp((void *)&ScaleformInitHook_Install);
		}
	};

	void * codeBuf = g_localTrampoline.StartAlloc();
	ScaleformInitHook_Code code(codeBuf);
	g_localTrampoline.EndAlloc(code.getCurr());

	g_branchTrampoline.Write5Call(ScaleformInitHook_Start, uintptr_t(code.getCode()));
}
