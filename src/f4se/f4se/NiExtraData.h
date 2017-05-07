#pragma once

#include "f4se/NiObjects.h"

class NiExtraData : public NiObject
{
public:
	virtual ~NiExtraData();

	BSFixedString	m_name;	// 10
};

// 20 (DynPosData)
class BSDynPosData : public NiExtraData
{
public:
	// DynPosData
	UInt8 * vertexData;	// 18

	static BSDynPosData * Create(const BSFixedString & name, BSTriShape * shape);
};

extern RelocAddr<uintptr_t> s_BSDynPosDataVtbl;

// 28 (FOD)
class BSFaceGenBaseMorphExtraData : public NiExtraData
{
public:
	NiPoint3	* vertexData;		// 18
	UInt32		modelVertexCount;	// 20
	UInt32		vertexCount;		// 24 - 0 if owning type isnt BSDynamicTriShape

	static BSFaceGenBaseMorphExtraData* Create(BSTriShape * shape);

protected:
	// Fills the vertex data from the original object's vertex data in NiPoint3 layout
	MEMBER_FN_PREFIX(BSFaceGenBaseMorphExtraData);
	DEFINE_MEMBER_FN(ctor, BSFaceGenBaseMorphExtraData*, 0x0066D590, BSTriShape * shape);
};