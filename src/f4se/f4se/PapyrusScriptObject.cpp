#include "f4se/PapyrusScriptObject.h"

#include "f4se/PapyrusVM.h"
#include "f4se/PapyrusNativeFunctions.h"

#include "f4se/PapyrusEvents.h"

namespace papyrusScriptObject
{
	void RegisterForKey(VMObject * thisObject, UInt32 key)
	{
		if(!thisObject)
			return;
		g_inputKeyEventRegs.Register(key, thisObject->GetHandle());
	}

	void UnregisterForKey(VMObject * thisObject, UInt32 key)
	{
		if(!thisObject)
			return;
		g_inputKeyEventRegs.Unregister(key, thisObject->GetHandle());
	}

	void RegisterForControl(VMObject * thisObject, BSFixedString control)
	{
		if(!thisObject)
			return;
		g_inputControlEventRegs.Register(control, thisObject->GetHandle());
	}

	void UnregisterForControl(VMObject * thisObject, BSFixedString control)
	{
		if(!thisObject)
			return;
		g_inputControlEventRegs.Unregister(control, thisObject->GetHandle());
	}
}

void papyrusScriptObject::RegisterFuncs(VirtualMachine* vm)
{
	vm->RegisterFunction(
		new NativeFunction1 <VMObject, void, UInt32>("RegisterForKey", "ScriptObject", papyrusScriptObject::RegisterForKey, vm));

	vm->RegisterFunction(
		new NativeFunction1 <VMObject, void, UInt32>("UnregisterForKey", "ScriptObject", papyrusScriptObject::UnregisterForKey, vm));

	vm->RegisterFunction(
		new NativeFunction1 <VMObject, void, BSFixedString>("RegisterForControl", "ScriptObject", papyrusScriptObject::RegisterForControl, vm));

	vm->RegisterFunction(
		new NativeFunction1 <VMObject, void, BSFixedString>("UnregisterForControl", "ScriptObject", papyrusScriptObject::UnregisterForControl, vm));
}
