#pragma once

#include "f4se_common/Utilities.h"
#include "f4se/GameEvents.h"
#include "f4se/ScaleformTypes.h"

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

	GFxValue(GFxValue * value)  : objectInterface(value->objectInterface), type(value->type), unk18(value->unk18) { data.obj = value->data.obj; }
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

	class DisplayInfo
	{
	public:
		DisplayInfo() : _varsSet(0) {}
		enum
		{
			kChange_x				= (1 << 0),
			kChange_y				= (1 << 1),
			kChange_rotation		= (1 << 2),
			kChange_xscale			= (1 << 3),
			kChange_yscale			= (1 << 4),
			kChange_alpha			= (1 << 5),
			kChange_visible			= (1 << 6),
			kChange_z				= (1 << 7),
			kChange_xrotation		= (1 << 8),
			kChange_yrotation		= (1 << 9),
			kChange_zscale			= (1 << 10),
			kChange_FOV				= (1 << 11),
			kChange_projMatrix3D	= (1 << 12),
			kChange_viewMatrix3D	= (1 << 13)
		};

		double		_x;				// 00
		double		_y;				// 08
		double		_rotation;		// 10
		double		_xScale;		// 18
		double		_yScale;		// 20
		double		_alpha;			// 28
		bool		_visible;		// 30
		double		_z;				// 38
		double		_xRotation;		// 40
		double		_yRotation;		// 48
		double		_zScale;		// 50
		double		_perspFOV;		// 58
		GMatrix3D	_viewMatrix3D;	// 60
		GMatrix3D	_perspectiveMatrix3D;	// A0
		UInt16		_varsSet;		// E0

		void SetX(double x)					{ SetFlags(kChange_x); _x = x; }
		void SetY(double y)					{ SetFlags(kChange_y); _y = y; }
		void SetRotation(double degrees)	{ SetFlags(kChange_rotation); _rotation = degrees; }
		void SetXScale(double xscale)		{ SetFlags(kChange_xscale); _xScale = xscale; }
		void SetYScale(double yscale)		{ SetFlags(kChange_yscale); _yScale = yscale; }
		void SetAlpha(double alpha)			{ SetFlags(kChange_alpha); _alpha = alpha; }
		void SetVisible(bool visible)		{ SetFlags(kChange_visible); _visible = visible; }
		void SetZ(double z)					{ SetFlags(kChange_z); _z = z; }
		void SetXRotation(double degrees)	{ SetFlags(kChange_xrotation); _xRotation = degrees; }
		void SetYRotation(double degrees)	{ SetFlags(kChange_yrotation); _yRotation = degrees; }
		void SetZScale(double zscale)		{ SetFlags(kChange_zscale); _zScale = zscale; }
		void SetFOV(double fov)				{ SetFlags(kChange_FOV); _perspFOV = fov; }
		void SetProjectionMatrix3D(const GMatrix3D *pmat)  
		{ 
			if (pmat) {
				SetFlags(kChange_projMatrix3D);
				_perspectiveMatrix3D = *pmat;
			} else
				ClearFlags(kChange_projMatrix3D); 
		}
		void SetViewMatrix3D(const GMatrix3D *pmat) 
		{ 
			if (pmat) { 
				SetFlags(kChange_viewMatrix3D); 
				_viewMatrix3D = *pmat;
			} else
				ClearFlags(kChange_viewMatrix3D); 
		}

		// Convenience functions
		void SetPosition(double x, double y) { SetFlags(kChange_x | kChange_y); _x = x; _y = y; }
		void SetScale(double xscale, double yscale)  { SetFlags(kChange_xscale | kChange_yscale); _xScale = xscale; _yScale = yscale; }

		void SetFlags(UInt32 flags) { _varsSet |= flags; }
		void ClearFlags(UInt32 flags) { _varsSet &= ~flags; }
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

		void * unk1;

		MEMBER_FN_PREFIX(ObjectInterface);
		DEFINE_MEMBER_FN(HasMember, bool, 0x02087950, void* pData, const char* name);
		DEFINE_MEMBER_FN(GetMember, bool, 0x0207FD00, void* pData, const char* name, GFxValue* pValue, bool isDisplayObj);
		DEFINE_MEMBER_FN(SetMember, bool, 0x020A8280, void* pData, const char* name, const GFxValue* pValue, bool isDisplayObj);
		DEFINE_MEMBER_FN(Invoke, bool, 0x020899C0, void * pData, GFxValue * result, const char * name, GFxValue * args, UInt64 numArgs, UInt8 isDisplayObj);
		DEFINE_MEMBER_FN(CreateEmptyMovieClip, bool, 0x02061D60, void* pData, GFxValue* pValue, const char* instanceName, SInt32 depth);
		DEFINE_MEMBER_FN(AttachMovie, bool, 0x020592D0, void* pData, GFxValue* pValue, const char* symbolName, const char* instanceName, SInt32 depth, const void * initArgs);
		DEFINE_MEMBER_FN(GetArraySize, UInt32, 0x02079B00, void * pData);
		// ref CC19A4FFD76032A42FBBC61E80011469E50993D7 (+4)
		DEFINE_MEMBER_FN(SetArraySize, bool, 0x020A26C0, void * pData, UInt32 size);
		DEFINE_MEMBER_FN(GetElement, bool, 0x0207D7F0, void * pData, UInt32 index, GFxValue * value);
		DEFINE_MEMBER_FN(PushBack, bool, 0x0209A610, void * pData, GFxValue * value);
		DEFINE_MEMBER_FN(PopBack, bool, 0x02096530, void * pData, GFxValue * value);
		DEFINE_MEMBER_FN(VisitElements, void, 0x020B2D80, void * pData, ArrayVisitor * visitor, UInt32 idx, SInt32 count);
		// ref D46DE0BD07CCA1A3763C21820E22DC491344D2C5 (+485)
		DEFINE_MEMBER_FN(GotoLabeledFrame, bool, 0x020B2EB0, void * pData, const char * frameLabel, bool stop);
		// ref 1A7DD5D4A014A3E7CBF9A53D55DA751C11218613 (+1E7)
		DEFINE_MEMBER_FN(VisitMembers, void, 0x020B2EB0, void * pData, ObjVisitor * visitor, bool isDisplayObj);
		DEFINE_MEMBER_FN(GetText, bool, 0x02085570, void * pData, GFxValue * value, bool html);
		DEFINE_MEMBER_FN(SetText, bool, 0x020AB360, void * pData, const char * text, bool html);
		DEFINE_MEMBER_FN(GetDisplayInfo, bool, 0x0207CEE0, void * pData, DisplayInfo * displayInfo);
		DEFINE_MEMBER_FN(SetDisplayInfo, bool, 0x020A6B90, void * pData, DisplayInfo * displayInfo);
		DEFINE_MEMBER_FN(AddManaged_Internal, void, 0x020918D0, GFxValue * value, void * pData);
		DEFINE_MEMBER_FN(ReleaseManaged_Internal, void, 0x02091920, GFxValue * value, void * pData);
	};

	ObjectInterface	* objectInterface;	// 00
	Type			type;				// 08
	Data			data;				// 10
	void			* unk18;			// 18

	UInt32	GetType(void) const		{ return type & kMask_Type; }
	bool	IsManaged(void) const	{ return (type & kTypeFlag_Managed) != 0; }
	void	CleanManaged(void);
	void	AddManaged(void);

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
	bool	GotoLabeledFrame(const char * frameLabel, bool stop);

	UInt32	GetArraySize();
	bool	SetArraySize(UInt32 size);
	bool	GetElement(UInt32 index, GFxValue * value);
	bool	PushBack(GFxValue * value);
	bool	PopBack(GFxValue * value);
	void	VisitElements(ObjectInterface::ArrayVisitor * visitor, UInt32 idx, SInt32 count);
	void	VisitMembers(ObjectInterface::ObjVisitor * visitor);
	bool	GetText(GFxValue * value, bool html);
	bool	SetText(const char * text, bool html);
	bool	GetDisplayInfo(DisplayInfo * displayInfo);
	bool	SetDisplayInfo(DisplayInfo * displayInfo);
};

// 38
class BSGFxObject : public GFxValue
{
public:
	BSGFxObject() : unk20(0), unk28(0), unk30(0) { }
	BSGFxObject(GFxValue * value) : GFxValue(value), unk20(0), unk28(0), unk30(0)
	{
		if(value->IsManaged())
			value->AddManaged();
	}

	UInt64	unk20;	// 20
	UInt64	unk28;	// 28
	UInt64	unk30;	// 30
};

// 50
class BSGFxDisplayObject : public BSGFxObject
{
public:
	BSGFxDisplayObject() : unk40(0), unk48(0), unk4C(0) { }
	BSGFxDisplayObject(GFxValue * value) : BSGFxObject(value), unk40(0)
	{
		GFxValue width, height;
		GetMember("width", &width);
		GetMember("height", &height);
		unk48 = width.GetNumber();
		unk4C = height.GetNumber();
	}
	virtual ~BSGFxDisplayObject() { };

	struct BSDisplayInfo
	{
		BSGFxDisplayObject		* displayObject;	// 00
		BSGFxDisplayObject		* unk08;			// 08
		GFxValue::DisplayInfo	displayInfo;		// 10
		double	unkF0[(0x1C0 - 0xF0) >> 3];			// F0
		UInt32	unk1C0;	// 1C0
		UInt16	unk1C4;	// 1C4
		UInt16	unk1C6;	// 1C6
	};

	UInt64	unk40;	// 40
	float	unk48;	// 48
	float	unk4C;	// 4C
};
STATIC_ASSERT(sizeof(BSGFxDisplayObject) == 0x50);

class BSGFxShaderFXTarget;

struct FilterColor
{
	float r, g, b;
};

// B0
class BSGFxShaderFXTarget : public BSGFxDisplayObject,
							public BSTEventSink<ApplyColorUpdateEvent>
{
public:
	BSGFxShaderFXTarget() { }
	BSGFxShaderFXTarget(GFxValue * source) : BSGFxDisplayObject(source), 
		unk58(0), unk60(0), unk68(0), unk6C(0), unk70(0), unk74(0), unk78(0), unk7C(0), red(0), 
		green(0), blue(0), multiplier(0), unk94(0), unk98(0), unkA0(0), colorType(0), unkAC(0) {  }//{ CALL_MEMBER_FN(this, Impl_ctor)(source); }
	virtual ~BSGFxShaderFXTarget() { CALL_MEMBER_FN(this, Impl_dtor)(); };

	virtual void Unk_01(void * unk1, void * unk2)
	{
		CALL_MEMBER_FN(this, Impl_Fn1)(unk1, unk2);
	};

	virtual	EventResult	ReceiveEvent(ApplyColorUpdateEvent * evn, void * dispatcher);

	enum ColorTypes
	{
		kColorUnk1 = 0,
		kColorUnk2,
		kColorNormal,
		kColorUnk3,
		kColorUnk4,
		kColorWarning,
		kColorUnk6,
		kColorUnk7
	};

	UInt64	unk58;			// 58
	UInt64	unk60;			// 60
	float	unk68;			// 68
	float	unk6C;			// 6C
	float	unk70;			// 70
	float	unk74;			// 74
	float	unk78;			// 78
	float	unk7C;			// 7C
	float	red;			// 80
	float	green;			// 84
	float	blue;			// 88
	UInt32	colorFlags;		// 8C
	float	multiplier;		// 90
	UInt32	unk94;			// 94
	UInt64	unk98;			// 98
	UInt64	unkA0;			// A0
	UInt32	colorType;		// A8
	UInt32	unkAC;			// AC

	DEFINE_STATIC_HEAP(Heap_Allocate, Heap_Free)

	void SetFilterColor(bool isHostile);

	MEMBER_FN_PREFIX(BSGFxShaderFXTarget);
	// 98B654B565F35633CBE8804A5CBF84646AE30A1B+9
	DEFINE_MEMBER_FN(Impl_ctor, BSGFxShaderFXTarget *, 0x020C5D60, GFxValue * source);
	DEFINE_MEMBER_FN(Impl_dtor, void, 0x020C9370);
	DEFINE_MEMBER_FN(Impl_Fn1, void, 0x020C9890, void * unk1, void * unk2);
};
STATIC_ASSERT(offsetof(BSGFxShaderFXTarget, red) == 0x80);
STATIC_ASSERT(sizeof(BSGFxShaderFXTarget) == 0xB0);

// This function acquires the HUD color by type e.g. normal, PA, hostile
typedef FilterColor * (* _GetFilterColorByType)(BSGFxShaderFXTarget * component, FilterColor * color);
extern RelocAddr <_GetFilterColorByType> GetFilterColorByType;

// Sets explicit component filter color
typedef void (* _ApplyColorFilter)(BSGFxShaderFXTarget * component, FilterColor * color, float unk1);
extern RelocAddr <_ApplyColorFilter> ApplyColorFilter;

typedef void (* _SetDefaultColors)(BSGFxShaderFXTarget * component);
extern RelocAddr <_SetDefaultColors> SetDefaultColors;

typedef void * (* _GetExtDisplayInfo)(BSGFxDisplayObject::BSDisplayInfo * dInfo, BSGFxDisplayObject * target);
extern RelocAddr <_GetExtDisplayInfo> GetExtDisplayInfo;

typedef void (* _SetExtDisplayInfoAlpha)(void * dInfo, double alpha);
extern RelocAddr <_SetExtDisplayInfoAlpha> SetExtDisplayInfoAlpha;

typedef void (* _SetExtDisplayInfo)(BSGFxDisplayObject::BSDisplayInfo * dInfo);
extern RelocAddr <_SetExtDisplayInfo> SetExtDisplayInfo;
