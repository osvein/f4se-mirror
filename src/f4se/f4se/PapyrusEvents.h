#pragma once

#include "f4se/PapyrusVM.h"
#include "f4se/PapyrusValue.h"
#include "f4se/PapyrusArgs.h"

#include "f4se/PluginAPI.h"
#include "f4se/Serialization.h"

#include <set>


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

template <typename D>
class EventRegistration
{
public:

	UInt64	handle;
	D		params;

	bool operator<(const EventRegistration & rhs) const	{ return handle < rhs.handle; }

	bool Save(const F4SESerializationInterface * intfc, UInt32 version) const
	{
		if (! intfc->WriteRecordData(&handle, sizeof(handle)))
			return false;
		if (! params.Save(intfc, version))
			return false;
		return true;
	}

	bool Load(const F4SESerializationInterface * intfc, UInt32 version)
	{
		if (! intfc->ReadRecordData(&handle, sizeof(handle)))
			return false;
		if (! params.Load(intfc, version))
			return false;
		return true;
	}

	void Dump(void)
	{
		_MESSAGE("> handle:\t%016I64x", handle);
		params.Dump();
	}
};

class NullParameters
{
public:
	bool Save(const F4SESerializationInterface * intfc, UInt32 version) const { return true; }
	bool Load(const F4SESerializationInterface * intfc, UInt32 version) { return true; }
	void Dump(void) {}
};

template <typename K, typename D = NullParameters>
class RegistrationMapHolder : public SafeDataHolder<std::map<K,std::set<EventRegistration<D>>>>
{
	typedef std::set<EventRegistration<D>>	RegSet;
	typedef std::map<K,RegSet>				RegMap;

public:

	void Register(K & key, UInt64 handle, D * params = NULL)
	{
		VirtualMachine		* registry =	(*g_gameVM)->m_virtualMachine;
		IObjectHandlePolicy	* policy =		registry->GetHandlePolicy();

		EventRegistration<D> reg;
		reg.handle = handle;
		if (params)
			reg.params = *params;

		Lock();

		if (m_data[key].insert(reg).second)
			policy->AddRef(handle);

		Release();
	}

	template <typename T>
	void Register(K & key, UInt32 type, T * classType, D * params = NULL)
	{
		VirtualMachine		* registry =	(*g_gameVM)->m_virtualMachine;
		IObjectHandlePolicy	* policy =		registry->GetHandlePolicy();

		EventRegistration<D> reg;
		reg.handle = policy->Create(type, (void *)classType);
		if (params)
			reg.params = *params;

#ifdef _DEBUG
		_MESSAGE("Executed PapyrusEvents::Register - %016llX", reg.handle);
#endif

		Lock();

		if (m_data[key].insert(reg).second)
			policy->AddRef(reg.handle);

		Release();
	}

	void Unregister(K & key, UInt64 handle)
	{
		VirtualMachine		* registry =	(*g_gameVM)->m_virtualMachine;
		IObjectHandlePolicy	* policy =		registry->GetHandlePolicy();

		EventRegistration<D> reg;
		reg.handle = handle;

		Lock();

		if (m_data[key].erase(reg))
			policy->Release(handle);

		Release();
	}

	template <typename T>
	void Unregister(K & key, UInt32 type, T * classType)
	{
		VirtualMachine		* registry =	(*g_gameVM)->m_virtualMachine;
		IObjectHandlePolicy	* policy =		registry->GetHandlePolicy();

		EventRegistration<D> reg;
		reg.handle = policy->Create(type, (void *)classType);

		Lock();

		if (m_data[key].erase(reg))
			policy->Release(reg.handle);

		Release();
	}

	void UnregisterAll(UInt64 handle)
	{
		VirtualMachine		* registry =	(*g_gameVM)->m_virtualMachine;
		IObjectHandlePolicy	* policy =		registry->GetHandlePolicy();

		EventRegistration<D> reg;
		reg.handle = handle;

		Lock();

		for (RegMap::iterator iter = m_data.begin(); iter != m_data.end(); ++iter)
			if (iter->second.erase(reg))
				policy->Release(handle);

		Release();
	}

	template <typename T>
	void UnregisterAll(UInt32 type, T * classType)
	{
		VirtualMachine		* registry =	(*g_gameVM)->m_virtualMachine;
		IObjectHandlePolicy	* policy =		registry->GetHandlePolicy();

		EventRegistration<D> reg;
		reg.handle = policy->Create(type, (void *)classType);

		Lock();

		for (RegMap::iterator iter = m_data.begin(); iter != m_data.end(); ++iter)
			if (iter->second.erase(reg))
				policy->Release(reg.handle);

		Release();
	}

	template <typename F>
	void ForEach(K & key, F & functor)
	{
		Lock();

		RegMap::iterator handles = m_data.find(key);

		if (handles != m_data.end())
			for (RegSet::iterator iter = handles->second.begin(); iter != handles->second.end(); ++iter)
				functor(*iter);

		Release();
	}

	void Clear(void)
	{
		Lock();
		m_data.clear();
		Release();
	}

	bool Save(const F4SESerializationInterface * intfc, UInt32 type, UInt32 version)
	{
		intfc->OpenRecord(type, version);

		Lock();

		for (RegMap::iterator iter = m_data.begin(); iter != m_data.end(); ++iter)
		{
			UInt32 numRegs = iter->second.size();

			if (!numRegs)
				continue;

			intfc->OpenRecord('REGS', version);

			// Key
			Serialization::WriteData(intfc, &iter->first);
			// Reg count
			intfc->WriteRecordData(&numRegs, sizeof(numRegs));
			// Regs
			for (RegSet::iterator elems = iter->second.begin(); elems != iter->second.end(); ++elems)
				elems->Save(intfc, version);
		}

		intfc->OpenRecord('REGE', version);

		Release();

		return true;
	}

	bool Load(const F4SESerializationInterface* intfc, UInt32 version)
	{
		UInt32 type, length, curVersion;

		while (intfc->GetNextRecordInfo(&type, &curVersion, &length))
		{
			switch (type)
			{
			case 'REGS':
				{
					K curKey;
					// Key
					if (! Serialization::ReadData(intfc, &curKey))
					{
						_MESSAGE("Error loading reg key");
						return false;
					}

					// Reg count
					UInt32 numRegs = 0;
					if (! intfc->ReadRecordData(&numRegs, sizeof(numRegs)))
					{
						_MESSAGE("Error loading reg count");
						return false;
					}

					for (UInt32 i = 0; i< numRegs; i++)
					{
						EventRegistration<D> reg;
						if (reg.Load(intfc, version))
						{
							VirtualMachine		* registry =	(*g_gameVM)->m_virtualMachine;
							IObjectHandlePolicy	* policy =		registry->GetHandlePolicy();

							UInt64 newHandle = 0;

							// Skip if handle is no longer valid.
							if (! intfc->ResolveHandle(reg.handle, &newHandle))
								continue;

							reg.handle = newHandle;

							Lock();

							if (m_data[curKey].insert(reg).second)
								policy->AddRef(reg.handle);

							Release();

						}
						else
						{
							_MESSAGE("Error loading regs");
							return false;
						}
					}

					break;
				}
			case 'REGE':
				{
					return true;
				}
			default:
				{
					_MESSAGE("Error loading unexpected chunk type %08X (%.4s)", type, &type);
					return false;
				}
			}
		}

		_MESSAGE("Missing record data for type %08X (%.4s)", type, &type);
		return false;
	}
};

template <typename D = NullParameters>
class RegistrationSetHolder : public SafeDataHolder<std::set<EventRegistration<D>>>
{
	typedef std::set<EventRegistration<D>>	RegSet;

public:

	void Register(UInt64 handle, D * params = NULL)
	{
		VirtualMachine		* registry =	(*g_gameVM)->m_virtualMachine;
		IObjectHandlePolicy	* policy =		registry->GetHandlePolicy();

		EventRegistration<D> reg;
		reg.handle = handle;
		if (params)
			reg.params = *params;

		Lock();

		if (m_data.insert(reg).second)
			policy->AddRef(handle);

		Release();
	}

	template <typename T>
	void Register(UInt32 type, T * classType, D * params = NULL)
	{
		VirtualMachine		* registry =	(*g_gameVM)->m_virtualMachine;
		IObjectHandlePolicy	* policy =		registry->GetHandlePolicy();

		EventRegistration<D> reg;
		reg.handle = policy->Create(type, (void *)classType);
		if (params)
			reg.params = *params;

		Lock();

		if (m_data.insert(reg).second)
			policy->AddRef(reg.handle);

		Release();
	}

	void Unregister(UInt64 handle)
	{
		VirtualMachine		* registry =	(*g_gameVM)->m_virtualMachine;
		IObjectHandlePolicy	* policy =		registry->GetHandlePolicy();

		EventRegistration<D> reg;
		reg.handle = handle;

		Lock();

		if (m_data.erase(reg))
			policy->Release(handle);

		Release();
	}

	template <typename T>
	void Unregister(UInt32 type, T * classType)
	{
		VirtualMachine		* registry =	(*g_gameVM)->m_virtualMachine;
		IObjectHandlePolicy	* policy =		registry->GetHandlePolicy();

		EventRegistration<D> reg;
		reg.handle = policy->Create(type, (void *)classType);

		Lock();

		if (m_data.erase(reg))
			policy->Release(reg.handle);

		Release();
	}

	template <typename F>
	void ForEach(F & functor)
	{
		Lock();

		for (RegSet::iterator iter = m_data.begin(); iter != m_data.end(); ++iter)
			functor(*iter);

		Release();
	}

	void Clear(void)
	{
		Lock();
		m_data.clear();
		Release();
	}

	bool Save(F4SESerializationInterface * intfc, UInt32 type, UInt32 version)
	{
		intfc->OpenRecord(type, version);

		Lock();

		UInt32 numRegs = m_data.size();

		// Reg count
		intfc->WriteRecordData(&numRegs, sizeof(numRegs));

		// Regs
		for (RegSet::iterator iter = m_data.begin(); iter != m_data.end(); ++iter)
			iter->Save(intfc, version);

		Release();

		return true;
	}

	bool Load(F4SESerializationInterface* intfc, UInt32 version)
	{
		// Reg count
		UInt32 numRegs = 0;
		if (! intfc->ReadRecordData(&numRegs, sizeof(numRegs)))
		{
			_MESSAGE("Error loading reg count");
			return false;
		}

		for (UInt32 i = 0; i < numRegs; i++)
		{
			EventRegistration<D> reg;
			if (reg.Load(intfc, version))
			{
				VirtualMachine		* registry =	(*g_gameVM)->m_virtualMachine;
				IObjectHandlePolicy	* policy =		registry->GetHandlePolicy();

				UInt64 newHandle = 0;

				// Skip if handle is no longer valid.
				if (! intfc->ResolveHandle(reg.handle, &newHandle))
					continue;

				reg.handle = newHandle;

				Lock();

				if (m_data.insert(reg).second)
					policy->AddRef(reg.handle);

				Release();

			}
			else
			{
				_MESSAGE("Error loading regs");
				return false;
			}
		}

		return true;
	}
};

extern RegistrationMapHolder<UInt32>							g_inputKeyEventRegs;
extern RegistrationMapHolder<BSFixedString>						g_inputControlEventRegs;


#define NUM_PARAMS 1
#include "PapyrusEventsDef.inl"

#define NUM_PARAMS 2
#include "PapyrusEventsDef.inl"

#define NUM_PARAMS 3
#include "PapyrusEventsDef.inl"

#define NUM_PARAMS 4
#include "PapyrusEventsDef.inl"

#define NUM_PARAMS 5
#include "PapyrusEventsDef.inl"

#define NUM_PARAMS 6
#include "PapyrusEventsDef.inl"

#define NUM_PARAMS 7
#include "PapyrusEventsDef.inl"

#define NUM_PARAMS 8
#include "PapyrusEventsDef.inl"

#define NUM_PARAMS 9
#include "PapyrusEventsDef.inl"

#define NUM_PARAMS 10
#include "PapyrusEventsDef.inl"
