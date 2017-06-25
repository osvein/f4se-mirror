#include "f4se/GameWorkshop.h"

// Power related natives
RelocAddr <_LinkPower> LinkPower_Internal(0x001F4FE0);

// Usually paired with LinkPower
RelocAddr <_LinkPower2> LinkPower2_Internal(0x001FFCD0);

// Acquires objects that are touching attach points
RelocAddr <_GetObjectAtConnectPoint> GetObjectAtConnectPoint(0x001FD520);

// Wire related calls
RelocAddr <_LinkPower3> LinkPower3_Internal(0x001F4A50);
RelocAddr <_LinkPower4> LinkPower4_Internal(0x002027D0);
RelocAddr <_SetWireEndpoints> SetWireEndpoints_Internal(0x001FF010);
RelocAddr <_FinalizeWireLink> FinalizeWireLink(0x001FED10);

RelocAddr <_ScrapReference> ScrapReference(0x00206640);