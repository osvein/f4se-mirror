#include "f4se/GameWorkshop.h"

RelocAddr <_LinkPower> LinkPower_Internal(0x001F6E20); // Power related natives
RelocAddr <_LinkPower2> LinkPower2_Internal(0x00201B10); // Usually paired with LinkPower
RelocAddr <_GetObjectAtConnectPoint> GetObjectAtConnectPoint(0x001FF360); // Acquires objects that are touching attach points
RelocAddr <_LinkPower3> LinkPower3_Internal(0x001F6890); // Wire related calls
RelocAddr <_LinkPower4> LinkPower4_Internal(0x00204610);
RelocAddr <_SetWireEndpoints> SetWireEndpoints_Internal(0x00200E50);
RelocAddr <_FinalizeWireLink> FinalizeWireLink(0x00200B50);
// B040A6E939E55D7B97BC6BE389FC17F455E63F06+83
RelocAddr <_ScrapReference> ScrapReference(0x002084C0);
