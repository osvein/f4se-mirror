#pragma once

#include "f4se_common/Relocation.h"
#include "f4se_common/Utilities.h"

// ??
class BSRenderManager
{
public:
	UInt64				unk2588[0x2588 >> 3];	// 2588
	CRITICAL_SECTION	m_textureLock;			// 2590
};

// ??
class BSRenderData
{
public:
	
};

// ??
class BSRenderTargetManager
{
public:
	MEMBER_FN_PREFIX(BSRenderTargetManager);
	// 264CB6DCC7DACA88AC30E4EC83671FAAFBA2E490+7E
	DEFINE_MEMBER_FN(LockTextureType, void, 0x01D06500, UInt32 type);
	// 043E0332BAAAC13F99024C3C6EF85D0377BBAA12+14D
	DEFINE_MEMBER_FN(ReleaseTextureType, void, 0x01D06590, UInt32 type);
	DEFINE_MEMBER_FN(GetRenderData, BSRenderData *, 0x01D06460, UInt32 type, UInt64 unk1, UInt64 unk2, UInt32 unk3); // type, 0, 1, 0
	// 264CB6DCC7DACA88AC30E4EC83671FAAFBA2E490+1FD
	DEFINE_MEMBER_FN(Unk_01, void, 0x01D064B0, UInt32 type, BSRenderData *, UInt8 unk3); // type, rendererData, 1
};

// 1B8
class BSRenderer
{
public:

};

extern RelocPtr <BSRenderer*> g_renderer;
extern RelocPtr <BSRenderManager> g_renderManager;
extern RelocPtr <BSRenderTargetManager> g_renderTargetManager;
