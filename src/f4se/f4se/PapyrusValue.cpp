#include "f4se/PapyrusValue.h"
#include "f4se/PapyrusInterfaces.h"

UInt64 VMIdentifier::GetHandle(void)
{
	UInt64	result = (*g_objectHandlePolicy)->GetInvalidHandle();

	SInt32	oldLock = Lock();
	result = m_handle;
	Unlock(oldLock);

	return result;
}

SInt32 VMIdentifier::Lock(void)
{
	UInt32	spinCount = 0;
	SInt32	lockValue;

	while(true)
	{
		lockValue = m_lock;

		if(lockValue & kLockBit)
		{
			// someone else is holding the lock, sleep
			if(spinCount <= kFastSpinThreshold)
			{
				Sleep(0);
				spinCount++;
			}
			else
			{
				Sleep(1);
			}
		}
		else
		{
			// try to take the lock
			if(InterlockedCompareExchange(&m_lock, lockValue | kLockBit, lockValue) == lockValue)
				break;
		}
	}

	return lockValue;
}

void VMIdentifier::Unlock(SInt32 oldLock)
{
	m_lock = oldLock;
}

// try to increment the lock
void VMIdentifier::IncrementLock(void)
{
	UInt32	spinCount = 0;
	
	while(true)
	{
		SInt32	lockValue = m_lock;

		if(lockValue & kLockBit)
		{
			if(spinCount <= kFastSpinThreshold)
			{
				Sleep(0);
				spinCount++;
			}
			else
			{
				Sleep(1);
			}
		}
		else
		{
			if(lockValue == 1)
			{
				if(InterlockedCompareExchange(&m_lock, lockValue | kLockBit, lockValue) == lockValue)
				{
					(*g_objectHandlePolicy)->AddRef(m_handle);
					m_lock = 2;
					break;
				}
			}
			else
			{
				if(InterlockedCompareExchange(&m_lock, lockValue + 1, lockValue) == lockValue)
					break;
			}
		}
	}
}

// try to decrement the lock
SInt32 VMIdentifier::DecrementLock(void)
{
	UInt32	spinCount = 0;

	while(true)
	{
		SInt32	lockValue = m_lock;

		if(lockValue & kLockBit)
		{
			if(spinCount <= kFastSpinThreshold)
			{
				Sleep(0);
				spinCount++;
			}
			else
			{
				Sleep(1);
			}
		}
		else
		{
			if(lockValue == 2)
			{
				if(InterlockedCompareExchange(&m_lock, lockValue | kLockBit, lockValue) == lockValue)
				{
					(*g_objectHandlePolicy)->Release(m_handle);
					m_lock = 1;
					return 1;
				}
			}
			else
			{
				if(InterlockedCompareExchange(&m_lock, lockValue - 1, lockValue) == lockValue)
					return lockValue - 1;
			}
		}
	}
}

void VMIdentifier::Destroy(void)
{
	CALL_MEMBER_FN(this, Destroy_Internal)();
	Heap_Free(this);
}

UInt64 GetArrayType(UInt64 type)
{
	if(type > VMValue::kType_StructArray)
	{
		return type & ~0x01;
	}
	else if(type > VMValue::kType_IntegralStart)
	{
		return type - VMValue::kType_ArrayOffset;
	}

	return type;
}
