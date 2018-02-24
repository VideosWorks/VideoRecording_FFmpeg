
// SFFPlayerDlg.h : 头文件
//

#pragma once
#include  "Resource.h"

class IVedioCapture;

// CSFFPlayerDlg 对话框
class CSFFPlayerDlg : public CDialogEx
{
// 构造
public:
	CSFFPlayerDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_SFFPLAYER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	CWinThread *pThreadPlay;
	IVedioCapture* m_VideoCapture;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedStart();
	afx_msg void OnBnClickedPause();
//	afx_msg void OnBnClickedContinue();
	afx_msg void OnBnClickedStop();
	afx_msg void OnBnClickedAbout();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedFilebrowser();
	CEdit m_url;
	CEdit m_device;
	//afx_msg void OnBnClickedPause2();
	afx_msg void OnBnClickedSave();
	afx_msg void OnBnClickedStopSave();
	afx_msg void OnBnClickedStopCap();
};
