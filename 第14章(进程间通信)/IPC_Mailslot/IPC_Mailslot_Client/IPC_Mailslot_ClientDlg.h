// IPC_Mailslot_ClientDlg.h : ͷ�ļ�
//

#pragma once


// CIPC_Mailslot_ClientDlg �Ի���
class CIPC_Mailslot_ClientDlg : public CDialog
{
// ����
public:
	CIPC_Mailslot_ClientDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_IPC_MAILSLOT_CLIENT_DIALOG };

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
	CString szData;
public:
	afx_msg void OnBnClickedSend();
};
