
// SFFPlayerDlg.h : ͷ�ļ�
//

#pragma once
#include  "Resource.h"

class IVedioCapture;

// CSFFPlayerDlg �Ի���
class CSFFPlayerDlg : public CDialogEx
{
// ����
public:
	CSFFPlayerDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_SFFPLAYER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	CWinThread *pThreadPlay;
	IVedioCapture* m_VideoCapture;

	// ���ɵ���Ϣӳ�亯��
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
