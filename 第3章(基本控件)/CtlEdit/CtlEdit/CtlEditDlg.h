// CtlEditDlg.h : ͷ�ļ�
//

#pragma once


// CCtlEditDlg �Ի���
class CCtlEditDlg : public CDialog
{
// ����
public:
	CCtlEditDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_CTLEDIT_DIALOG };

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
	CString szMsg1;
	CString szMsg2;
	CString szMsg3;
	CString szMsg4;
	CString szMsg5;
	CString szMsg6;
	CString szMsg7;
	CString szMsg8;
	CString szMsg9;
	CString szMsg10;
	CString szMsg11;
	CString szMsg12;
};
