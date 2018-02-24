

#include "stdafx.h"
#include "SFFPlayer.h"
#include "SFFPlayerDlg.h"
#include "afxdialogex.h"
//#include "IVedioCapture.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CSFFPlayerDlg::CSFFPlayerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSFFPlayerDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	//m_VideoCapture = IVedioCapture::CreateCapture();
}

void CSFFPlayerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_URL, m_url);
	DDX_Control(pDX, IDC_EDIT_DEVICE, m_device);
}

BEGIN_MESSAGE_MAP(CSFFPlayerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(ID_START, &CSFFPlayerDlg::OnBnClickedStart)
	ON_BN_CLICKED(ID_PAUSE, &CSFFPlayerDlg::OnBnClickedPause)
//	ON_BN_CLICKED(ID_CONTINUE, &CSFFPlayerDlg::OnBnClickedContinue)
	ON_BN_CLICKED(ID_STOP, &CSFFPlayerDlg::OnBnClickedStop)
	ON_BN_CLICKED(ID_ABOUT, &CSFFPlayerDlg::OnBnClickedAbout)
	ON_BN_CLICKED(IDCANCEL, &CSFFPlayerDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_FILEBROWSER, &CSFFPlayerDlg::OnBnClickedFilebrowser)
	ON_BN_CLICKED(ID_SAVE, &CSFFPlayerDlg::OnBnClickedSave)
	ON_BN_CLICKED(ID_STOP_SAVE, &CSFFPlayerDlg::OnBnClickedStopSave)
	ON_BN_CLICKED(ID_STOP_CAP, &CSFFPlayerDlg::OnBnClickedStopCap)
END_MESSAGE_MAP()


// CSFFPlayerDlg 消息处理程序

BOOL CSFFPlayerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	//设置默认参数
	m_device.SetWindowTextA("Integrated Webcam");
	m_url.SetWindowTextA("defaultFile");
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CSFFPlayerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CSFFPlayerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CSFFPlayerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CSFFPlayerDlg::OnBnClickedStart()
{
	
	char url[250]={0};
	m_url.GetWindowTextA(url,250);
	if(strcmp(url,"")==0){
		AfxMessageBox("文件路径为空！");
		return ;
	}

	char device[250] = {0}
	;
	m_device.GetWindowTextA(device, 250);
	if (strcmp(device, "") == 0) {
		AfxMessageBox("没有指定设备！");
		return;
	}
	
	//pThreadPlay = AfxBeginThread(Thread_Play,this);//开启线程
	//m_VideoCapture->Start(device/*"Integrated Webcam"*/, this->GetDlgItem(IDC_SCREEN), url );
}


void CSFFPlayerDlg::OnBnClickedPause()
{
	//thread_pause=!thread_pause;
	//m_VideoCapture->Suspend();
}


void CSFFPlayerDlg::OnBnClickedStop()
{
	//m_VideoCapture->Stop();
//	thread_exit=1;
}


void CSFFPlayerDlg::OnBnClickedAbout()
{
	//CAboutDlg dlg;
	//dlg.DoModal();
}


void CSFFPlayerDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}


void CSFFPlayerDlg::OnBnClickedFilebrowser()
{
	CString FilePathName;
	CFileDialog dlg(TRUE,NULL,NULL,NULL,NULL);///TRUE为OPEN对话框，FALSE为SAVE AS对话框 
	if(dlg.DoModal()==IDOK) {
		FilePathName=dlg.GetPathName();
		m_url.SetWindowText(FilePathName);
	}
}
int main(int argc, char *argv[])
{
	return -1;
}



void CSFFPlayerDlg::OnBnClickedSave()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CSFFPlayerDlg::OnBnClickedStopSave()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CSFFPlayerDlg::OnBnClickedStopCap()
{
	// TODO: 在此添加控件通知处理程序代码
}
