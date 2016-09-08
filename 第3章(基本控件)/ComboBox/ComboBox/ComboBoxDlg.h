// ComboBoxDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"


// CComboBoxDlg �Ի���
class CComboBoxDlg : public CDialog
{
// ����
public:
	CComboBoxDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_COMBOBOX_DIALOG };

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
	afx_msg void OnEnChangeEdit2();
	afx_msg void OnBnClickedAdd();
	afx_msg void OnCbnSelchangeCombo();
	afx_msg void OnCbnSelchangeCombo2();

public:
	CString		szFruitName;			// �µ�ˮ������
	CString		szCurName,szCurName2;	// ��ǰѡ���ˮ������
	CComboBox	MyComboBox,MyComboBox2;	// ������Ͽ����
};
