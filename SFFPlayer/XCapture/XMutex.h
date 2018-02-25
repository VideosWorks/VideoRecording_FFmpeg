#pragma once
#include <WinSock2.h>
#include "Windows.h"
class XMutex
{
public:
	inline XMutex()
	{
		InitializeCriticalSection(&cs);
	}

	inline ~XMutex()
	{
		DeleteCriticalSection(&cs);
	}

	inline void lock()
	{
		EnterCriticalSection(&cs);
	}

	inline void unlock()
	{
		LeaveCriticalSection(&cs);
	}

private:

	CRITICAL_SECTION cs;

	//  Disable copy construction and assignment.
	XMutex(const XMutex&);
	void operator = (const XMutex&);
};