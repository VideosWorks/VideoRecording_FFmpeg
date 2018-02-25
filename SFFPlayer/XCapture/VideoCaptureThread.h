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
	* 名称：OnTimer
	* 说明：//定时器实现者实现该函数。
	* 参数：id定时器事件ID
	* 返回值：无
	/************************************************************************/
	virtual void OnTimer(int id) ;

	/************************************************************************
	* 名称：OnAttach
	* 说明：附加对象到线程成功事件
	* 参数：无
	* 返回值：无
	/************************************************************************/
	virtual void OnAttach();

	/************************************************************************
	* 名称：OnDetach
	* 说明：从线程分离事件
	* 参数：无
	* 返回值：无
	/************************************************************************/
	virtual void OnDetach();

	/************************************************************************
	* 名称：OnMsg
	* 说明：响应其他线程的消息
	* 参数：cmd 命令ID,lparm,wparam
	* 返回值：无
	/************************************************************************/
	virtual void OnMsg(int cmd_, long long  lparm_, long long wparam_);


private:
	//重置设备
	void OnProcResetDevice(void* deviceinfo);

	//开始存储文件
	void OnProcStartSave(void* info);

	//停止存储事件
	void OnProcStopSave();

	//处理定时事件
	void OnProcDataCap();
private:
	//void OnCloseDevice();
	bool OnCloseDevice();
private:
	/////////////////////////截获设备相关//////////////////////////////
	//截获设备需要的Frame
	AVFormatContext	*m_CapFormatCtx = NULL;
	
	//视屏流在编码器的第几个
	int m_CapVideoIndex;

	//视屏截获的编码器上下文
	AVCodecContext	*m_CapCodecCtx;
	AVCodec			*m_CapCodec;
	
	//截获设备的帧和转码后的YUV帧
	AVFrame	*m_CapFrame, *m_CapFrameYUV;
	
	//YuvFrme内存存储的位置
	uint8_t *m_YuvBuffer;
	AVPacket *m_CapPacket;

	//标识当前是否存储
	bool     m_Save;

	//
	struct SwsContext *m_ImgSwsCtx;

	////////////////////////////
	int m_FreqCy;//采样率信息
	MultMediaCapture*	m_MediaCapture;

};

