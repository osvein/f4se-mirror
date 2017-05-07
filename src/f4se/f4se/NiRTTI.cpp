#include "f4se/NiRTTI.h"
#include "f4se/NiObjects.h"

NiObject * DoNiRTTICast(NiObject * src, const NiRTTI * typeInfo)
{
	uintptr_t typeAddr = uintptr_t(typeInfo) + RelocationManager::s_baseAddr;
	if(src)
		for(NiRTTI * iter = src->GetRTTI(); iter; iter = iter->parent)
			if(iter == (NiRTTI *)typeAddr)
				return src;

	return nullptr;
}

// E8007B50AB42A5298C03123C69989D33E62E5595+3D
const NiRTTI *	NiRTTI_BSLightingShaderProperty = (NiRTTI *)0x066B25F8;
