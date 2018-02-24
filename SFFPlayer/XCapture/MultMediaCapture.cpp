#include "MultMediaCapture.h"
#include "SDLWindowThread.h"


MultMediaCapture::MultMediaCapture(void * WID):
	m_SDLThread(NULL)
{
}

MultMediaCapture::~MultMediaCapture()
{
}

int MultMediaCapture::Start(const char * device, const char * rect, int sampRate)
{
	return 0;
}

int MultMediaCapture::Stop()
{
	//¹Ø±ÕSDL
	if (m_SDLThread)
	{
		m_SDLThread->Stop();
		delete m_SDLThread;
		m_SDLThread = NULL;
	}
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
