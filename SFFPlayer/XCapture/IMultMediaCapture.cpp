#include "IMultMediaCapture.h"
#include "MultMediaCapture.h"

#ifdef _WIN32
//Windows  
extern "C"
{
#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
#include "libswscale/swscale.h"
#include "libavdevice/avdevice.h"
}
#endif

void IMultMediaCapture::Init()
{
	static bool isFirstInit = true;
	if (isFirstInit)
	{
		//注册所有的设备与编码器
		av_register_all();
		avcodec_register_all();
		avdevice_register_all();
	}
}

IMultMediaCapture * IMultMediaCapture::CreateCapture(void * WID)
{
	return new MultMediaCapture(WID);
}
