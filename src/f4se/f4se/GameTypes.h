#pragma once

class TESForm;

// 08
struct BSIntrusiveRefCounted
{
public:
	volatile UInt32	m_refCount;	// 00
	UInt32			unk04;
};

// 18
template <class T>
class tArray
{
public:
	T* entries;			// 00
	UInt32 capacity;	// 08
	UInt32 pad0C;		// 0C
	UInt32 count;		// 10
	UInt32 pad14;		// 14

	tArray() : entries(NULL), capacity(0), count(0) { }

	T& operator[](UInt64 index)
	{
		return entries[index];
	}

	bool GetNthItem(UInt64 index, T& pT) const
	{
		if (index < count) {
			pT = entries[index];
			return true;
		}
		return false;
	}

	SInt64 GetItemIndex(T & pFind) const
	{
		for (UInt64 n = 0; n < count; n++) {
			T& pT = entries[n];
			if (pT == pFind)
				return n;
		}
		return -1;
	}
};

typedef tArray<UInt64> UnkArray;
typedef tArray<TESForm*> UnkFormArray;

// 80808
class StringCache
{
public:
	// 18+
	struct Entry
	{
		enum
		{
			kState_RefcountMask =	0x3FFF,
			kState_External =		0x4000,
		};

		Entry	* next;				// 00
		UInt32	state;				// 08 - refcount, hash, flags
		UInt32	length;				// 0C
		Entry	* externData;		// 10
		char	data[0];			// 18

		char * Get()
		{
			Entry * iter = this;

			while(iter->state & kState_External)
				iter = iter->externData;

			return iter->data;
		}
	};

	// 10
	struct Lock
	{
		UInt32	unk00;	// 00 - set to 80000000 when locked
		UInt32	pad04;	// 04
		UInt64	pad08;	// 08
	};

	Entry	* lut[0x10000];	// 00000
	Lock	lock[0x80];		// 80000
	UInt8	isInit;			// 80800
};

typedef StringCache::Entry *	BSFixedString;
