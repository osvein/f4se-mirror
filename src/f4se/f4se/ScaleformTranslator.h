#pragma once

#include "f4se/ScaleformState.h"

class GFxTranslator : public GFxState
{
public:
	virtual ~GFxTranslator();

	virtual void Unk_01(void);
	virtual void Unk_02(void);
	virtual void Unk_03(void);
	virtual void Unk_04(void);
};

// 50
class BSScaleformTranslator : public GFxTranslator
{
public:
	UInt64 unk18[(0x50 - 0x18) / 8];	// 18
};
