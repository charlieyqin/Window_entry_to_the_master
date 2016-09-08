// IPC_ClipboardDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"


// CIPC_ClipboardDlg �Ի���
class CIPC_ClipboardDlg : public CDialog
{
// ����
public:
	CIPC_ClipboardDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_IPC_CLIPBOARD_DIALOG };

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
	afx_msg void OnBnClickedText();
public:
	afx_msg void OnBnClickedBitmap();
public:
	afx_msg void OnBnClickedMultData();
public:
	afx_msg void OnBnClickedDelaySubmit();
public:
	afx_msg void OnBnClickedSelfDefine();
public:
	CListBox MsgList;
public:
	afx_msg void OnRenderAllFormats();
public:
	afx_msg void OnRenderFormat(UINT nFormat);
public:
	afx_msg void OnDestroyClipboard();
	afx_msg void OnDestroy();

private:
	UINT	uDeskopPixelX ;
	UINT	uDeskopPixelY ;
	UINT	uNewFormat ;

public:
	VOID	WriteIntoText () ;
	VOID	WriteIntoBitmap () ;
	VOID	WriteIntoSelfDefineData () ;
};
