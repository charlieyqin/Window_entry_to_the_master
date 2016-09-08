// ReserveAndSubmitDlg.h : ͷ�ļ�
//

#pragma once

#include "Region.h"
#include "afxwin.h"


// CReserveAndSubmitDlg �Ի���
class CReserveAndSubmitDlg : public CDialog
{
// ����
public:
	CReserveAndSubmitDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_RESERVEANDSUBMIT_DIALOG };

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
	afx_msg void OnBnClickedAlloc();
public:
	afx_msg void OnBnClickedRelease();

private:
	LPVOID	lpData ;
	CRegion	PaintRegion ;
	CBrush	WhiteBrush ;
	CBrush	GreyBrush ;
	CBrush	BlackBrush ;
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	CString szBaseAddr;
	CString szCurAddr;
};
