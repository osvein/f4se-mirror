#pragma once

#include "f4se_common/Utilities.h"
#include "f4se/GameTypes.h"

#include "f4se/PapyrusInterfaces.h"

// 58
class VMObjectTypeInfo : public IComplexType
{
public:
	virtual ~VMObjectTypeInfo();

	virtual UInt32	GetType();	// returns 1 (kType_Identifier)

	void				* unk20;	// 20
	UInt64				unk28;		// 28
	UInt64				unk30;		// 30
	UInt64				unk38;		// 38
	UInt64				unk40;		// 40
	UInt64				unk48;		// 48
	UInt64				unk50;		// 50
};

// 70
class VMStructTypeInfo : public IComplexType
{
public:
	virtual ~VMStructTypeInfo();

	virtual UInt32	GetType();	// returns 7 (kType_Struct)

	struct StructData
	{
		UInt64	unk00;		// 00
		UInt64	unk08;		// 08
		UInt64	m_type;		// 10
		void	* unk18;	// 18
		UInt64	unk20;		// 20
	};
	tArray<StructData>	m_data;		// 20
	UInt64				unk38[(0x70 - 0x38) >> 3];
};

// 30
class VMIdentifier
{
public:
	enum
	{
		kLockBit = 0x80000000,
		kFastSpinThreshold = 10000
	};

	SInt32				m_refCount;		// 00
	UInt32				unk04;			// 04
	VMObjectTypeInfo	* m_typeInfo;	// 08
	void				* unk10;		// 10
	UInt64				unk18;			// 18
	volatile UInt64		m_handle;		// 20
	volatile SInt32		m_lock;			// 28
	UInt32				unk2C;			// 2C

	UInt64	GetHandle(void);

	SInt32	Lock(void);
	void	Unlock(SInt32 oldLock);

	// lock and refcount?
	void	IncrementLock(void);
	SInt32	DecrementLock(void);

	void	Destroy(void);

	MEMBER_FN_PREFIX(VMIdentifier);
	DEFINE_MEMBER_FN(Destroy_Internal, void, 0x025BB6C0);
};

// 10
class VMValue
{
public:
	VMValue() : type(kType_None) { data.p = nullptr; }
	~VMValue() { CALL_MEMBER_FN(this, Destroy)(); }

	VMValue(const VMValue & other)
	{
		if(&other != this)
		{
			type = kType_None;
			data.p = nullptr;
			CALL_MEMBER_FN(this, Set)(&other);
		}
	}
	VMValue& operator=(const VMValue& other)
	{
		if(&other == this)
			return *this;
		
		CALL_MEMBER_FN(this, Set)(&other);
		return *this;
	}

	enum
	{
		kType_None			= 0,
		kType_Identifier	= 1,	// Number not actually used by VMValue
		kType_String		= 2,
		kType_Int			= 3,
		kType_Float			= 4,
		kType_Bool			= 5,
		kType_Variable		= 6,	// Points to a VMValue
		kType_Struct		= 7,	// Number not actually used by VMValue

		kType_ArrayBegin	= 11,
		kType_StringArray	= 12,
		kType_IntArray		= 13,
		kType_FloatArray	= 14,
		kType_BoolArray		= 15,
		kType_VariableArray	= 16,
		kType_StructArray	= 17,	// Number not actually used by VMValue
		kType_ArrayEnd		= 18
	};

	struct ArrayData
	{
		SInt32				m_refCount;	// 00
		UInt32				unk04;		// 04
		UInt64				m_type;		// 08 - base types 1-6
		UInt64				unk10;		// 10
		tArray<VMValue>		arr;	// 18

		MEMBER_FN_PREFIX(ArrayData);
		DEFINE_MEMBER_FN(Destroy, void, 0x025E73C0);
	};

	struct StructData
	{
		SInt32				m_refCount;	// 00
		UInt32				unk04;		// 04
		UInt64				unk08;		// 08
		VMStructTypeInfo	* m_type;	// 10
		UInt8				unk18;		// 18 - set to 1 if unk19 is 1 (3EFCF27952D674A8FA959AABC29A0FE3E726FA91)
		UInt8				unk19;		// 19 - set to 1 when type+0x68 == 3
		UInt16				unk1A;		// 1A
		UInt32				unk1C;		// 1C
		char				m_value[0];	// 20

		VMValue * GetStruct() { return (VMValue *)&m_value[0]; }
	};

	UInt64	type;	// Can be number or IComplexType or IComplexType | 1 (array)
	
	union
	{
		SInt32				i;
		UInt32				u;
		float				f;
		bool				b;
		void				* p;
		StructData			* strct;
		ArrayData			* arr;
		VMValue				* var;
		VMIdentifier		* id;
		StringCache::Entry	* str;
		BSFixedString *	GetStr(void)	{ return (BSFixedString *)(&str); }
	} data;	

	void	SetNone(void)
	{
		CALL_MEMBER_FN(this, Destroy)();

		type = kType_None;
		data.u = 0;
	}

	void	SetInt(SInt32 i)
	{
		CALL_MEMBER_FN(this, Destroy)();

		type = kType_Int;
		data.i = i;
	}

	void	SetFloat(float f)
	{
		CALL_MEMBER_FN(this, Destroy)();

		type = kType_Float;
		data.f = f;
	}

	void	SetBool(bool b)
	{
		CALL_MEMBER_FN(this, Destroy)();

		type = kType_Bool;
		data.b = b;
	}

	
	void	SetString(const char * str)
	{
		CALL_MEMBER_FN(this, Destroy)();

		type = kType_String;
		CALL_MEMBER_FN(data.GetStr(), Set)(str);
	}

	void	SetVariable(VMValue * value)
	{
		CALL_MEMBER_FN(this, Destroy)();

		type = kType_Variable;
		data.var = value;
	}

	void	SetComplexType(IComplexType * typeInfo)
	{
		CALL_MEMBER_FN(this, Destroy)();

		type = (UInt64)typeInfo;
		data.p = nullptr;
	}

	void	SetIdentifier(VMIdentifier	** identifier)
	{
		IComplexType * typeInfo = GetComplexType();
		if(typeInfo && typeInfo->GetType() == kType_Identifier)
		{
			CALL_MEMBER_FN(this, Destroy)();

			if(*identifier)
				(*identifier)->IncrementLock();

			data.id = *identifier;
		}
	}

	bool	IsIntegralType()
	{
		return type >= kType_String && type <= kType_Variable;
	}

	bool	IsIntegralArrayType()
	{
		return type > kType_ArrayBegin && type < kType_ArrayEnd;
	}

	bool	IsComplexArrayType()
	{
		return (IsComplexType() && (type & 0x01LL));
	}

	bool	IsArrayType()
	{
		return IsIntegralArrayType() || IsComplexArrayType();
	}

	bool	IsComplexType()
	{
		return type >= kType_ArrayEnd;
	}

	bool	IsIdentifier()
	{
		IComplexType * typeInfo = GetComplexType();
		return typeInfo ? typeInfo->GetType() == kType_Identifier : false;
	}

	IComplexType * GetComplexType()
	{
		return IsComplexType() ? reinterpret_cast<IComplexType *>(type & ~0x01LL) : nullptr;
	}

	MEMBER_FN_PREFIX(VMValue);
	DEFINE_MEMBER_FN(Set, void, 0x025C06C0, const VMValue * src);
	DEFINE_MEMBER_FN(Destroy, void, 0x025C0070);
	DEFINE_STATIC_HEAP(Heap_Allocate, Heap_Free)
};

UInt64 GetArrayType(UInt64 type);
