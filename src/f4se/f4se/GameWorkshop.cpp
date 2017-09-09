#include "f4se/GameWorkshop.h"

// Power related natives
RelocAddr <_LinkPower> LinkPower_Internal(0x001F6D80);

// Usually paired with LinkPower
RelocAddr <_LinkPower2> LinkPower2_Internal(0x00201A70);

// Acquires objects that are touching attach points
RelocAddr <_GetObjectAtConnectPoint> GetObjectAtConnectPoint(0x001FF2C0);

// Wire related calls
RelocAddr <_LinkPower3> LinkPower3_Internal(0x001F67F0);
RelocAddr <_LinkPower4> LinkPower4_Internal(0x00204570);
RelocAddr <_SetWireEndpoints> SetWireEndpoints_Internal(0x00200DB0);
RelocAddr <_FinalizeWireLink> FinalizeWireLink(0x00200AB0);

RelocAddr <_ScrapReference> ScrapReference(0x002083E0);