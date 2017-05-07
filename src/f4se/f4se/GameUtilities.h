#pragma once

#include "f4se_common/Relocation.h"

typedef void (* _CalculateCRC32)(UInt32 * out, UInt64 data, UInt32 previous);
extern RelocAddr <_CalculateCRC32> CalculateCRC32;
