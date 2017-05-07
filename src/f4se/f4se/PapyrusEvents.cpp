#include "f4se/PapyrusEvents.h"
#include "f4se/PapyrusUtilities.h"

RelocAddr <_SendCustomEvent> SendCustomEvent_Internal(0x013BB850);
RelocAddr <_CallFunctionNoWait> CallFunctionNoWait_Internal(0x013B8DC0);
RelocAddr <_CallGlobalFunctionNoWait> CallGlobalFunctionNoWait_Internal(0x01433E70);

RegistrationMapHolder<UInt32>								g_inputKeyEventRegs;
RegistrationMapHolder<BSFixedString>						g_inputControlEventRegs;
