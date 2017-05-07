#pragma once

#include "f4se/NiObjects.h"
#include "f4se/BSSkin.h"

class NiProperty;

// 40
class BSGeometrySegmentData : public NiObject
{
public:
	// 68
	struct SSFData
	{
		struct SubData
		{
			UInt32	unk00;		// 00
			UInt32	unk04;		// 04
			float	unk08[8];	// 08
		};
		UInt64	unk00;			// 00
		BSFixedString ssfFile;	// 08
		UInt32	sequenceCount;	// 10
		UInt32	numSubIndexes;	// 14
		UInt32	* sequence;		// 18
		SubData	* subIndexData;	// 20
		UInt64	unk28[(0x68-0x28)/8];
	};

	SSFData	* ssfData;	// 10
	UInt32	* segment;	// 18
	void	* unk20;	// 20
	UInt32	unk28;	// 28
	UInt32	unk2C;	// 2C
	UInt32	unk30;	// 30
	UInt32	numTriangles;	// 34
	UInt32	unk38;	// 38
	UInt32	unk3C;	// 3C
};

// 160
class BSGeometry : public NiAVObject
{
public:
	virtual void Unk_39();
	virtual void Unk_3A();
	virtual void Unk_3B();
	virtual void Unk_3C();
	virtual void Unk_3D();
	virtual void Unk_3E();
	virtual void Unk_3F();
	virtual void Unk_40();

	float	unk120[4];						// 120
	NiPointer<NiProperty> effectState;		// 130
	NiPointer<NiProperty> shaderProperty;	// 138
	NiPointer<BSSkin::Instance>	skinInstance;		// 140

	struct GeometryData
	{
		UInt64	flags;

		struct VertexData
		{
			void * unk00;	// 00

			struct Vertex
			{
				typedef UInt16 hfloat;
				struct HalfVector3
				{
					hfloat	x;	// 00
					hfloat	y;	// 02
					hfloat	z;	// 04
				};

				HalfVector3 position;
				hfloat		bitangent_x;
				struct UV
				{
					hfloat u;
					hfloat v;
				} uv;
				HalfVector3	normal;
				UInt8		bitangent_y;
				HalfVector3	tangent;
				UInt8		bitangent_z;
				hfloat		boneWeights[4];
				UInt8		boneIndices[4];
			};

			Vertex	* vertices;	// 08
		};

		struct TriangleData
		{
			void	* unk00;		// 00 - same ptr as the one on vertexData
			UInt16	* triangles;	// 08
		};

		VertexData		* vertexData;	// 08
		TriangleData	* triangleData;	// 10
	};

	GeometryData	* geometryData;			// 148
	UInt64	unk150;							// 150
	UInt8	unk158;							// 158
	UInt8	unk159;							// 159
	UInt16	pad15A;							// 15A
	UInt32	unk15C;							// 15C
};
STATIC_ASSERT(sizeof(BSGeometry) == 0x160);

// 170
class BSTriShape : public BSGeometry
{
public:
	UInt32	numTriangles;	// 160
	UInt16	numVertices;	// 164
	UInt16	unk166;	// 166
	float	unk168;	// 168
	float	unk16C;	// 16C
};
STATIC_ASSERT(sizeof(BSTriShape) == 0x170);

// 1A0
class BSDynamicTriShape : public BSTriShape
{
public:
	UInt32	unk170;		// 170
	UInt32	unk174;		// 174
	UInt32	unk178;		// 178
	UInt32	unk17C;		// 17C
	void	* unk180;	// 180
	BSGeometrySegmentData	* segmentData;	// 188
	void	* unk190;	// 190
	void	* unk198;	// 198
};
STATIC_ASSERT(sizeof(BSDynamicTriShape) == 0x1A0);

// 190
class BSSubIndexTriShape : public BSTriShape
{
public:
	BSGeometrySegmentData	* segmentData;	// 170
	void	* unk178;	// 178
	void	* unk180;	// 180
	void	* unk188;	// 188
};
STATIC_ASSERT(sizeof(BSSubIndexTriShape) == 0x190);
