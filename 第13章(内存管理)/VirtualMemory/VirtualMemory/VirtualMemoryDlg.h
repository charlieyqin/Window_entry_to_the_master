// VirtualMemoryDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"

#include "VMInfo.h"
#include "afxwin.h"


// CVirtualMemoryDlg �Ի���
class CVirtualMemoryDlg : public CDialog
{
// ����
public:
	CVirtualMemoryDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_VIRTUALMEMORY_DIALOG };

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
private:
	DWORD		dwSelProcessId ;
	CListCtrl	VMList;
	CVMInfo		VMInfo ;
	CString		szProcess;

private:
	afx_msg void OnBnClickedFlush();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedSelect();
	CButton CommitCheck;
	CButton ReserveCheck;
	CButton FreeCheck;
	afx_msg void OnBnClickedCheck1();
	afx_msg void OnBnClickedCheck2();
	afx_msg void OnBnClickedCheck3();
};
