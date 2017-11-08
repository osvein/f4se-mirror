#include "f4se/NiRTTI.h"
#include "f4se/NiObjects.h"

NiObject * DoNiRTTICast(NiObject * src, const NiRTTI * typeInfo)
{
	if(src)
		for(NiRTTI * iter = src->GetRTTI(); iter; iter = iter->parent)
			if(iter == typeInfo)
				return src;

	return nullptr;
}

// E8007B50AB42A5298C03123C69989D33E62E5595+3D
const RelocPtr<NiRTTI>	NiRTTI_BSLightingShaderProperty(0x06759F48);

// E8007B50AB42A5298C03123C69989D33E62E5595+79
const RelocPtr<NiRTTI>	NiRTTI_BSEffectShaderProperty(0x06759F38);

// xref aBsshaderproper, loaded to ecx
const RelocPtr<NiRTTI>	NiRTTI_BSShaderProperty(0x06759ED0);

// xref aNiextradata, loaded to ecx
const RelocPtr<NiRTTI>	NiRTTI_NiExtraData(0x05C42E90);
