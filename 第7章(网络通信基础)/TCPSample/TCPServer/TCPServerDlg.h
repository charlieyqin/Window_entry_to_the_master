// TCPServerDlg.h : ͷ�ļ�
//

#pragma once


// CTCPServerDlg �Ի���
class CTCPServerDlg : public CDialog
{
// ����
public:
	CTCPServerDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_TCPSERVER_DIALOG };

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
	UINT nDataA;
public:
	UINT nDataB;
public:
	UINT nDataC;
public:
	BOOL	bStatus ;
	HANDLE	hThread ;
	friend	DWORD WINAPI ServerThread ( LPVOID lParam ) ;
};
