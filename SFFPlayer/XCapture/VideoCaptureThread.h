#pragma once
#include "XThreadBase.h"
#define __STDC_CONSTANT_MACROS
//#define OUT_FILE
extern "C"
{
#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
#include "libswscale/swscale.h"
#include "libavdevice/avdevice.h"
#include "SDL2/SDL.h"
};

class MultMediaCapture;

class VideoCaptureThread : public XThreadBase
{
public:
	VideoCaptureThread(MultMediaCapture* capture, XThreadMgr* mgr_);
	virtual ~VideoCaptureThread();

	/************************************************************************
	* ���ƣ�OnTimer
	* ˵����//��ʱ��ʵ����ʵ�ָú�����
	* ������id��ʱ���¼�ID
	* ����ֵ����
	/************************************************************************/
	virtual void OnTimer(int id) ;

	/************************************************************************
	* ���ƣ�OnAttach
	* ˵�������Ӷ����̳߳ɹ��¼�
	* ��������
	* ����ֵ����
	/************************************************************************/
	virtual void OnAttach();

	/************************************************************************
	* ���ƣ�OnDetach
	* ˵�������̷߳����¼�
	* ��������
	* ����ֵ����
	/************************************************************************/
	virtual void OnDetach();

	/************************************************************************
	* ���ƣ�OnMsg
	* ˵������Ӧ�����̵߳���Ϣ
	* ������cmd ����ID,lparm,wparam
	* ����ֵ����
	/************************************************************************/
	virtual void OnMsg(int cmd_, long long  lparm_, long long wparam_);


private:
	//�����豸
	void OnProcResetDevice(void* deviceinfo);

	//��ʼ�洢�ļ�
	void OnProcStartSave(void* info);

	//ֹͣ�洢�¼�
	void OnProcStopSave();

	//����ʱ�¼�
	void OnProcDataCap();
private:
	//void OnCloseDevice();
	bool OnCloseDevice();
private:
	/////////////////////////�ػ��豸���//////////////////////////////
	//�ػ��豸��Ҫ��Frame
	AVFormatContext	*m_CapFormatCtx = NULL;
	
	//�������ڱ������ĵڼ���
	int m_CapVideoIndex;

	//�����ػ�ı�����������
	AVCodecContext	*m_CapCodecCtx;
	AVCodec			*m_CapCodec;
	
	//�ػ��豸��֡��ת����YUV֡
	AVFrame	*m_CapFrame, *m_CapFrameYUV;
	
	//YuvFrme�ڴ�洢��λ��
	uint8_t *m_YuvBuffer;
	AVPacket *m_CapPacket;

	//��ʶ��ǰ�Ƿ�洢
	bool     m_Save;

	//
	struct SwsContext *m_ImgSwsCtx;

	////////////////////////////
	int m_FreqCy;//��������Ϣ
	MultMediaCapture*	m_MediaCapture;

};

