// TestAStarDlg.h : ͷ�ļ�
//

#pragma once


// CTestAStarDlg �Ի���
class CTestAStarDlg : public CDialog
{
// ����
public:
	CTestAStarDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_TESTASTAR_DIALOG };

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
	afx_msg void OnBnClickedGenMap();
public:
	afx_msg void OnBnClickedSearchPath();
public:
	afx_msg void OnEnChangeSize();
public:
	afx_msg void OnEnChangeRate();

public:
	UINT	nMapSize, nRate ;
	CListBox	OutputList ;
public:
	afx_msg void OnBnClickedButton1();
};
