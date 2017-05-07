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
	virtual void	Unk_40(void);
	virtual void	UpdateUpwardPass(void);

	NiTArray <NiAVObject *>	m_children;	// 120
	float					unk138;
	float					unk13C;
};
STATIC_ASSERT(sizeof(NiNode) == 0x140);
