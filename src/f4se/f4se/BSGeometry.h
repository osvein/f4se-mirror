#pragma once

#include "f4se/NiObjects.h"

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

	float	unk120[4];			// 120
	void	* effectState;		// 130
	void	* shaderProperty;	// 138
	void	* skinInstance;		// 140
	void	* unk148;			// 148
	UInt64	unk150;				// 150
	UInt16	unk158;				// 158
	UInt16	pad15A;				// 15A
	UInt32	unk15C;				// 15C
};
STATIC_ASSERT(sizeof(BSGeometry) == 0x160);

// 170
class BSTriShape : public BSGeometry
{
public:
	UInt64	unk160;	// 160
	float	unk168;	// 168
	float	unk16C;
};
STATIC_ASSERT(sizeof(BSTriShape) == 0x170);

// 1A0
class BSDynamicTriShape : public BSTriShape
{
public:
	void	* unk170;	// 170
	void	* unk178;	// 178
	void	* unk180;	// 180
	void	* unk188;	// 188
	void	* unk190;	// 190
	void	* unk198;	// 198
};
STATIC_ASSERT(sizeof(BSDynamicTriShape) == 0x1A0);

// 190
class BSSubIndexTriShape : public BSTriShape
{
public:
	void	* unk170;	// 170
	void	* unk178;	// 178
	void	* unk180;	// 180
	void	* unk188;	// 188
};
STATIC_ASSERT(sizeof(BSSubIndexTriShape) == 0x190);