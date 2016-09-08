// IPC_ShareMemDlg.h : ͷ�ļ�
//

#pragma once


// CIPC_ShareMemDlg �Ի���
class CIPC_ShareMemDlg : public CDialog
{
// ����
public:
	CIPC_ShareMemDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_IPC_SHAREMEM_DIALOG };

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

private:
	HANDLE	hMapFile ;
	LPVOID	lpData ;
	afx_msg void OnBnClickedCreate();
	afx_msg void OnBnClickedClose();
	afx_msg void OnBnClickedWrite();
	afx_msg void OnEnChangeData();
};
