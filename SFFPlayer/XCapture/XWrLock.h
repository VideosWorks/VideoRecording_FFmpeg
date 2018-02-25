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
		//��ʼ����д��
		InitializeSRWLock(&rwlock);
	}

	void rlock()
	{
		//����
		AcquireSRWLockShared(&rwlock);
	}

	void wlock()
	{
		//д��
		AcquireSRWLockExclusive(&rwlock);
	}

	void r_unlock()
	{
		//������
		ReleaseSRWLockShared(&rwlock);
	}

	void w_unlock()
	{
		//д����
		ReleaseSRWLockExclusive(&rwlock);
	}
private:
	SRWLOCK rwlock;
	XWRLock(const XWRLock&);
	void operator = (const XWRLock&);
};