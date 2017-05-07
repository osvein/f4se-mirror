#include "f4se/NiExtraData.h"
#include "f4se/BSGeometry.h"

// ??_7NiStringExtraData@@6B@
RelocAddr<uintptr_t> s_NiStringExtraDataVtbl(0x02D1EDC8);
// ??_7BSFaceGenBaseMorphExtraData@@6B@
RelocAddr<uintptr_t> s_BSFaceGenBaseMorphExtraDataVtbl(0x02BF5A18);

NiStringExtraData * NiStringExtraData::Create(const BSFixedString & name, const BSFixedString & string)
{
	void* memory = Heap_Allocate(sizeof(NiStringExtraData));
	memset(memory, 0, sizeof(NiStringExtraData));
	((UInt64*)memory)[0] = s_NiStringExtraDataVtbl.GetUIntPtr();
	NiStringExtraData * data = (NiStringExtraData*)memory;
	data->m_name = name;
	data->m_string = string;
	return data;
}

BSFaceGenBaseMorphExtraData * BSFaceGenBaseMorphExtraData::Create(BSTriShape * shape)
{
	BSFaceGenBaseMorphExtraData * data = (BSFaceGenBaseMorphExtraData*)Heap_Allocate(sizeof(BSFaceGenBaseMorphExtraData));
	CALL_MEMBER_FN(data, ctor)(shape);
	return data;
}

BSFaceGenBaseMorphExtraData* BSFaceGenBaseMorphExtraData::Create(const BSFixedString & name, UInt32 vertexCount)
{
	void* memory = Heap_Allocate(sizeof(BSFaceGenBaseMorphExtraData));
	memset(memory, 0, sizeof(BSFaceGenBaseMorphExtraData));
	((UInt64*)memory)[0] = s_BSFaceGenBaseMorphExtraDataVtbl.GetUIntPtr();
	BSFaceGenBaseMorphExtraData * data = (BSFaceGenBaseMorphExtraData*)memory;
	data->m_name = name;
	data->modelVertexCount = vertexCount;
	data->vertexCount = vertexCount;
	data->vertexData = (NiPoint3*)Heap_Allocate(sizeof(NiPoint3) * vertexCount);
	memset(data->vertexData, 0, sizeof(NiPoint3) * vertexCount);
	return data;
}
