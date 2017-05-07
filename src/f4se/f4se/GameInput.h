#pragma once

#include "f4se_common/Utilities.h"
#include "f4se_common/Relocation.h"
#include "f4se/GameTypes.h"


class InputEvent
{
public:
	virtual ~InputEvent();
	UInt64 unk08[2];
	InputEvent* next;
	UInt64 unk20;
};
STATIC_ASSERT(sizeof(InputEvent) == 0x28);


class IDEvent : public InputEvent
{
public:
	BSFixedString	controlID;
};
STATIC_ASSERT(offsetof(IDEvent, controlID) == 0x28);
STATIC_ASSERT(sizeof(IDEvent) == 0x030);


// 40
class ButtonEvent : public IDEvent
{
	UInt32 unk28[4];
};
STATIC_ASSERT(sizeof(ButtonEvent) == 0x040);


// 30
class CharacterEvent : public InputEvent
{
	UInt64 unk28;
};
STATIC_ASSERT(sizeof(CharacterEvent) == 0x030);

// 40
class MouseMoveEvent : public IDEvent
{
	UInt32 unk28[4];
};

// 40
class CursorMoveEvent : public IDEvent
{
	UInt32 unk28[4];
};

// 48
class ThumbstickEvent : public IDEvent
{
	UInt32 unk20[6];
};
STATIC_ASSERT(sizeof(ThumbstickEvent) == 0x048);

// 30
class DeviceConnectEvent : public InputEvent
{
	UInt32 unk20[2];
};
STATIC_ASSERT(sizeof(DeviceConnectEvent) == 0x030);

// 40
class KinectEvent : public IDEvent
{
	UInt32 unk28[4];
};
STATIC_ASSERT(sizeof(KinectEvent) == 0x040);

// EF0
class InputEventTable
{
public:
	UInt64				unk00;
	ButtonEvent			buttonEvents[30];
	CharacterEvent		characterEvents[15];
	MouseMoveEvent		mouseMoveEvents[3];
	CursorMoveEvent		cursorMoveEvents[3];
	ThumbstickEvent		thumbstickEvents[6];
	DeviceConnectEvent	deviceConnectEvents[3];
	KinectEvent			kinectEvents[3];
};
//STATIC_ASSERT(offsetof(InputEventTable, mouseMoveEvents) == 0xA6C);
//STATIC_ASSERT(sizeof(InputEventTable) == 0xEF0);
extern RelocPtr <InputEventTable*> g_inputEventTable;

class BSInputDevice
{
public:
	virtual ~BSInputDevice();

	UInt64		unk008; // init to 0
	UInt64		unk010;
	UInt32		unk018; // padding?
	UInt32		unk01C; // init to 0
	UInt32		unk020;
	UInt32		unk024;
	void*		unk028;	// init to unk_1438CDC80 in 1.3.47
	UInt64		unk030;
	UInt64		unk038; // init to 0
	void*		unk040;
	UInt32		unk048;
	UInt32		unk04C; // init to 0
	UInt32		unk050;
	UInt32		unk054;
	void*		unk058;	// init to &unk_1438CDC84 in 1.3.47
	UInt64		unk060;
	UInt64		unk068; // init to 0
};
STATIC_ASSERT(offsetof(BSInputDevice, unk058) == 0x058);
STATIC_ASSERT(sizeof(BSInputDevice) == 0x70);

class BSKeyboardDevice : public BSInputDevice
{
public:
};
STATIC_ASSERT(sizeof(BSKeyboardDevice) == 0x70);

// 070
class BSVirtualKeyboardDevice : public BSKeyboardDevice
{

};
STATIC_ASSERT(sizeof(BSVirtualKeyboardDevice) == 0x70);


// 270
class BSPCKeyboardDevice : public BSKeyboardDevice
{
public:
	UInt64	unk070[(0x270-0x70)/sizeof(UInt64)];
};
STATIC_ASSERT(sizeof(BSPCKeyboardDevice) == 0x270);

class BSMouseDevice : public BSInputDevice
{

};
STATIC_ASSERT(sizeof(BSVirtualKeyboardDevice) == 0x70);

// 88
class BSPCMouseDevice : public BSMouseDevice
{
public:
	UInt64	unk070;
	UInt64	unk078;
	UInt64	unk080;
};
STATIC_ASSERT(sizeof(BSPCMouseDevice) == 0x88);

class BSGamepadDevice : public BSInputDevice
{
};


class BSGamepadDeviceDelegate : public BSGamepadDevice
{

};

class BSPCGamepadDevice : public BSGamepadDeviceDelegate
{

};

// B8
class BSPCGamepadDeviceHandler : public BSGamepadDevice
{
public:
	UInt64 unk070[(0xB8-0x70)/sizeof(UInt64)];
};
STATIC_ASSERT(sizeof(BSPCGamepadDeviceHandler) == 0xB8);

// 70
class BSPCVirtualKeyboardDevice : public BSVirtualKeyboardDevice
{


};
STATIC_ASSERT(sizeof(BSPCVirtualKeyboardDevice) == 0x70);


class InputManager
{
public:
	UInt64						unk00;
	BSPCKeyboardDevice*			keyboardDevice;			// 008
	BSPCMouseDevice*			mouseDevice;			// 010
	BSPCGamepadDeviceHandler*	gamepadHandler018;		// 018
	BSPCGamepadDeviceHandler*	gamepadHandler020;		// 020
	BSPCVirtualKeyboardDevice*	virtualKeyboardDevice;	// 028
};
extern RelocPtr <InputManager*> g_inputMgr;
