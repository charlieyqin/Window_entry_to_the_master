// DAOSampleDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"

#include "afxdao.h"

// CDAOSampleDlg �Ի���
class CDAOSampleDlg : public CDialog
{
// ����
public:
	CDAOSampleDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_DAOSAMPLE_DIALOG };

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
	CDaoDatabase	db ;
	CListCtrl		BookList;
public:
	afx_msg void OnBnClickedAdd();
public:
	afx_msg void OnBnClickedModify();
public:
	afx_msg void OnBnClickedDel();
public:
	afx_msg void OnBnClickedFlush();
public:
	afx_msg void OnDestroy();
};
