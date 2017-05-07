#pragma once

// 10
class GRefCountImplCore
{
public:
	GRefCountImplCore() :refCount(1) { }
	virtual ~GRefCountImplCore() { }

//	void	** _vtbl;				// 00
	volatile	SInt32	refCount;	// 08
	UInt32		pad0C;				// 0C
};

class GRefCountImpl : public GRefCountImplCore
{
public:
	GRefCountImpl() { }
	virtual ~GRefCountImpl() { }
};

class GRefCountBaseStatImpl : public GRefCountImpl
{
public:
	GRefCountBaseStatImpl() { }
	virtual ~GRefCountBaseStatImpl() { }
};

class GRefCountBase : public GRefCountBaseStatImpl
{
public:
	GRefCountBase() { }
	virtual ~GRefCountBase() { }
};