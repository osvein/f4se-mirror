#pragma once

class NiObject;

// 10
class NiRTTI
{
public:
	const char	* name;
	NiRTTI		* parent;
};

NiObject * DoNiRTTICast(NiObject * src, const NiRTTI * typeInfo);

#define ni_cast(obj, type)	(type *)DoNiRTTICast(obj, NiRTTI_##type)

extern const NiRTTI *	NiRTTI_BSLightingShaderProperty;
