// SnifferDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"

#include "IpPack.h"


// CSnifferDlg �Ի���
class CSnifferDlg : public CDialog
{
// ����
public:
	CSnifferDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_SNIFFER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	BOOL	isMonitor ;
	CListCtrl m_PackList;

	VOID	AddPackInfo ( LPPACK_INFO lpPackInfo ) ;
	friend DWORD WINAPI MonitorThread ( LPVOID lParam ) ;
public:
	afx_msg void OnBnClickedStart();
public:
	afx_msg void OnBnClickedStop();
public:
	afx_msg void OnBnClickedEmpty();
};
