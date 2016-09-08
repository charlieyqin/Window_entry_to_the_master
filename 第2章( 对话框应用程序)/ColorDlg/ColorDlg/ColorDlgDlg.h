// ColorDlgDlg.h : ͷ�ļ�
//

#pragma once


// CColorDlgDlg �Ի���
class CColorDlgDlg : public CDialog
{
// ����
public:
	CColorDlgDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_COLORDLG_DIALOG };

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
	BYTE	r, g, b;		// ���ڱ��������õ���ɫֵ
	CRect	ColorShowRect ;	// �������ָ����ɫ������
public:
	afx_msg void OnBnClickedSetColor();
	afx_msg void OnEnChangeR();
	afx_msg void OnEnChangeG();
	afx_msg void OnEnChangeB();
};
