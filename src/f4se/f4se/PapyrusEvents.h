#pragma once

#include "f4se/PapyrusVM.h"
#include "f4se/PapyrusValue.h"
#include "f4se/PapyrusArgs.h"

// This is the callback function to ScriptObject.SendCustomEvent, the high-level parameters were more convenient
// The only issue is you actually need a sending object and a CustomEvent on the sender's script, which can't be native
typedef void (* _SendCustomEvent)(VirtualMachine * vm, UInt64 unk1, VMIdentifier * sender, const BSFixedString * eventName, VMValue * args);
extern RelocAddr <_SendCustomEvent> SendCustomEvent_Internal;

// Same callback as ScriptObject.CallFunctionNoWait
typedef void (* _CallFunctionNoWait)(VirtualMachine * vm, UInt64 unk1, VMIdentifier * vmIdentifier, const BSFixedString * eventName, VMValue * args);
extern RelocAddr <_CallFunctionNoWait> CallFunctionNoWait_Internal;

// Same callback as Utility.CallGlobalFunctionNoWait
typedef void (* _CallGlobalFunctionNoWait)(VirtualMachine * vm, UInt64 unk1, UInt64 unk2, const BSFixedString * className, const BSFixedString * eventName, VMValue * args);
extern RelocAddr <_CallGlobalFunctionNoWait> CallGlobalFunctionNoWait_Internal;

template<class T>
void SendCustomEvent(T * sender, const BSFixedString & eventName, VMArray<VMVariable> & arguments)
{
	VirtualMachine * vm = (*g_gameVM)->m_virtualMachine;

	VMValue senderValue;
	PackValue(&senderValue, &sender, vm);
	VMValue args;
	PackValue(&args, &arguments, vm);

	if(senderValue.IsIdentifier()) {
		VMIdentifier * identifier = senderValue.data.id;
		if(identifier) {
			SendCustomEvent_Internal(vm, 0, identifier, &eventName, &args);
		}
	}
}

template<class T>
void CallFunctionNoWait(T * sender, const BSFixedString & eventName, VMArray<VMVariable> & arguments)
{
	VirtualMachine * vm = (*g_gameVM)->m_virtualMachine;

	VMValue senderValue;
	PackValue(&senderValue, &sender, vm);
	VMValue args;
	PackValue(&args, &arguments, vm);

	if(senderValue.IsIdentifier()) {
		VMIdentifier * identifier = senderValue.data.id;
		if(identifier) {
			CallFunctionNoWait_Internal(vm, 0, identifier, &eventName, &args);
		}
	}
}

void CallGlobalFunctionNoWait(const BSFixedString & className, const BSFixedString & functionName, VMArray<VMVariable> & arguments);
