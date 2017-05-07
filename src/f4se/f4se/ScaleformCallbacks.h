#pragma once

#include "f4se/ScaleformTypes.h"

class GFxFunctionHandler : public GRefCountBase
{
public:
	GFxFunctionHandler();
	virtual ~GFxFunctionHandler();
};

class BSGFxFunctionHandler : public GFxFunctionHandler
{
public:
	virtual ~BSGFxFunctionHandler();
};