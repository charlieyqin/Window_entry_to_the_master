// TCPClientDlg.h : ͷ�ļ�
//

#pragma once


// CTCPClientDlg �Ի���
class CTCPClientDlg : public CDialog
{
// ����
public:
	CTCPClientDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_TCPCLIENT_DIALOG };

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
	afx_msg void OnEnChangeDataA();
public:
	afx_msg void OnEnChangeDataB();
public:
	UINT nDataA;
public:
	UINT nDataB;
public:
	afx_msg void OnBnClickedSend();
public:
	UINT nDataC;
public:
	CString szSrvIp;
public:
	afx_msg void OnEnChangeIp();
};
