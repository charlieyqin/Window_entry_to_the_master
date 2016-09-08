// DDPToolDlg.h : ͷ�ļ�
//

#pragma once

#include "DDP.h"


// CDDPToolDlg �Ի���
class CDDPToolDlg : public CDialog
{
// ����
public:
	CDDPToolDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_DDPTOOL_DIALOG };

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
	virtual BOOL PreTranslateMessage(MSG* pMsg);

private:
	BOOL bStatus ;
	CDDP ddp ;
	friend UINT NewThread ( LPVOID lpParam ) ;
};
