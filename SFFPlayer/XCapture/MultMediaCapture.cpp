#include "MultMediaCapture.h"
#include "SDLWindowThread.h"
#include "VideoCaptureThread.h"
#include "XThreadMgr.h"

MultMediaCapture::MultMediaCapture(void * WID):
	m_SDLThread(NULL)
{

	m_ThreadMgr = new XThreadMgr(3,0);

	m_CaptureThread = new VideoCaptureThread(this, m_ThreadMgr);
	m_ThreadMgr->attach_obj(m_CaptureThread);
}

MultMediaCapture::~MultMediaCapture()
{
}

int MultMediaCapture::Start(const char * device, int width, int height, int sampRate)
{
	return 0;
}

int MultMediaCapture::Stop()
{
	//¹Ø±ÕSDL
	m_WRLock.wlock();
	if (m_SDLThread)
	{
		m_SDLThread->Stop();
		delete m_SDLThread;
		m_SDLThread = NULL;
	}
	m_WRLock.w_unlock();
	return 0;
}

int MultMediaCapture::StartSave(const char * name)
{
	return 0;
}

int MultMediaCapture::StopSave()
{
	return 0;
}

void MultMediaCapture::SendRender( char* data, int inersize)
{
	m_WRLock.rlock();
	if (m_SDLThread)
	{
		stRenderData data_;
		data_.data = data;
		data_.inersize = inersize;
		m_SDLThread->PushData(data_);
	}
	m_WRLock.rlock();
}
