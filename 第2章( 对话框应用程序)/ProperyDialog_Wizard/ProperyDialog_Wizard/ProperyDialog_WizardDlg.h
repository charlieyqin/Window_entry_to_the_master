// ProperyDialog_WizardDlg.h : ͷ�ļ�
//

#pragma once


// CProperyDialog_WizardDlg �Ի���
class CProperyDialog_WizardDlg : public CDialog
{
// ����
public:
	CProperyDialog_WizardDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_PROPERYDIALOG_WIZARD_DIALOG };

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
};
