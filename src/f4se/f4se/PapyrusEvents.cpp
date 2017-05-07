#include "f4se/PapyrusEvents.h"

RelocAddr <_SendCustomEvent> SendCustomEvent_Internal(0x013B81B0);
RelocAddr <_CallFunctionNoWait> CallFunctionNoWait_Internal(0x013B5720);
RelocAddr <_CallGlobalFunctionNoWait> CallGlobalFunctionNoWait_Internal(0x014307D0);

void CallGlobalFunctionNoWait(const BSFixedString & className, const BSFixedString & functionName, VMArray<VMVariable> & arguments)
{
	VirtualMachine * vm = (*g_gameVM)->m_virtualMachine;

	VMValue args;
	PackValue(&args, &arguments, vm);

	CallGlobalFunctionNoWait_Internal(vm, 0, 0, &className, &functionName, &args);
}
