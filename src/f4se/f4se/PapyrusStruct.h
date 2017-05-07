#pragma once

#include "f4se/PapyrusArgs.h"

bool CreateStruct(VMValue * dst, BSFixedString * structName, VirtualMachine * vm, bool bNone);

template<const char* T_structName>
class VMStructBase
{
public:
	VMStructBase() : m_none(false) { };
	~VMStructBase() { }

	enum { kTypeID = 0 };

	// Will make the VM return None instead of a structure with nothing defined
	void SetNone(bool bNone) { m_none = bNone; }
	bool IsNone() const { return m_none; }

protected:
	bool m_none;
};

template <class T>
struct IsStructType
{
	static const bool value = false;
	static inline const char* name() { return nullptr; };
};

#define DECLARE_STRUCT_TYPE(structName, ...) <Name_##structName##, __VA_ARGS__> ##structName##;
#define DECLARE_STRUCT_STRING(structName) #structName

#define DECLARE_STRUCT(structName, scriptOwner, numParams, ...) \
	char StructName_##structName##[] = ##scriptOwner## "#" DECLARE_STRUCT_STRING(structName); \
	typedef VMStruct##numParams##<StructName_##structName##, __VA_ARGS__> ##structName##;

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
