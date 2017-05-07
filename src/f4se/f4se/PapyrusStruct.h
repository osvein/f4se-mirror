#pragma once

#include "f4se/PapyrusArgs.h"

bool CreateStruct(VMValue * dst, BSFixedString * structName, VirtualMachine * vm);

template<const char* T_structName>
class VMStructBase
{
public:
	VMStructBase() { };
	~VMStructBase() { }

	enum { kTypeID = 0 };
};

template <class T>
struct IsStructType
{
	static const bool value = false;
	static inline const char* name() { return nullptr; };
};

#define NUM_PARAMS 1
#include "PapyrusStructDef.inl"

#define NUM_PARAMS 2
#include "PapyrusStructDef.inl"

#define NUM_PARAMS 3
#include "PapyrusStructDef.inl"

#define NUM_PARAMS 4
#include "PapyrusStructDef.inl"

#define NUM_PARAMS 5
#include "PapyrusStructDef.inl"

#define NUM_PARAMS 6
#include "PapyrusStructDef.inl"

#define NUM_PARAMS 7
#include "PapyrusStructDef.inl"

#define NUM_PARAMS 8
#include "PapyrusStructDef.inl"

#define NUM_PARAMS 9
#include "PapyrusStructDef.inl"

#define NUM_PARAMS 10
#include "PapyrusStructDef.inl"
