// UDPServerDlg.h : ͷ�ļ�
//

#pragma once


// CUDPServerDlg �Ի���
class CUDPServerDlg : public CDialog
{
// ����
public:
	CUDPServerDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_UDPSERVER_DIALOG };

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
	HANDLE hThread ;
	friend DWORD WINAPI ServerThread ( LPVOID lParam ) ;
};
