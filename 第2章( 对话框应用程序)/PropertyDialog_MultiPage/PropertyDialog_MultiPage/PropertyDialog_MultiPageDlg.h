// PropertyDialog_MultiPageDlg.h : ͷ�ļ�
//

#pragma once


// CPropertyDialog_MultiPageDlg �Ի���
class CPropertyDialog_MultiPageDlg : public CDialog
{
// ����
public:
	CPropertyDialog_MultiPageDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_PROPERTYDIALOG_MULTIPAGE_DIALOG };

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
