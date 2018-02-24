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

	//循环等待数据的到来
	static void Loop(void*);

	//启动线程()
	void Start();

	//停止线程
	void Stop();

	//刷新数据
	void Flash();

	//插入数据
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

