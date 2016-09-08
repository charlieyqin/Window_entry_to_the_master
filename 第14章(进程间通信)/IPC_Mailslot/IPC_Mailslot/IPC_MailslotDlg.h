// IPC_MailslotDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"

#define DEF_BUF_SIZE	1024
#define MAILSLOT_NAME	L"\\\\.\\mailslot\\test_mailslot"


// CIPC_MailslotDlg �Ի���
class CIPC_MailslotDlg : public CDialog
{
// ����
public:
	CIPC_MailslotDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_IPC_MAILSLOT_DIALOG };

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
	CListBox InfoList;
public:
	afx_msg void OnBnClickedFlush();

private:
	HANDLE	hMailslot ;
public:
	VOID	StartServer () ;
	VOID	StopServer () ;
public:
	afx_msg void OnDestroy();
};
