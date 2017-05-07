#pragma once

#include "f4se_common/Relocation.h"
#include "f4se/GameTypes.h"
#include "f4se/GameForms.h"


class DataHandler
{
public:
	UInt64						unk00;		// 00
	UnkArray					unk08;		// 08
	UnkArray					unk20;		// 20
	UnkArray					unk38;		// 38
	UnkArray					unk50;		// 50
	UnkFormArray				unk68[158];  // 68 // tArrays by FormID
	//UnkFormArray				unk68;		// 68 Form Type 0x0
	//UnkFormArray				unk80;		// 80 Form Type 0x1
	//UnkFormArray				unk98;		// 98 Form Type 0x2
	//UnkFormArray				unkB0;		// B0 Form Type 0x3
	//tArray<BGSKeywordForm*>		keywords;	// C8 Form Type 0x4
};

extern RelocPtr<DataHandler*> g_dataHandler;