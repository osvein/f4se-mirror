#include "f4se/PapyrusEvents.h"

RelocAddr <_SendCustomEvent> SendCustomEvent_Internal(0x013B78D0);
RelocAddr <_CallFunctionNoWait> CallFunctionNoWait_Internal(0x013B4E40);
RelocAddr <_CallGlobalFunctionNoWait> CallGlobalFunctionNoWait_Internal(0x0142FEF0);

void CallGlobalFunctionNoWait(const BSFixedString & className, const BSFixedString & functionName, VMArray<VMVariable> & arguments)
{
	VirtualMachine * vm = (*g_gameVM)->m_virtualMachine;

	VMValue args;
	PackValue(&args, &arguments, vm);

	CallGlobalFunctionNoWait_Internal(vm, 0, 0, &className, &functionName, &args);
}
