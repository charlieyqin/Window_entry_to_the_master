// CHInputDemonDlg.h : ͷ�ļ�
//

#pragma once

#include "PYTrie.h"
#include "LXWord.h"


// CCHInputDemonDlg �Ի���
class CCHInputDemonDlg : public CDialog
{
// ����
public:
	CCHInputDemonDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_CHINPUTDEMON_DIALOG };

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
	CString szString;
public:
	afx_msg void OnBnClickedEmpty();
public:
	CString szPY;
public:
	UINT nTotalWord;
public:
	UINT nTotalPage;
public:
	UINT nCurPage;
public:
	afx_msg void OnEnChangePinyin();


private:
	CPYTrie PYTrie ;
	CLXWord LXWord ;
	CString szSearchWord;
	VOID	OnNum ( UINT nIndex ) ;
	VOID	OnPrevPage () ;
	VOID	OnNextPage () ;
	VOID	UpdateWord () ;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
