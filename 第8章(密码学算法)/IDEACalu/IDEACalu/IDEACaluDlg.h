// IDEACaluDlg.h : ͷ�ļ�
//

#pragma once

#include "IDEA.h"


#define DEF_BUF_SIZE 1024

// CIDEACaluDlg �Ի���
class CIDEACaluDlg : public CDialog
{
// ����
public:
	CIDEACaluDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_IDEACALU_DIALOG };

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

private:
	CIDEA idea ;
	afx_msg void OnBnClickedEnDe();
	afx_msg void OnBnClickedSetKey();

private:
	UINT nEnDataSize ;
	BYTE bMsg[DEF_BUF_SIZE] ;
	BYTE bEnMsg[DEF_BUF_SIZE] ;
	BYTE bDeMsg[DEF_BUF_SIZE] ;
};
