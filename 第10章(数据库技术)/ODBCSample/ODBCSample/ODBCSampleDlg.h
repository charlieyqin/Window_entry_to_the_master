// ODBCSampleDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"

#include "book.h"

// CODBCSampleDlg �Ի���
class CODBCSampleDlg : public CDialog
{
// ����
public:
	CODBCSampleDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_ODBCSAMPLE_DIALOG };

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
	CBook		Record ;
	CListCtrl	BookList;
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
