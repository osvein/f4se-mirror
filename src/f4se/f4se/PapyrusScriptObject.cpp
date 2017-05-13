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

		g_inputKeyEventRegs.Register(key, thisObject->GetHandle(), thisObject->GetObjectType());
	}

	void UnregisterForKey(VMObject * thisObject, UInt32 key)
	{
		if(!thisObject)
			return;
		g_inputKeyEventRegs.Unregister(key, thisObject->GetHandle(), thisObject->GetObjectType());
	}

	void RegisterForControl(VMObject * thisObject, BSFixedString control)
	{
		if(!thisObject)
			return;
		g_inputControlEventRegs.Register(control, thisObject->GetHandle(), thisObject->GetObjectType());
	}

	void UnregisterForControl(VMObject * thisObject, BSFixedString control)
	{
		if(!thisObject)
			return;
		g_inputControlEventRegs.Unregister(control, thisObject->GetHandle(), thisObject->GetObjectType());
	}

	void RegisterForExternalEvent(VMObject * thisObject, BSFixedString eventName, BSFixedString callback)
	{
		if(!thisObject)
			return;

		ExternalEventParameters params;
		params.callbackName = callback;
		g_externalEventRegs.Register(eventName, thisObject->GetHandle(), thisObject->GetObjectType(), &params);
	}

	void UnregisterForExternalEvent(VMObject * thisObject, BSFixedString eventName)
	{
		if(!thisObject)
			return;
		g_externalEventRegs.Unregister(eventName, thisObject->GetHandle(), thisObject->GetObjectType());
	}

	void RegisterForCameraState(VMObject * thisObject)
	{
		if(!thisObject)
			return;

		g_cameraEventRegs.Register(thisObject->GetHandle(), thisObject->GetObjectType());
	}

	void UnregisterForCameraState(VMObject * thisObject)
	{
		if(!thisObject)
			return;

		g_cameraEventRegs.Unregister(thisObject->GetHandle(), thisObject->GetObjectType());
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

	vm->RegisterFunction(
		new NativeFunction2 <VMObject, void, BSFixedString, BSFixedString>("RegisterForExternalEvent", "ScriptObject", papyrusScriptObject::RegisterForExternalEvent, vm));

	vm->RegisterFunction(
		new NativeFunction1 <VMObject, void, BSFixedString>("UnregisterForExternalEvent", "ScriptObject", papyrusScriptObject::UnregisterForExternalEvent, vm));

	vm->RegisterFunction(
		new NativeFunction0 <VMObject, void>("RegisterForCameraState", "ScriptObject", papyrusScriptObject::RegisterForCameraState, vm));

	vm->RegisterFunction(
		new NativeFunction0 <VMObject, void>("UnregisterForCameraState", "ScriptObject", papyrusScriptObject::UnregisterForCameraState, vm));
}
