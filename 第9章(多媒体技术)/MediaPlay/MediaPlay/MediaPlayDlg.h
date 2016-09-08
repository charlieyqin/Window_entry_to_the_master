// MediaPlayDlg.h : ͷ�ļ�
//

#pragma once
#include "player.h"


// CMediaPlayDlg �Ի���
class CMediaPlayDlg : public CDialog
{
// ����
public:
	CMediaPlayDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MEDIAPLAY_DIALOG };

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
	CPlayer MediaPlayer;
public:
	afx_msg void OnEnChangeUrl();
public:
	afx_msg void OnBnClickedSet();
public:
	CString szMediaUrl;
};
