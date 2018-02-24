
#include "VideoCaptureThread.h"
#include "InerDefine.h"

VideoCaptureThread::VideoCaptureThread(XThreadMgr* mgr_):
	XThreadBase("video_capture", mgr_)
{
}


VideoCaptureThread::~VideoCaptureThread()
{
}

void VideoCaptureThread::OnTimer(int id)
{
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

	}
	break;
	}
}
