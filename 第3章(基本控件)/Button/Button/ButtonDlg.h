// ButtonDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"


// CButtonDlg �Ի���
class CButtonDlg : public CDialog
{
// ����
public:
	CButtonDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_BUTTON_DIALOG };

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
	CButton game1;
	CButton game2;
	CButton game3;
	CButton game4;
	CButton game5;
	CButton game6;
public:
	CButton addr1;
	CButton addr2;
	CButton addr3;
	CButton addr4;
public:
	afx_msg void OnBnClickedSure();
};
