#pragma once

#include "f4se/GameTypes.h"

class NiTexture;

// 38
class BSShaderMaterial : public BSIntrusiveRefCounted
{
public:
	virtual ~BSShaderMaterial();

	virtual BSShaderMaterial	* Create(void);
	virtual void	Copy(BSShaderMaterial * other);
	virtual void	Unk_03(void);
	virtual void	Unk_04(void);	// Default material? returns global 1478D7F48
	virtual UInt32	GetType(void);
	virtual void	Unk_06(void);	// Returns 2?
	virtual void	Unk_07(void);
	virtual void	Unk_08(void);

	// vtable   00
	// refCount 08
	UInt64	unk10;	// 10
	UInt32	unk18;	// 18
	float	unk1C;	// 1C
	float	unk20;	// 20
	float	unk24;	// 24
	float	unk28;	// 28
	SInt32	unk2C;	// 2C
	UInt32	unk30;	// 30
	UInt32	pad34;	// 34
};

class BSEffectShaderMaterial : public BSShaderMaterial
{
public:
	virtual ~BSEffectShaderMaterial();
};

class BSWaterShaderMaterial : public BSShaderMaterial
{
public:
	virtual ~BSWaterShaderMaterial();
};

// E0
class BSLightingShaderMaterialBase : public BSShaderMaterial
{
public:
	enum ShaderTypes
	{
		kType_Default = 0,
		kType_Envmap,
		kType_Glowmap,
		kType_Parallax,
		kType_Face,
		kType_SkinTint,
		kType_HairTint,
		kType_ParallaxOcc,
		kType_Landscape,
		kType_LODLandscape,
		kType_Snow,
		kType_MultiLayerParallax,
		kType_Unknown12,
		kType_Unknown13,
		kType_Snow2,
		kType_Unknown15,
		kType_Eye,
		kType_Unknown17,
		kType_LODLandscape2,
		kType_Landscape2,
		kType_Dismemberment
	};

	virtual void	Unk_09();
	virtual void	Unk_0A();
	virtual void	Unk_0B();
	virtual void	Unk_0C();
	virtual void	Unk_0D();
	virtual void	Unk_0E();
	virtual void	Unk_0F();
	virtual void	Unk_10();
	virtual void	Unk_11();

	float	unk38;	// 38
	float	unk3C;	// 3C
	float	unk40;	// 40
	UInt32	unk44;	// 44
	NiTexture	* diffuse;	// 48
	NiTexture	* normal;	// 50
	NiTexture	* unk58;	// 58
	NiTexture	* specular;	// 60
	NiTexture	* unk68;	// 68
	NiTexture	* unk70;	// 70
	float		unk78;		// 78
	UInt32		unk7C;		// 7C
	UInt32		unk80;		// 80
	float		unk84;		// 84
	float		unk88;		// 88
	UInt16		unk8C;		// 8C
	UInt16		unk8E;		// 8E
	UInt32		unk90;		// 90
	UInt32		unk94;		// 94
	void		* unk98;	// 98
	UInt32		unkA0;		// A0
	float		unkA4;		// A4
	UInt32		unkA8;		// A8
	float		unkAC;		// AC
	float		unkB0;		// B0
	float		unkB4;		// B4
	float		unkB8;		// B8
	float		unkBC;		// BC
	float		unkC0;		// C0
	float		unkC4;		// C4
	float		unkC8;		// C8
	UInt32		unkCC;		// CC
	UInt32		unkD0;		// D0
	UInt32		unkD4;		// D4
	UInt32		unkD8;		// D8
	float		unkDC;		// DC
};

// E0
class BSLightingShaderMaterial : public BSLightingShaderMaterialBase
{
public:
	virtual ~BSLightingShaderMaterial();
};

// E8
class BSLightingShaderMaterialDismemberment : public BSLightingShaderMaterialBase
{
public:
	virtual ~BSLightingShaderMaterialDismemberment();

	NiTexture	* unkE0;	// E0
};

// F8
class BSLightingShaderMaterialEnvmap : public BSLightingShaderMaterialBase
{
public:
	virtual ~BSLightingShaderMaterialEnvmap();

	NiTexture	* envmap;	// E0
	NiTexture	* unkE8;	// E8
	float		unkF0;		// F0
	UInt16		unkF4;		// F4
	UInt16		padF6;		// F6
};

// 110
class BSLightingShaderMaterialEye : public BSLightingShaderMaterialBase
{
public:
	virtual ~BSLightingShaderMaterialEye();
};

// E8
class BSLightingShaderMaterialFace : public BSLightingShaderMaterialBase
{
public:
	virtual ~BSLightingShaderMaterialFace();

	NiTexture	* baseDiffuse;	// E0
};

// E8
class BSLightingShaderMaterialGlowmap : public BSLightingShaderMaterialBase
{
public:
	virtual ~BSLightingShaderMaterialGlowmap();

	NiTexture	* unkE0;	// E0
};

// F0
class BSLightingShaderMaterialHairTint : public BSLightingShaderMaterialBase
{
public:
	virtual ~BSLightingShaderMaterialHairTint();
	
	float	unkE0;	// E0
	float	unkE4;	// E4
	float	unkE8;	// E8
	UInt32	unkEC;	// EC
};

// 110
class BSLightingShaderMaterialLODLandscape : public BSLightingShaderMaterialBase
{
public:
	virtual ~BSLightingShaderMaterialLODLandscape();
};

// 1B0
class BSLightingShaderMaterialLandscape : public BSLightingShaderMaterialBase
{
public:
	virtual ~BSLightingShaderMaterialLandscape();
};

// 110
class BSLightingShaderMaterialMultiLayerParallax : public BSLightingShaderMaterialBase
{
public:
	virtual ~BSLightingShaderMaterialMultiLayerParallax();
};

// E8
class BSLightingShaderMaterialParallax : public BSLightingShaderMaterialBase
{
public:
	virtual ~BSLightingShaderMaterialParallax();

	NiTexture	* unkE0;	// E0
};

// F0
class BSLightingShaderMaterialParallaxOcc : public BSLightingShaderMaterialBase
{
public:
	virtual ~BSLightingShaderMaterialParallaxOcc();

	NiTexture	* unkE0;	// E0
	void		* unkE8;	// E8
};

// F0
class BSLightingShaderMaterialSkinTint : public BSLightingShaderMaterialBase
{
public:
	virtual ~BSLightingShaderMaterialSkinTint();

	float	unkE0;	// E0
	float	unkE4;	// E4
	float	unkE8;	// E8
	UInt32	unkEC;	// EC
};

// F0
class BSLightingShaderMaterialSnow : public BSLightingShaderMaterialBase
{
public:
	virtual ~BSLightingShaderMaterialSnow();

	float	unkE0;	// E0
	float	unkE4;	// E4
	float	unkE8;	// E8
	float	unkEC;	// EC
};
