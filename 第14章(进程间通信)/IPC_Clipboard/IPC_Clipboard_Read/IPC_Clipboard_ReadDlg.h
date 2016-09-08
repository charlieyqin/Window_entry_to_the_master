// IPC_Clipboard_ReadDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"


// CIPC_Clipboard_ReadDlg �Ի���
class CIPC_Clipboard_ReadDlg : public CDialog
{
// ����
public:
	CIPC_Clipboard_ReadDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_IPC_CLIPBOARD_READ_DIALOG };

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
	afx_msg void OnBnClickedGetText();
public:
	afx_msg void OnBnClickedGetBitmap();
public:
	afx_msg void OnBnClickedGetSelfDefine();
public:
	afx_msg void OnBnClickedGetAll();

public:
	VOID	ReadOutText () ;
	VOID	ReadOutBitmap () ;
	VOID	ReadOutSelfDefineData () ;
};
