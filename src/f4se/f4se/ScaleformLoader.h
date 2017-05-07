#pragma once

#include "f4se_common/Relocation.h"
#include "f4se_common/Utilities.h"

#include "f4se/ScaleformState.h"

class GImageInfoBase;

class GFxImageLoader : public GFxState
{
public:
	virtual GImageInfoBase*	LoadImage(const char * url) = 0;
};

class BSScaleformImageLoader : public GFxImageLoader
{
public:
	virtual ~BSScaleformImageLoader();
	virtual GImageInfoBase*	LoadImage(const char * url);
	virtual void Unk_02(void);
	virtual void Unk_03(void);
	virtual void Unk_04(void);
	virtual void Unk_06(void);
};

class BSScaleformManager
{
public:
	virtual ~BSScaleformManager();
	virtual void Unk_01(void); // Init image loader?

	UInt64					unk08;			// 08 - 0
	GFxStateBag				* stateBag;		// 10
	void					* unk18;		// 18
	void					* unk20;		// 20
	BSScaleformImageLoader	* imageLoader;	// 28
};

extern RelocPtr <BSScaleformManager *> g_scaleformManager;
