#pragma once
#ifndef ___MULTMEDIA_CAPTURE_HH
#define ___MULTMEDIA_CAPTURE_HH
#include "IMultMediaCapture.h"

class SDLWindowThread;

class MultMediaCapture  : public IMultMediaCapture
{
public:
	MultMediaCapture(void* WID);

	virtual ~MultMediaCapture() ;

	//启动设备(输入设备名称, 数据截获大小,截获频率)
	virtual int Start(const char* device, const char* rect="1080X720", int sampRate = 60);

	//停止设备
	virtual int Stop();

	//启动存储
	virtual int StartSave(const char* name = "default");

	//停止存储
	virtual int StopSave();

protected:
	SDLWindowThread*	m_SDLThread;
};
#endif