
#include "afxwin.h"
#include "SDLWindowThread.h"

extern "C"
{
	#include "SDL2/SDL.h"
};

#define SFM_REFRESH_EVENT  (SDL_USEREVENT + 1)
#define SFM_BREAK_EVENT  (SDL_USEREVENT + 2)

SDLWindowThread::SDLWindowThread(int width, int height, void* WID):
	m_WID(WID),
	m_width(width),
	m_height(height)
{
}


SDLWindowThread::~SDLWindowThread()
{
}

void SDLWindowThread::Loop(void* para)
{
	SDLWindowThread* pThread = (SDLWindowThread*)para;
	
	//初始化SDL对象
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_AUDIO)) {

		return;
	}

	SDL_Window* m_Screen = NULL;
	if (0 == pThread->m_WID)
	{
		m_Screen = SDL_CreateWindow(
			"视屏监控",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			500, 300,
			SDL_WINDOW_RESIZABLE/* SDL_WINDOW_HIDDEN*/ | SDL_WINDOW_OPENGL);
	}
	else
	{
		//显示在MFC控件上
		m_Screen = SDL_CreateWindowFrom((void*)((CWnd*)(pThread->m_WID))->GetSafeHwnd());
	}
	//===========================================
	if (!m_Screen) {

		SDL_Quit();
		return;
	}

	//重新打开时不显示窗口,所以需要在这里实行
	SDL_ShowWindow(m_Screen);

	//创建渲染器和贴图对象
	SDL_Renderer* m_SDLRenderer = SDL_CreateRenderer(m_Screen, -1, 0);
	SDL_Texture*  m_SDLTexture = SDL_CreateTexture(m_SDLRenderer,
		SDL_PIXELFORMAT_IYUV, 
		SDL_TEXTUREACCESS_STREAMING,
		pThread->m_width,
		pThread->m_height);

	if (NULL == m_SDLRenderer || NULL == m_SDLTexture)
	{
		SDL_Quit();
		return;
	}


	SDL_Event event;
	stRenderData data;
	for (;;)
	{
		//等待线程
		SDL_WaitEvent(&event);
		if(SFM_REFRESH_EVENT == event.type)
		{
			if (!pThread->PopData(data))
			{
				continue;
			}

			SDL_UpdateTexture(m_SDLTexture, NULL, data.data, data.inersize);
			SDL_RenderClear(m_SDLRenderer);
			SDL_RenderCopy(m_SDLRenderer, m_SDLTexture, NULL, NULL);
			SDL_RenderPresent(m_SDLRenderer);
		}
		else if(SFM_BREAK_EVENT == event.type)
		{
			break;
		}
	}


	//SDL清理相关
	if (m_SDLTexture)
	{
		SDL_DestroyTexture(m_SDLTexture);
		m_SDLTexture = NULL;
	}
	if (m_SDLRenderer)
	{
		SDL_DestroyRenderer(m_SDLRenderer);
		m_SDLRenderer = NULL;
	}

	if (m_Screen)
	{
		SDL_DestroyWindow(m_Screen);
		m_Screen = NULL;
	}


	SDL_Quit();
}

void SDLWindowThread::Start()
{
	m_Thread.start(Loop, this);
}

void SDLWindowThread::Stop()
{
	SDL_Event event;
	event.type = SFM_BREAK_EVENT;
	SDL_PushEvent(&event);
	m_Thread.stop();
}

void SDLWindowThread::Flash()
{
	SDL_Event event;
	event.type = SFM_REFRESH_EVENT;
	SDL_PushEvent(&event);
}

void SDLWindowThread::PushData(const stRenderData & data)
{
	m_DataMutx.lock();
	m_RenderData.push_back(data);
	m_DataMutx.unlock();

	Flash();
}

bool SDLWindowThread::PopData(stRenderData & data)
{
	m_DataMutx.lock();
	if (m_RenderData.size() <= 0)
	{
		m_DataMutx.unlock();
		return false;
	}
	data = m_RenderData.front();
	m_DataMutx.unlock();

	return true;
}
