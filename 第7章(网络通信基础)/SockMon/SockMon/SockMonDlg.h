// SockMonDlg.h : ͷ�ļ�
//

#pragma once

#include "LSPInstall.h"
#include "afxcmn.h"
#include "Data.h"


// CSockMonDlg �Ի���
class CSockMonDlg : public CDialog
{
// ����
public:
	CSockMonDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_SOCKMON_DIALOG };

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
	afx_msg void OnBnClickedInstall();
	afx_msg void OnBnClickedUninstall();
	afx_msg void OnDestroy();
	afx_msg LRESULT OnNotifyMessage ( WPARAM wParam, LPARAM lParam ) ;

private:
	BOOL			bStatus ;
	CLSPInstall		LSP ;
	CTreeCtrl		SockTree;
	CData			SockData ;
	afx_msg void OnBnClickedEmpty();
	afx_msg void OnBnClickedFlush();
};
