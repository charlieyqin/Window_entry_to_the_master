// BlowfishCaluDlg.h : ͷ�ļ�
//

#pragma once

#include "Blowfish.h"


// CBlowfishCaluDlg �Ի���
class CBlowfishCaluDlg : public CDialog
{
// ����
public:
	CBlowfishCaluDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_BLOWFISHCALU_DIALOG };

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
	afx_msg void OnEnChangeKey();

private:
	BYTE	szKey[MAX_KEY_SIZE] ;
	BYTE	szMsg[DEF_BUF_SIZE] ;
	BYTE	ECB_szEnMsg[DEF_BUF_SIZE] ;
	BYTE	ECB_szDeMsg[DEF_BUF_SIZE] ;
	BYTE	CBC_szEnMsg[DEF_BUF_SIZE] ;
	BYTE	CBC_szDeMsg[DEF_BUF_SIZE] ;

	CBlowfish	Blowfish ;
	afx_msg void OnBnClickedCoding();
};
