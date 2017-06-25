#pragma once

#include "f4se/NiObjects.h"

// 18
class NiExtraData : public NiObject
{
public:
	virtual ~NiExtraData();

	BSFixedString	m_name;	// 10
};

// 20
class NiStringExtraData : public NiExtraData
{
public:
	virtual ~NiStringExtraData();

	BSFixedString	m_string;	// 18

	static NiStringExtraData * Create(const BSFixedString & name, const BSFixedString & string);
};
extern RelocAddr<uintptr_t> s_NiStringExtraDataVtbl;

// 28
class NiBinaryExtraData : public NiExtraData
{
public:
	UInt8 * binaryData;	// 18
	UInt32	size;		// 20

	static NiBinaryExtraData* Create(const BSFixedString & name, UInt32 size);
};

// 20 (DynPosData)
class BSDynPosData : public NiExtraData
{
public:
	UInt8 * vertexData;	// 18

	static BSDynPosData* Create(const BSFixedString & name, BSTriShape * shape);
};

// 28 (FOD)
class BSFaceGenBaseMorphExtraData : public NiExtraData
{
public:
	NiPoint3	* vertexData;		// 18
	UInt32		modelVertexCount;	// 20
	UInt32		vertexCount;		// 24 - 0 if owning type isnt BSDynamicTriShape

	static BSFaceGenBaseMorphExtraData* Create(BSTriShape * shape);
	static BSFaceGenBaseMorphExtraData* Create(const BSFixedString & name, UInt32 vertexCount);

protected:
	// Fills the vertex data from the original object's vertex data in NiPoint3 layout
	MEMBER_FN_PREFIX(BSFaceGenBaseMorphExtraData);
	DEFINE_MEMBER_FN(ctor, BSFaceGenBaseMorphExtraData*, 0x006821B0, BSTriShape * shape);
};

extern RelocAddr<uintptr_t> s_BSFaceGenBaseMorphExtraDataVtbl;


class BSConnectPoint
{
public:
	// 30
	class Parents : public NiExtraData
	{
	public:
		struct ConnectPoint
		{
			UInt64			unk00;	// 00 - refcount?
			BSFixedString	parent;	// 08
			BSFixedString	name;	// 10
			NiQuaternion	rot;	// 18
			NiPoint3		pos;	// 28
			float			scale;	// 34
		};
		tArray<ConnectPoint*>	points;	// 18
	};
};