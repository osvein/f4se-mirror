#pragma once

#include "f4se/GameTypes.h"
#include "f4se/NiTypes.h"

class NiTexture;
class BSTextureSet;
class NiStream;
class BSShaderData;

// 38
class BSShaderMaterial : public BSIntrusiveRefCounted
{
public:
	virtual ~BSShaderMaterial();

	virtual BSShaderMaterial	* Create();
	virtual void	CopyMembers(const BSShaderMaterial * other);
	virtual void	ComputeCRC32(UInt32, bool);
	virtual BSShaderMaterial	* GetDefault();
	virtual UInt32	GetType();
	virtual void	Unk_06(void);	// Returns 2?
	virtual void	Compare(const BSShaderMaterial & other);
	virtual void	IsCopy(const BSShaderMaterial * other);

	NiPoint2	textCoordOffset[2];	// 10
	NiPoint2	textCoordScale[2];	// 20
	UInt32		uiHashKey;			// 30
	UInt32		uiUniqueCode;		// 34
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

	virtual bool	IsLightingShaderMaterialEnvmap();
	virtual void	ClearTextures();
	virtual void	GetTextures(NiTexture ** textures);	// Returns textures into this array
	virtual void	SaveBinary(NiStream * stream);
	virtual void	LoadBinary(NiStream * stream);
	virtual void	OnPrefetchTextures();
	virtual void	OnLoadTextureSet1();
	virtual void	OnLoadTextureSet(const BSTextureSet *);
	virtual void	DoReceiveValuesFromRootMaterial(const BSShaderData &);

	NiColor					kSpecularColor;					// 38
	NiPointer<NiTexture>	spDiffuseTexture;				// 48
	NiPointer<NiTexture>	spNormalTexture;				// 50
	NiPointer<NiTexture>	spRimSoftLightingTexture;		// 58
	NiPointer<NiTexture>	spSmoothnessSpecMaskTexture;	// 60
	NiPointer<NiTexture>	spLookupTexture;				// 68
	UInt32					eTextureClampMode;				// 70
	UInt32					unk74;							// 74
	NiPointer<BSTextureSet>	spTextureSet;					// 78
	float					fMaterialAlpha;					// 80
	float					fRefractionPower;				// 84
	float					fSmoothness;					// 88
	float					fSpecularColorScale;			// 8C
	float					fFresnelPower;					// 90
	float					fWetnessControl_SpecScale;		// 94
	float					fWetnessControl_SpecPowerScale;	// 98
	float					fWetnessControl_SpecMin;		// 9C
	float					fWetnessControl_EnvMapScale;	// A0
	float					fWetnessControl_FresnelPower;	// A4
	float					fWetnessControl_Metalness;		// A8
	float					fSubsurfaceLightRolloff;		// AC
	float					fRimLightPower;					// B0
	float					fBackLightPower;				// B4
	float					fLookupScale;					// B8
	BSNonReentrantSpinLock	LoadTextureSetLock;				// BC
};

// D0
class BSLightingShaderMaterial : public BSLightingShaderMaterialBase
{
public:
	virtual ~BSLightingShaderMaterial();
};

// C8
class BSLightingShaderMaterialDismemberment : public BSLightingShaderMaterialBase
{
public:
	virtual ~BSLightingShaderMaterialDismemberment();

	NiPointer<NiTexture>	unkC0;	// C0
};

// D8
class BSLightingShaderMaterialEnvmap : public BSLightingShaderMaterialBase
{
public:
	virtual ~BSLightingShaderMaterialEnvmap();

	NiPointer<NiTexture> envmap;	// C0
	NiPointer<NiTexture> unkC8;		// C8
	float				unkD0;		// D0
	UInt16				unkD4;		// D4
	UInt16				padD6;		// D6
};

// 110
class BSLightingShaderMaterialEye : public BSLightingShaderMaterialBase
{
public:
	virtual ~BSLightingShaderMaterialEye();
};

// C8
class BSLightingShaderMaterialFace : public BSLightingShaderMaterialBase
{
public:
	virtual ~BSLightingShaderMaterialFace();

	NiPointer<NiTexture>	baseDiffuse;	// C0
};

// C8
class BSLightingShaderMaterialGlowmap : public BSLightingShaderMaterialBase
{
public:
	virtual ~BSLightingShaderMaterialGlowmap();

	NiPointer<NiTexture>	unkC0;	// C0
};

// D0
class BSLightingShaderMaterialHairTint : public BSLightingShaderMaterialBase
{
public:
	virtual ~BSLightingShaderMaterialHairTint();
	
	NiColorA	kTintColor;	// C0
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

// C8
class BSLightingShaderMaterialParallax : public BSLightingShaderMaterialBase
{
public:
	virtual ~BSLightingShaderMaterialParallax();

	NiPointer<NiTexture> unkC0;	// C0
};

// D0
class BSLightingShaderMaterialParallaxOcc : public BSLightingShaderMaterialBase
{
public:
	virtual ~BSLightingShaderMaterialParallaxOcc();

	NiPointer<NiTexture> unkC0;		// C0
	void				* unkC8;	// C8
};

// D0
class BSLightingShaderMaterialSkinTint : public BSLightingShaderMaterialBase
{
public:
	virtual ~BSLightingShaderMaterialSkinTint();

	NiColorA	kTintColor;	// C0
};

// D0
class BSLightingShaderMaterialSnow : public BSLightingShaderMaterialBase
{
public:
	virtual ~BSLightingShaderMaterialSnow();

	float	unkC0;	// C0
	float	unkC4;	// C4
	float	unkC8;	// C8
	float	unkCC;	// CC
};
