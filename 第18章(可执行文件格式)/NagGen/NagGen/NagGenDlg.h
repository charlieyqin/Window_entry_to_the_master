// NagGenDlg.h : ͷ�ļ�
//

#pragma once

#include "PEInfo.h"

#include "Dbghelp.h"
#pragma comment ( lib, "Dbghelp.lib" )

// CNagGenDlg �Ի���
class CNagGenDlg : public CDialog
{
// ����
public:
	CNagGenDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_NAGGEN_DIALOG };

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
	CPEInfo	PEInfo ;
	DWORD	dwDllNameOff, dwFunNameOff, dwIATOff, dwIIDNum, dwNewEntryOff, dwNagTitleOff, dwNagContentOff ;
public:
	CString m_PathName;
public:
	CString m_NagTitle;
public:
	CString m_NagContent;
public:
	afx_msg void OnEnChangePath();
public:
	afx_msg void OnEnChangeNagTitle();
public:
	afx_msg void OnEnChangeNagContent();
public:
	afx_msg void OnBnClickedBrowse();
public:
	afx_msg void OnBnClickedOk();
public:
	DWORD GenerateData(PBYTE pData, LPVOID lpImageBase);
};
