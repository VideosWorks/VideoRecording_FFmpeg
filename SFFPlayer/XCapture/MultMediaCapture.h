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

	//�����豸(�����豸����, ���ݽػ��С,�ػ�Ƶ��)
	virtual int Start(const char* device, const char* rect="1080X720", int sampRate = 60);

	//ֹͣ�豸
	virtual int Stop();

	//�����洢
	virtual int StartSave(const char* name = "default");

	//ֹͣ�洢
	virtual int StopSave();

protected:
	SDLWindowThread*	m_SDLThread;
};
#endif