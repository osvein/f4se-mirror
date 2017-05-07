#include "f4se_common/Utilities.h"
#include "f4se_common/SafeWrite.h"

#define LOG_INPUT_HOOK 0

typedef BOOL (WINAPI * _RegisterRawInputDevices)(RAWINPUTDEVICE * devices, UINT numDevices, UINT structSize);
_RegisterRawInputDevices Original_RegisterRawInputDevices = nullptr;

typedef UINT (WINAPI * _GetRawInputData)(HRAWINPUT rawinput, UINT cmd, void * data, UINT * dataSize, UINT headerSize);
_GetRawInputData Original_GetRawInputData = nullptr;

BOOL WINAPI Hook_RegisterRawInputDevices(RAWINPUTDEVICE * devices, UINT numDevices, UINT structSize)
{
#if LOG_INPUT_HOOK
	_MESSAGE("RegisterRawInputDevices %08X %08X", numDevices, structSize);
	for(UINT i = 0; i < numDevices; i++)
	{
		RAWINPUTDEVICE * dev = &devices[i];

		_MESSAGE("%04X %04X %08X %08X", dev->usUsagePage, dev->usUsage, dev->dwFlags, dev->hwndTarget);
	}
#endif

	BOOL result = Original_RegisterRawInputDevices(devices, numDevices, structSize);

	return result;
}

UINT WINAPI Hook_GetRawInputData(HRAWINPUT rawinput, UINT cmd, void * data, UINT * dataSize, UINT headerSize)
{
	UINT result = Original_GetRawInputData(rawinput, cmd, data, dataSize, headerSize);

#if LOG_INPUT_HOOK

	_MESSAGE("GetRawInputData %08X %08X %08X", cmd, *dataSize, headerSize);

	if(data)
	{
		RAWINPUT * input = (RAWINPUT *)data;

		_MESSAGE("hdr: %08X %08X %08X %08X", input->header.dwType, input->header.dwSize, input->header.hDevice, input->header.wParam);

		if(cmd == RID_INPUT)
		{
			switch(input->header.dwType)
			{
				case RIM_TYPEHID:
				{
					_MESSAGE("hid: %08X %08X", input->data.hid.dwSizeHid, input->data.hid.dwCount);
				}
				break;

				case RIM_TYPEKEYBOARD:
				{
					RAWKEYBOARD * kbd = &input->data.keyboard;

					_MESSAGE("kbd: %04X %04X %04X %04X %08X %08X",
						kbd->MakeCode, kbd->Flags, kbd->Reserved, kbd->VKey, kbd->Message, kbd->ExtraInformation);
				}
				break;

				case RIM_TYPEMOUSE:
				{
					RAWMOUSE * mse = &input->data.mouse;

					_MESSAGE("mse: %04X %08X %08X %d %d %08X",
						mse->usFlags, mse->ulButtons, mse->ulRawButtons, mse->lLastX, mse->lLastY, mse->ulExtraInformation);
				}
				break;
			}
		}
	}

#endif

	return result;
}

void Hooks_Input_Init()
{
	//
}

void Hooks_Input_Commit()
{
	void ** iat = (void **)GetIATAddr(GetModuleHandle(NULL), "user32.dll", "RegisterRawInputDevices");
	Original_RegisterRawInputDevices = (_RegisterRawInputDevices)*iat;
	SafeWrite64((uintptr_t)iat, (UInt64)Hook_RegisterRawInputDevices);

	iat = (void **)GetIATAddr(GetModuleHandle(NULL), "user32.dll", "GetRawInputData");
	Original_GetRawInputData = (_GetRawInputData)*iat;
	SafeWrite64((uintptr_t)iat, (UInt64)Hook_GetRawInputData);
}
