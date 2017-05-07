#pragma once

#include "f4se_common/Utilities.h"
#include "f4se/GameEvents.h"

class GFxMovieRoot;

// 20
class GFxValue
{
public:
	GFxValue()					: objectInterface(NULL), type(kType_Undefined), unk18(nullptr)	{ }
	GFxValue(int v)				: objectInterface(NULL), type(kType_Int), unk18(nullptr)		{ data.number = v; }
	GFxValue(UInt32 v)			: objectInterface(NULL), type(kType_UInt), unk18(nullptr)		{ data.number = v; }
	GFxValue(SInt32 v)			: objectInterface(NULL), type(kType_Int), unk18(nullptr)		{ data.number = v; }
	GFxValue(double v)			: objectInterface(NULL), type(kType_Number), unk18(nullptr)		{ data.number = v; }
	GFxValue(bool v)			: objectInterface(NULL), type(kType_Bool), unk18(nullptr)		{ data.boolean = v; }
	GFxValue(const char* ps)	: objectInterface(NULL), type(kType_String), unk18(nullptr)		{ data.string = ps; }

	~GFxValue();

	enum Type
	{
		kType_Undefined =	0,
		kType_Null,
		kType_Bool,
		kType_Int,
		kType_UInt,
		kType_Number,
		kType_String,
		kType_Unknown7,
		kType_Object,
		kType_Array,
		kType_DisplayObject,


		kTypeFlag_Managed =	1 << 6,

		kMask_Type =		0x8F,	// not sure why it checks the top bit
	};

	union Data
	{
		UInt32			u32;
		SInt32			s32;
		double			number;
		bool			boolean;
		const char		* string;
		const char		** managedString;
		void			* obj;
	};

	class ObjectInterface
	{
	public:
		class ArrayVisitor
        {
        public:
            virtual ~ArrayVisitor() {}
            virtual void Visit(UInt32 idx, const GFxValue * val) = 0;
        };
		class ObjVisitor
		{
		public:
			virtual ~ObjVisitor() { }
			virtual bool ShowDisplayMembers(void) { return false; }
			virtual void Visit(const char * unk1, const GFxValue * value) = 0;
		};

		GFxMovieRoot * movieRoot;

		MEMBER_FN_PREFIX(ObjectInterface);
		DEFINE_MEMBER_FN(HasMember, bool, 0x02040E00, void* pData, const char* name);
		DEFINE_MEMBER_FN(GetMember, bool, 0x020391B0, void* pData, const char* name, GFxValue* pValue, bool isDisplayObj);
		DEFINE_MEMBER_FN(SetMember, bool, 0x02061730, void* pData, const char* name, const GFxValue* pValue, bool isDisplayObj);
		DEFINE_MEMBER_FN(Invoke, bool, 0x02042E70, void * pData, GFxValue * result, const char * name, GFxValue * args, UInt64 numArgs, UInt8 isDisplayObj);
		DEFINE_MEMBER_FN(CreateEmptyMovieClip, bool, 0x0201B210, void* pData, GFxValue* pValue, const char* instanceName, SInt32 depth);
		DEFINE_MEMBER_FN(AttachMovie, bool, 0x02012780, void* pData, GFxValue* pValue, const char* symbolName, const char* instanceName, SInt32 depth, const void * initArgs);
		DEFINE_MEMBER_FN(GetArraySize, UInt32, 0x02032FB0, void * pData);
		// ref 0x0212D9E0 (+4)
		DEFINE_MEMBER_FN(SetArraySize, bool, 0x0205BB70, void * pData, UInt32 size);
		DEFINE_MEMBER_FN(GetElement, bool, 0x02036CA0, void * pData, UInt32 index, GFxValue * value);
		DEFINE_MEMBER_FN(PushBack, bool, 0x02053AC0, void * pData, GFxValue * value);
		DEFINE_MEMBER_FN(PopBack, bool, 0x0204F9E0, void * pData, GFxValue * value);
		DEFINE_MEMBER_FN(VisitElements, void, 0x0206C230, void * pData, ArrayVisitor * visitor, UInt32 idx, SInt32 count);
		// ref 0x02177360 (+485)
		DEFINE_MEMBER_FN(VisitMembers, void, 0x0206C360, void * pData, ObjVisitor * visitor, bool isDisplayObj);
		DEFINE_MEMBER_FN(GetText, bool, 0x0203EA20, void * pData, GFxValue * value, bool html);
		DEFINE_MEMBER_FN(SetText, bool, 0x02064810, void * pData, const char * text, bool html);
		DEFINE_MEMBER_FN(ReleaseManaged_Internal, void, 0x0204ADD0, GFxValue * value, void * pData);
	};

	ObjectInterface	* objectInterface;	// 00
	Type			type;				// 08
	Data			data;				// 10
	void			* unk18;			// 18

	UInt32	GetType(void) const		{ return type & kMask_Type; }
	bool	IsManaged(void) const	{ return (type & kTypeFlag_Managed) != 0; }
	void	CleanManaged(void);

	bool	IsUndefined() const		{ return GetType() == kType_Undefined; }
	bool	IsNull() const			{ return GetType() == kType_Null; }
	bool	IsBool() const			{ return GetType() == kType_Bool; }
	bool	IsNumber() const		{ return GetType() == kType_Number; }
	bool	IsString() const		{ return GetType() == kType_String; }
	bool	IsObject() const		{ return (GetType() == kType_Object) ||  GetType() == kType_Array ||  GetType() == kType_DisplayObject; }
	bool	IsArray() const			{ return GetType() == kType_Array; }
	bool	IsDisplayObject() const	{ return GetType() == kType_DisplayObject; }

	void	SetUndefined(void);
	void	SetNull(void);
	void	SetBool(bool value);
	void	SetInt(SInt32 value);
	void	SetUInt(UInt32 value);
	void	SetNumber(double value);
	void	SetString(const char * value);

	bool			GetBool(void) const;
	const char *	GetString(void) const;
	double			GetNumber(void) const;
	SInt32			GetInt(void) const;
	UInt32			GetUInt(void) const;

	bool	HasMember(const char * name);
	bool	SetMember(const char * name, GFxValue * value);
	bool	GetMember(const char * name, GFxValue * value);
	bool	Invoke(const char * name, GFxValue * result, GFxValue * args, UInt32 numArgs);

	bool	CreateEmptyMovieClip(GFxValue* pValue, const char* instanceName, SInt32 depth);
	bool	AttachMovie(GFxValue* pValue, const char* symbolName, const char* instanceName, SInt32 depth, const void * initArgs);

	UInt32	GetArraySize();
	bool	SetArraySize(UInt32 size);
	bool	GetElement(UInt32 index, GFxValue * value);
	bool	PushBack(GFxValue * value);
	bool	PopBack(GFxValue * value);
	void	VisitElements(ObjectInterface::ArrayVisitor * visitor, UInt32 idx, SInt32 count);
	void	VisitMembers(ObjectInterface::ObjVisitor * visitor);
	bool	GetText(GFxValue * value, bool html);
	bool	SetText(const char * text, bool html);
};

// 38
class BSGFxObject : public GFxValue
{
public:
	UInt64	unk20;	// 20
	UInt64	unk28;	// 28
	UInt64	unk30;	// 30
};

// 50
class BSGFxDisplayObject : public BSGFxObject
{
public:
	virtual ~BSGFxDisplayObject();

	UInt64	unk38;	// 38
	UInt64	unk40;	// 40
	UInt32	unk48;	// 48
	UInt32	unk4C;	// 4C
};

// B0
class BSGFxShaderFXTarget : public BSGFxDisplayObject
{
public:
	virtual ~BSGFxShaderFXTarget();

	BSTEventSink<ApplyColorUpdateEvent>	applyColorUpdateEvent;	// 50
	UInt64	unk58;	// 58
	UInt64	unk60;	// 60
	UInt64	unk68;	// 68
	UInt64	unk70;	// 70
	float	red;	// 78
	float	green;	// 7C
	float	blue;	// 80
	float	unk84;	// 84
	float	multiplier;	// 88
	void	* unk90;	// 90
	UInt64	unk98;	// 98
	UInt64	unkA0;	// A0
	UInt64	unkA8;	// A8
};
