// PipeDlg.h : ͷ�ļ�
//

#pragma once


// CPipeDlg �Ի���
class CPipeDlg : public CDialog
{
// ����
public:
	CPipeDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_PIPE_DIALOG };

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
	CString	szCmdPath ;
	CString szParam;
public:
	CString szOutput;
public:
	afx_msg void OnEnChangeParam();
public:
	afx_msg void OnBnClickedExecute();
	afx_msg void OnDestroy();
};
