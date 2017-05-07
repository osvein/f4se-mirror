#pragma once

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
	virtual ~BSTEventSink();
	virtual	EventResult	ReceiveEvent(T * evn, void * dispatcher); // pure
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
