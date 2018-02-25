#pragma once
#ifndef ___MULTMEDIA_CAPTURE_HH
#define ___MULTMEDIA_CAPTURE_HH
#include "IMultMediaCapture.h"
#include "XWrLock.h"
class SDLWindowThread;
class VideoCaptureThread;
class XThreadMgr;

class MultMediaCapture  : public IMultMediaCapture
{
public:
	MultMediaCapture(void* WID);

	virtual ~MultMediaCapture() ;

	//�����豸(�����豸����, ���ݽػ��С,�ػ�Ƶ��)
	virtual int Start(const char* device,int width, int height, int sampRate = 60);

	//ֹͣ�豸
	virtual int Stop();

	//�����洢
	virtual int StartSave(const char* name = "default");

	//ֹͣ�洢
	virtual int StopSave();

	//��Ⱦ�̵߳Ĳ���
	void SendRender( char* data, int inersize);

protected:
	SDLWindowThread*	m_SDLThread;
	XWRLock				m_WRLock;
	VideoCaptureThread*	m_CaptureThread;
	XThreadMgr*			m_ThreadMgr;
};
#endif