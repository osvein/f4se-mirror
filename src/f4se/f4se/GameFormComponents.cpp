#include "f4se/GameFormComponents.h"

RelocAddr <_EvaluationConditions> EvaluationConditions(0x00728CF0);

#ifdef _DEBUG
#include "f4se/GameExtraData.h"

void BGSInventoryItem::Dump()
{
	stack->Dump();
}

void BGSInventoryItem::Stack::Dump()
{
	if(next) {
		gLog.Indent();
		next->Dump();
		gLog.Outdent();
	}
	if(extraData)
		extraData->Dump();
}
#endif
