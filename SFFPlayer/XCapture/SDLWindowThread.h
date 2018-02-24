#pragma once

#include <list>
#include "InerDefine.h"
#include "thread.hpp"
#include "XMutex.h"

using namespace std;

class SDLWindowThread
{
public:
	SDLWindowThread(int width, int height, void* WID);
	~SDLWindowThread();

	//ѭ���ȴ����ݵĵ���
	static void Loop(void*);

	//�����߳�()
	void Start();

	//ֹͣ�߳�
	void Stop();

	//ˢ������
	void Flash();

	//��������
	void PushData(const stRenderData& data);

	bool PopData(stRenderData& data);
	
public:
	void*				m_WID;
	int					m_width;
	int					m_height;
private:
	list<stRenderData>	m_RenderData;
	XMutex				m_DataMutx;

	aqueue::thread_t	m_Thread;
};

