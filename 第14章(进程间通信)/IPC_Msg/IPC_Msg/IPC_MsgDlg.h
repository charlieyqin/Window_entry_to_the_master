// IPC_MsgDlg.h : ͷ�ļ�
//

#pragma once


// CIPC_MsgDlg �Ի���
class CIPC_MsgDlg : public CDialog
{
// ����
public:
	CIPC_MsgDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_IPC_MSG_DIALOG };

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
	afx_msg void OnEnChangeData();
public:
	afx_msg void OnBnClickedSend();
};
