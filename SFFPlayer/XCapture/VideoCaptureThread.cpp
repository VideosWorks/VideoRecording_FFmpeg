
#include "VideoCaptureThread.h"
#include "InerDefine.h"
#include "XThreadMgr.h"
#include "MultMediaCapture.h"
#include <string.h>

VideoCaptureThread::VideoCaptureThread(MultMediaCapture* capture, XThreadMgr* mgr_):
	XThreadBase("video_capture", mgr_),
	/////////////////////////截获设备相关//////////////////////////////
	//截获设备需要的Frame
	m_CapFormatCtx(NULL),
	//视屏流在编码器的第几个
	m_CapVideoIndex(-1),
	//视屏截获的编码器上下文
	m_CapCodecCtx(NULL),
	m_CapCodec(NULL),
	//截获设备的帧和转码后的YUV帧
	m_CapFrame(NULL),
	m_CapFrameYUV(NULL),
	//YuvFrme内存存储的位置
	m_YuvBuffer(NULL),
	m_CapPacket(NULL),
	m_ImgSwsCtx(NULL),//转码用的上下文
	m_Save(false),
	m_FreqCy(30),
	m_MediaCapture(capture)
{
}


VideoCaptureThread::~VideoCaptureThread()
{
}

void VideoCaptureThread::OnTimer(int id)
{
	switch (id)
	{
	case VIDEO_DATA_CAPTURE_ID:
	{
		OnProcDataCap();
	}
	break;
	}
}

void VideoCaptureThread::OnAttach()
{

}

void VideoCaptureThread::OnDetach()
{

}

void VideoCaptureThread::OnMsg(int cmd_, long long lparm_, long long wparam_)
{
	switch (cmd_)
	{
		//重置采集设备信息
	case RESET_CAPTURE:
	{
		if (lparm_ == sizeof(stResetDevice))
		{
			OnProcResetDevice((void*)wparam_);
		}
	}
	break;
	case STOP_SAVE:
	{
		m_Save = false;
		//发送停止存储事件到存储线程
		OnProcStopSave();
	}
	break;
	case SATRT_SAVE:
	{
		if (lparm_ <= SAVE_FILE_MAX_LEN)
		{
			//输入存储名称
			OnProcStartSave((void*)wparam_);
		}
	};
	}
}


void VideoCaptureThread::OnProcResetDevice(void* deviceinfo)
{
	//关闭之前的设备
	OnCloseDevice();

	stResetDevice* pDevice = (stResetDevice*)deviceinfo;
	if (!pDevice)
	{
		return;
	}

	if (!strcmp(pDevice->deviceName, ""))
	{
		return ;
	}

	AVDictionary *options = NULL;

	//设置截获设备的宽高
	char buffSize[128] = {0};
	sprintf(buffSize, "%dx%d", pDevice->width, pDevice->height);
	av_dict_set(&options, "video_size", buffSize, 0);

	//设置设备采样率
	if (pDevice->freqcy <= 0)
	{
		pDevice->freqcy = 30;
	}
	char buffRate[64] = {0};
	sprintf(buffRate, "%d", pDevice->freqcy);
	av_dict_set(&options, "framerate", buffRate, 0);
	m_FreqCy = pDevice->freqcy;

	//打开设备
	char devicebuff[MAX_DEVICE_LENGTH + 7] = { 0 };
	sprintf(devicebuff, "video=%s", pDevice->deviceName);

	//找到DSHow的fmt
	AVInputFormat *ifmt = av_find_input_format("dshow");
	if (avformat_open_input(&m_CapFormatCtx, devicebuff, ifmt, &options) != 0) {
		printf("Couldn't open input stream.\n");
		m_CapFormatCtx = 0;
		return;
	}

	//找到对应的流
	if (avformat_find_stream_info(m_CapFormatCtx, NULL) < 0) {
		//关闭设备
		avformat_close_input(&m_CapFormatCtx);
		m_CapFormatCtx = 0;
		return;
	}

	m_CapVideoIndex = -1;
	for (int i = 0; i < m_CapFormatCtx->nb_streams; i++)
		if (m_CapFormatCtx->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO) {
			m_CapVideoIndex = i;
			break;
		}

	//如果没有找到对应的视屏编码器则关闭设备
	if (m_CapVideoIndex == -1) {
		//关闭设备
		avformat_close_input(&m_CapFormatCtx);
		m_CapFormatCtx = 0;
		return;
	}

	//找到对应的编码器上下文
	m_CapCodecCtx = m_CapFormatCtx->streams[m_CapVideoIndex]->codec;
	m_CapCodec = avcodec_find_decoder(m_CapCodecCtx->codec_id);
	if (m_CapCodec == NULL) {
		//关闭设备
		avformat_close_input(&m_CapFormatCtx);
		m_CapFormatCtx = 0;
		m_CapCodecCtx = 0;
		m_CapCodec = 0;
		return;
	}

	//打开对应的编码器
	if (avcodec_open2(m_CapCodecCtx, m_CapCodec, NULL) < 0) {
		//关闭设备
		avformat_close_input(&m_CapFormatCtx);
		m_CapFormatCtx = 0;
		m_CapCodecCtx = 0;
		m_CapCodec = 0;
		return;
	}

	//为帧预分配内存
	m_CapFrame = av_frame_alloc();
	m_CapFrameYUV = av_frame_alloc();
	m_YuvBuffer = (uint8_t *)av_malloc(avpicture_get_size(AV_PIX_FMT_YUV420P, m_CapCodecCtx->width, m_CapCodecCtx->height));
	avpicture_fill((AVPicture *)m_CapFrameYUV, m_YuvBuffer, AV_PIX_FMT_YUV420P, m_CapCodecCtx->width, m_CapCodecCtx->height);

	//获取编码上下文
	m_ImgSwsCtx = sws_getContext(m_CapCodecCtx->width, m_CapCodecCtx->height, m_CapCodecCtx->pix_fmt,
		m_CapCodecCtx->width, m_CapCodecCtx->height, AV_PIX_FMT_YUV420P, SWS_BICUBIC, NULL, NULL, NULL);

	m_CapPacket = (AVPacket *)av_malloc(sizeof(AVPacket));

	//向存储线程发送停止存储事件
	m_Save = false;

}

void VideoCaptureThread::OnProcStopSave()
{

}

void VideoCaptureThread::OnProcStartSave(void* info)
{

}

bool VideoCaptureThread::OnCloseDevice()
{
	//关闭数据采集定时器
	get_mgr()->unregist_timer(get_id(), VIDEO_DATA_CAPTURE_ID);

	m_CapVideoIndex = -1;

	if (m_ImgSwsCtx)
	{
		sws_freeContext(m_ImgSwsCtx);
		m_ImgSwsCtx = NULL;
	}

	//清理数据截获相关的内存
	//--------------
	if (m_YuvBuffer)
	{
		av_free(m_YuvBuffer);
		m_YuvBuffer = NULL;
	}

	if (m_CapFrameYUV)
	{
		av_frame_free(&m_CapFrameYUV);
		m_CapFrameYUV = NULL;
	}

	if (m_CapFrame)
	{
		av_frame_free(&m_CapFrame);
		m_CapFrame = NULL;
	}

	if (m_CapCodecCtx)
	{
		avcodec_close(m_CapCodecCtx);
		m_CapCodecCtx = NULL;
	}

	if (m_CapFormatCtx)
	{
		avformat_close_input(&m_CapFormatCtx);
		m_CapFormatCtx = NULL;
	}

	if (m_CapPacket)
	{
		av_free(m_CapPacket);
		m_CapPacket = NULL;
	}

	return false;
}


void VideoCaptureThread::OnProcDataCap()
{
	int got_picture = 0;

	//读取一帧的数据
	if (av_read_frame(m_CapFormatCtx, m_CapPacket) >= 0) {
		if (m_CapPacket->stream_index == m_CapVideoIndex) {

			//解码
			int ret = avcodec_decode_video2(m_CapCodecCtx, m_CapFrame, &got_picture, m_CapPacket);
			if (ret > 0) {
				if (got_picture) {

					//转码
					sws_scale(m_ImgSwsCtx, (const uint8_t* const*)m_CapFrame->data,
						m_CapFrame->linesize,
						0,
						m_CapCodecCtx->height,
						m_CapFrameYUV->data,
						m_CapFrameYUV->linesize);

					//将数据发送给渲染线程和存储线程

					//渲染线程
					int picture_size = avpicture_get_size(AV_PIX_FMT_YUV420P, 
						m_CapCodecCtx->width,
						m_CapCodecCtx->height);
					char* renderBuff = (char*)malloc(picture_size);
					memcpy(renderBuff, m_YuvBuffer, picture_size);
					m_MediaCapture->SendRender(renderBuff, picture_size);

					//存储线程
					char* saveBuff = (char*)malloc(picture_size);
					memcpy(saveBuff, m_YuvBuffer, picture_size);
				}
			}
		}

		//释放分配的内存
		av_free_packet(m_CapPacket);
	}
}