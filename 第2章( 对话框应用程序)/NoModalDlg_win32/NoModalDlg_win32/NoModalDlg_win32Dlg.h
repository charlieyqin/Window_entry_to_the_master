// NoModalDlg_win32Dlg.h : ͷ�ļ�
//

#pragma once


// CNoModalDlg_win32Dlg �Ի���
class CNoModalDlg_win32Dlg : public CDialog
{
// ����
public:
	CNoModalDlg_win32Dlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_NOMODALDLG_WIN32_DIALOG };

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
	afx_msg void OnBnClickedCreateDialog();
};
