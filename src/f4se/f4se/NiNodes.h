#pragma once

#include "f4se/NiObjects.h"

// 140
class NiNode : public NiAVObject
{
public:
	virtual void	AttachChild(NiAVObject * obj, bool firstAvail);
	virtual void	DetachChild(UInt32 unk1, NiAVObject * obj);
	virtual void	Unk_3B(void);
	virtual void	RemoveChild(NiAVObject * obj);
	virtual void	Unk_3D(void);
	virtual void	RemoveAt(UInt32 i);
	virtual void	Unk_3F(void);
	virtual void	ReplaceChild(UInt32 index, NiAVObject * obj, NiAVObject ** replaced);
	virtual void	ReplaceAt(UInt32 index, NiAVObject * obj);
	virtual void	Unk_42(void);

	NiTArray <NiAVObject *>	m_children;	// 120
	float					unk138;
	float					unk13C;
};
STATIC_ASSERT(sizeof(NiNode) == 0x140);

// 190
class BSFaceGenNiNode : public NiNode
{
public:
	UInt64	unk140[(0x178 - 0x140) >> 3];	// 140
	UInt32	unk178;							// 178

	// 1FA2A8F9E63D0F771FC6A9BAB875E88A9215810B
	enum
	{
		kFlag_UpdateModel	= (1 << 0),
		kFlag_Unk1			= (1 << 7),
		kFlag_Unk2			= (1 << 8)
	};

	UInt32					flags;			// 17C
	UInt64					unk180;			// 180
	UInt64					unk188;			// 188
};
