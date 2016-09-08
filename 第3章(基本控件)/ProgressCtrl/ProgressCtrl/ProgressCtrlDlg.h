// ProgressCtrlDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"


// CProgressCtrlDlg �Ի���
class CProgressCtrlDlg : public CDialog
{
// ����
public:
	CProgressCtrlDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_PROGRESSCTRL_DIALOG };

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
	afx_msg void OnEnChangeBegin();
public:
	afx_msg void OnEnChangeEnd();
public:
	afx_msg void OnBnClickedShow();
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
public:
	BOOL	bStatus ;					// ��ǰ״̬���Ƿ�������ʾ
	UINT	nStart;						// ��ʼֵ
	UINT	nEnd;						// ��ֵֹ
	UINT	nStep;						// ����
	CString szInfo, szInfo2;			// ��ǰ������Ϣ
	CProgressCtrl ProgressCtrl;			// ���ö�λ��ʽ�Ľ�����
	CProgressCtrl ProgressCtrl2;		// �����𲽷�ʽ�Ľ�����
};
