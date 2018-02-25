#pragma once

#include<stdio.h>
#include<process.h>
#include <WinSock2.h>
#include<windows.h>


class XWRLock
{
public:
	XWRLock()
	{
		//³õÊ¼»¯¶ÁÐ´Ëø
		InitializeSRWLock(&rwlock);
	}

	void rlock()
	{
		//¶ÁËø
		AcquireSRWLockShared(&rwlock);
	}

	void wlock()
	{
		//Ð´Ëø
		AcquireSRWLockExclusive(&rwlock);
	}

	void r_unlock()
	{
		//¶Á½âËø
		ReleaseSRWLockShared(&rwlock);
	}

	void w_unlock()
	{
		//Ð´½âËø
		ReleaseSRWLockExclusive(&rwlock);
	}
private:
	SRWLOCK rwlock;
	XWRLock(const XWRLock&);
	void operator = (const XWRLock&);
};