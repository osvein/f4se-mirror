#include "f4se/NiExtraData.h"
#include "f4se/BSGeometry.h"

// ??_7BSDynPosData@@6B@
RelocAddr<uintptr_t> s_BSDynPosDataVtbl(0x02CCF468);

BSDynPosData * BSDynPosData::Create(const BSFixedString & name, BSTriShape * shape)
{
	void* memory = Heap_Allocate(sizeof(BSDynPosData));
	memset(memory, 0, sizeof(BSDynPosData));
	((UInt64*)memory)[0] = s_BSDynPosDataVtbl.GetUIntPtr();
	BSDynPosData * data = (BSDynPosData*)memory;
	data->m_name = name;

	auto geometryData = shape->geometryData;
	if(geometryData)
	{
		auto vertexData = geometryData->vertexData;
		if(vertexData)
		{
			// Yes this is really what it does.
			data->vertexData = (UInt8*)Heap_Allocate(shape->numVertices * 0x0C);
			UInt8 * src = vertexData->vertexBlock;
			UInt8 * dst = data->vertexData;
			for(UInt32 i = 0; i < shape->numVertices; i++)
			{
				memcpy_s(dst, 0x08, src, 0x08);
				*(dst + 0x08) = 0;

				dst += 0x0C;
				src += shape->GetVertexSize();
			}
		}
	}
	return data;
}

BSFaceGenBaseMorphExtraData * BSFaceGenBaseMorphExtraData::Create(BSTriShape * shape)
{
	BSFaceGenBaseMorphExtraData * data = (BSFaceGenBaseMorphExtraData*)Heap_Allocate(sizeof(BSFaceGenBaseMorphExtraData));
	CALL_MEMBER_FN(data, ctor)(shape);
	return data;
}
