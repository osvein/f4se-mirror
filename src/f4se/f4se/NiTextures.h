#pragma once

#include "f4se/NiObjects.h"
#include "f4se/GameTypes.h"

class BSRenderData;

// 48
class NiTexture : public NiObject
{
public:
	BSFixedString	name;				// 10
	UInt32			unk18;				// 18
	UInt32			unk1C;				// 1C
	NiTexture		* prevTexture;		// 20
	NiTexture		* nextTexture;		// 28
	UInt64			unk30;				// 30
	BSRenderData	* rendererData;		// 38
	UInt16			unk40;				// 40
	UInt16			unk42;				// 42
	UInt32			unk44;				// 44
};

// 10
class BSTextureSet : public NiObject
{
public:
	virtual BSFixedString GetTextureFilenameFS(UInt32 typeEnum);
	virtual const char * GetTextureFilename(UInt32 typeEnum);
	virtual void Unk_2A();
	virtual void GetTexture(UInt32 typeEnum, NiPointer<NiTexture> & texture, bool unk1);
	virtual void	SetTextureFilename(UInt32 typeEnum, const char * path);
};

// 60
class BSShaderTextureSet : public BSTextureSet
{
public:
	void * unk10[(0x60 - 0x10) >> 3];	// 10

	MEMBER_FN_PREFIX(BSShaderTextureSet);
	DEFINE_MEMBER_FN(Copy, BSShaderTextureSet*, 0x004C1510);
};

typedef NiTexture * (* _CreateTexture)(const BSFixedString & name, UInt8 unk1); // unk1 is true on diffuses?
extern RelocAddr <_CreateTexture> CreateTexture;
