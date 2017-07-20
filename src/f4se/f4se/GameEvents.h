#pragma once

#include "f4se/GameTypes.h"

class Actor;
class TESObjectREFR;

enum EventResult
{
	kEvent_Continue = 0,
	kEvent_Abort
};

// 08
template <typename T>
class BSTEventSink
{
public:
	virtual ~BSTEventSink() { };
	virtual	EventResult	ReceiveEvent(T * evn, void * dispatcher) { return kEvent_Continue; }; // pure
//	void	** _vtbl;	// 00
};

struct BGSInventoryListEvent
{
	struct Event
	{

	};
};

struct MenuOpenCloseEvent
{

};

struct MenuModeChangeEvent
{

};

struct UserEventEnabledEvent
{

};

struct RequestHUDModesEvent
{

};

struct TESHitEvent
{

};

struct PerkEntryUpdatedEvent
{
	struct PerkValueEvents
	{

	};
};

struct ApplyColorUpdateEvent
{

};

struct BSMovementDataChangedEvent
{

};

struct BSTransformDeltaEvent
{

};

struct BSSubGraphActivationUpdate
{

};

struct bhkCharacterMoveFinishEvent
{

};

struct bhkNonSupportContactEvent
{

};

struct bhkCharacterStateChangeEvent
{

};

struct ChargenCharacterUpdateEvent
{

};

struct TESCombatEvent 
{
	TESObjectREFR	* source;	// 00
	TESObjectREFR	* target;	// 04
	UInt32			state;		// 08
};

struct TESDeathEvent
{
	TESObjectREFR	* source;	// 00
};

struct TESObjectLoadedEvent
{
	UInt32	formId;
	UInt8	loaded; // 01 - loaded, 00 - unloaded
};

struct TESLoadGameEvent
{

};

struct TESFurnitureEvent
{
	Actor			* actor;
	TESObjectREFR	* furniture;
	bool			isGettingUp;
};

struct TESInitScriptEvent
{
	TESObjectREFR * reference;
};

// 08
template <typename EventT>
class BSTEventDispatcher
{
public:
	typedef BSTEventSink<EventT> SinkT;

	bool AddEventSink(SinkT * sink)
	{
		SimpleLocker locker(&lock);

		// Check for duplicate first
		for (int i = 0; i < eventSinks.count; i++)
		{
			if(eventSinks[i] == sink)
				return false;
		}

		eventSinks.Insert(0, sink);
		return true;
	}

	bool RemoveEventSink(SinkT * sink)
	{
		SimpleLocker locker(&lock);

		for (int i = 0; i < eventSinks.count; i++)
		{
			if(eventSinks[i] == sink) {
				eventSinks.Remove(i);
				break;
			}
		}
	}

	SimpleLock			lock;				// 000
	tArray<SinkT*>		eventSinks;			// 008
	tArray<SinkT*>		addBuffer;			// 020
	tArray<SinkT*>		removeBuffer;		// 038
	bool				stateFlag;			// 050
	char				pad[3];
};

template<typename EventT>
BSTEventDispatcher<EventT> * GetEventDispatcher() { };

#define DECLARE_EVENT_DISPATCHER(Event, address) \
template<> inline BSTEventDispatcher<Event> * GetEventDispatcher() \
{ \
	typedef BSTEventDispatcher<Event> * (*_GetEventDispatcher)(); \
	RelocAddr<_GetEventDispatcher> GetDispatcher(address); \
	return GetDispatcher(); \
}

// A548D71D41C7C2E9D21B25E06730FB911FC31F47+B4 (struct+A0)
DECLARE_EVENT_DISPATCHER(TESCombatEvent, 0x0043FF30) // 0x0043FF30 GetInstance

// A548D71D41C7C2E9D21B25E06730FB911FC31F47+118 (struct+C8)
DECLARE_EVENT_DISPATCHER(TESDeathEvent, 0x00440390)

DECLARE_EVENT_DISPATCHER(TESObjectLoadedEvent, 0x00441010)

DECLARE_EVENT_DISPATCHER(TESLoadGameEvent, 0x00440CF0)

DECLARE_EVENT_DISPATCHER(TESInitScriptEvent, 0x00440BB0)

DECLARE_EVENT_DISPATCHER(TESFurnitureEvent, 0x00440A70)

// TESFormIDRemapEvent
// 04409D0

// TESFormDeleteEvent
// 0440930

