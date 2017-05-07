#pragma once

#include "f4se/GameAPI.h"
#include "f4se_common/Utilities.h"

// class NiBinaryStream
// class NiFile : public NiBinaryStream
// class NiMemStream : public NiBinaryStream
// class OutputInfoStream : public NiBinaryStream
// class BSResourceNiBinaryStream : public NiBinaryStream
// class BSResourceStreamParser : public BSResourceNiBinaryStream
// class BSStreamParserData

class NiBinaryStream
{
public:
	virtual ~NiBinaryStream() { };

	virtual bool	IsValid(void) = 0;
	virtual void	Seek(SInt64 delta) = 0;
	virtual UInt64	GetOffset(void) { return 0; }
	virtual SInt64	Unk_04(void * unk1) = 0;
	virtual UInt32	Read(void * buf, UInt64 length) = 0;

	//	void	** _vtbl;	// 00
	void			* unk08;	// 08
};

// 30
class BSResourceNiBinaryStream : public NiBinaryStream
{
public:
	BSResourceNiBinaryStream();
	BSResourceNiBinaryStream(const char * path);
	virtual ~BSResourceNiBinaryStream();

	static void * operator new(std::size_t size)
	{
		return Heap_Allocate(size);
	}
	static void * operator new(std::size_t size, const std::nothrow_t &)
	{
		return Heap_Allocate(size);
	}
	static void * operator new(std::size_t size, void * ptr)
	{
		return ptr;
	}

	static void operator delete(void * ptr)
	{
		Heap_Free(ptr);
	}
	static void operator delete(void * ptr, const std::nothrow_t &)
	{
		Heap_Free(ptr);
	}
	static void operator delete(void *, void *)
	{

	}

	// stub implementations
	virtual bool	IsValid(void);
	virtual void	Seek(SInt64 delta);
	virtual UInt64	GetOffset(void);
	virtual SInt64	Unk_04(void * unk1);
	virtual UInt32	Read(void * buf, UInt64 length);
	virtual UInt32	Write(void * buf, UInt64 length);

	void	* unk10;	// 10
	void	* unk14;	// 18
	UInt64	offset;		// 20
	UInt32	unk28;		// 28
	UInt32	unk2C;		// 2C

	MEMBER_FN_PREFIX(BSResourceNiBinaryStream);
	DEFINE_MEMBER_FN(Construct, BSResourceNiBinaryStream *, 0x005133A0, const char * filePath, UInt8 unk1, UInt64 unk2, SInt8 unk3);	// unk1 = 0, unk2 = 0, unk3 = 0
	DEFINE_MEMBER_FN(ReadLine, UInt32, 0x01AF52A0, char * dst, UInt32 dstLen, UInt32 terminator);
	DEFINE_MEMBER_FN(Destroy, void, 0x01AF5580);
	DEFINE_MEMBER_FN(IsValid, bool, 0x01AF5180, void);
	DEFINE_MEMBER_FN(Seek, void, 0x01AF5190, SInt64);
	DEFINE_MEMBER_FN(GetOffset, UInt32, 0x01AF51F0, void);
	DEFINE_MEMBER_FN(Unk_04, SInt64, 0x01AF5200, void * unk1);
	DEFINE_MEMBER_FN(Read, UInt32, 0x01AF5360, void * buf, UInt64 length);
	DEFINE_MEMBER_FN(Write, UInt32, 0x01AF53F0, void * buf, UInt64 length);

	UInt32 ReadLine(char * dst, UInt32 dstLen, UInt32 terminator);
	UInt32 ReadLine_w(wchar_t * dst, UInt32 dstLen, UInt32 terminator);	// length in characters
};

typedef BSResourceNiBinaryStream* (* _CreateFileStream)(const char * filePath);
extern RelocAddr <_CreateFileStream> CreateFileStream;
