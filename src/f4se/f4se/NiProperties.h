#pragma once

#include "f4se/NiObjects.h"

class BSShaderMaterial;

class NiProperty : public NiObjectNET
{
public:
	virtual ~NiProperty();

	enum
	{
		kTypeAlpha = 0,
		kTypeShade = 1
	};

	virtual SInt32 GetType(void);
};

// 30
class NiAlphaProperty : public NiProperty
{
public:
	virtual ~NiAlphaProperty();

	UInt16	alphaFlags;		// 28
	UInt8	alphaThreshold;	// 2A
};

// 28
class NiShadeProperty : public NiProperty
{
public:
	virtual ~NiShadeProperty();

	virtual void Unk_23(void);
};

// 68
class BSShaderProperty : public NiShadeProperty
{
public:
	float	unk28;	// 28
	float	unk2C;	// 2C
	UInt64	unk30;	// 30
	UInt64	unk38;	// 38
	UInt64	unk40;	// 40
	NiNode	* root;	// 48
	UInt64	unk50;	// 50
	BSShaderMaterial	* shaderMaterial;	// 58
	UInt32	unk60;	// 60
	float	unk64;	// 64
};

// E8
class BSLightingShaderProperty : public BSShaderProperty
{
public:
	UInt64	unk68;	// 68
	UInt64	unk70;	// 70
	UInt64	unk78;	// 78
	float	unk80;	// 80
	float	unk84;	// 84
	float	unk88;	// 88
	float	unk8C;	// 8C
	UInt64	unk90;	// 90
	UInt64	unk98;	// 98
	UInt64	unkA0;	// A0
	UInt64	unkA8;	// A8
	UInt64	unkB0;	// B0

	struct UnkData
	{
		UInt32	unk00;	// 00
		UInt32	unk04;	// 04
		UInt32	unk08;	// 08
	};

	UnkData	* unkB8;	// B8
	void	* unkC0;	// C0
	float	unkC8;		// C8
	UInt32	unkCC;		// CC
	float	unkD0;		// D0
	float	unkD4;		// D4
	SInt32	unkD8;		// D8
	UInt32	unkDC;		// DC
	UInt32	unkE0;		// E0
	UInt32	unkE4;		// E4

	MEMBER_FN_PREFIX(BSLightingShaderProperty);
	DEFINE_MEMBER_FN(MakeValidForRendering, void, 0x026E3720, BSGeometry * geometry); // previously InvalidateShader
	DEFINE_MEMBER_FN(ApplyMaterial, bool, 0x00053690); // Calls BSShaderProperty::SetMaterial
	DEFINE_MEMBER_FN(LoadTextureSet, void, 0x026E3DB0, UInt32 unk1); // unk1 usually 0, called after material Releases textures (previously InvalidateTextures)
};
STATIC_ASSERT(sizeof(BSLightingShaderProperty) == 0xE8);
