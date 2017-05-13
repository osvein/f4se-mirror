#include "f4se/PapyrusUI.h"

#include "f4se/PapyrusVM.h"
#include "f4se/PapyrusNativeFunctions.h"

#include "f4se/PapyrusDelayFunctors.h"

#include "f4se/Serialization.h"
#include "f4se/PapyrusSerialization.h"

#include "f4se/GameMenus.h"
#include "f4se/PapyrusScaleformAdapter.h"

namespace papyrusUI
{
	bool UI_LatentSet(UInt32 stackId, StaticFunctionTag *, BSFixedString menuName, BSFixedString varPath, VMVariable var)
	{
		IMenu * menu = (*g_ui)->GetMenu(&menuName);
		if(!menu)
			return false;

		auto movie = menu->movie;
		if(!movie)
			return false;

		auto root = movie->movieRoot;
		if(!root)
			return false;

		GFxValue value;
		PlatformAdapter::ConvertPapyrusValue(&value, &var.GetValue(), root);
		return root->SetVariable(varPath.c_str(), &value);
	}

	VMVariable UI_LatentGet(UInt32 stackId, StaticFunctionTag *, BSFixedString menuName, BSFixedString varPath)
	{
		VMVariable result;
		// Work done here is now done on the main thread
		IMenu * menu = (*g_ui)->GetMenu(&menuName);
		if(!menu)
			return result;

		auto movie = menu->movie;
		if(!movie)
			return result;

		auto root = movie->movieRoot;
		if(!root)
			return result;

		GFxValue value;
		root->GetVariable(&value, varPath.c_str());
		PlatformAdapter::ConvertScaleformValue(&result.GetValue(), &value, (*g_gameVM)->m_virtualMachine);
		return result;
	}

	VMVariable UI_LatentInvoke(UInt32 stackId, StaticFunctionTag *, BSFixedString menuName, BSFixedString varPath, VMArray<VMVariable> arguments)
	{
		VMVariable result;
		// Work done here is now done on the main thread
		IMenu * menu = (*g_ui)->GetMenu(&menuName);
		if(!menu)
			return result;

		auto movie = menu->movie;
		if(!movie)
			return result;

		auto root = movie->movieRoot;
		if(!root)
			return result;

		UInt32 argCount = arguments.Length();
		GFxValue * args = nullptr;
		if(argCount > 0)
		{
			args = new GFxValue[argCount];
			for(UInt32 i = 0; i < argCount; i++)
			{
				VMVariable var;
				arguments.Get(&var, i);
				PlatformAdapter::ConvertScaleformValue(&var.GetValue(), &args[i], (*g_gameVM)->m_virtualMachine);
			}
		}

		GFxValue value;
		root->Invoke(varPath, &value, args, argCount);
		PlatformAdapter::ConvertScaleformValue(&result.GetValue(), &value, (*g_gameVM)->m_virtualMachine);
		if(args)
			delete [] args;
		return result;
	}

	DECLARE_DELAY_FUNCTOR(F4SEUISetFunctor, 3, UI_LatentSet, StaticFunctionTag, bool, BSFixedString, BSFixedString, VMVariable);
	DECLARE_DELAY_FUNCTOR(F4SEUIGetFunctor, 2, UI_LatentGet, StaticFunctionTag, VMVariable, BSFixedString, BSFixedString);
	DECLARE_DELAY_FUNCTOR(F4SEUIInvokeFunctor, 3, UI_LatentInvoke, StaticFunctionTag, VMVariable, BSFixedString, BSFixedString, VMArray<VMVariable>);

	// These are the functions that enqueue the Latent functions
	bool Set(VirtualMachine * vm, UInt32 stackId, StaticFunctionTag * tag, BSFixedString menuName, BSFixedString varPath, VMVariable var)
	{
		F4SEDelayFunctorManagerInstance().Enqueue(new F4SEUISetFunctor(UI_LatentSet, vm, stackId, tag, menuName, varPath, var));
		return true;
	}

	bool Get(VirtualMachine * vm, UInt32 stackId, StaticFunctionTag * tag, BSFixedString menuName, BSFixedString varPath)
	{
		F4SEDelayFunctorManagerInstance().Enqueue(new F4SEUIGetFunctor(UI_LatentGet, vm, stackId, tag, menuName, varPath));
		return true;
	}

	bool Invoke(VirtualMachine * vm, UInt32 stackId, StaticFunctionTag * tag, BSFixedString menuName, BSFixedString varPath, VMArray<VMVariable> args)
	{
		F4SEDelayFunctorManagerInstance().Enqueue(new F4SEUIInvokeFunctor(UI_LatentInvoke, vm, stackId, tag, menuName, varPath, args));
		return true;
	}
}

void papyrusUI::RegisterFuncs(VirtualMachine* vm)
{
	F4SEObjectRegistry& f4seObjRegistry = F4SEObjectRegistryInstance();
	f4seObjRegistry.RegisterClass<F4SEUISetFunctor>();
	f4seObjRegistry.RegisterClass<F4SEUIGetFunctor>();
	f4seObjRegistry.RegisterClass<F4SEUIInvokeFunctor>();

	vm->RegisterFunction(
		new LatentNativeFunction3 <StaticFunctionTag, bool, BSFixedString, BSFixedString, VMVariable>("Set", "UI", papyrusUI::Set, vm));

	vm->RegisterFunction(
		new LatentNativeFunction2 <StaticFunctionTag, VMVariable, BSFixedString, BSFixedString>("Get", "UI", papyrusUI::Get, vm));

	vm->RegisterFunction(
		new LatentNativeFunction3 <StaticFunctionTag, VMVariable, BSFixedString, BSFixedString, VMArray<VMVariable>>("Invoke", "UI", papyrusUI::Invoke, vm));

	vm->SetFunctionFlags("UI", "Set", IFunction::kFunctionFlag_NoWait);
	vm->SetFunctionFlags("UI", "Get", IFunction::kFunctionFlag_NoWait);
	vm->SetFunctionFlags("UI", "Invoke", IFunction::kFunctionFlag_NoWait);
}
