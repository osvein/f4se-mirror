#include "f4se/PapyrusStruct.h"

bool CreateStruct(VMValue * dst, BSFixedString * structName, VirtualMachine * vm)
{
	dst->SetNone();
	VMValue::StructData * structData = nullptr;
	VMStructTypeInfo * typeInfo = nullptr;

	if(vm->GetStructTypeInfo(structName, &typeInfo))
	{
		vm->CreateStruct(structName, &structData);
		if(structData)
		{
			dst->type = (UInt64)typeInfo;
			dst->data.strct = structData;
		}

		typeInfo->Release();
		return structData ? true : false;
	}

	return false;
}
