// CTRLAnimateDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"


// CCTRLAnimateDlg �Ի���
class CCTRLAnimateDlg : public CDialog
{
// ����
public:
	CCTRLAnimateDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_CTRLANIMATE_DIALOG };

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
	afx_msg void OnBnClickedOpen();
public:
	afx_msg void OnBnClickedClose();
public:
	afx_msg void OnBnClickedPlay();
public:
	afx_msg void OnBnClickedStop();
public:
	CAnimateCtrl AnimateCtrl;
};
