// SimKeyMsgDlg.h : ͷ�ļ�
//

#pragma once


// CSimKeyMsgDlg �Ի���
class CSimKeyMsgDlg : public CDialog
{
// ����
public:
	CSimKeyMsgDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_SIMKEYMSG_DIALOG };

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
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedUp();
	afx_msg void OnBnClickedDown();
	afx_msg void OnBnClickedLeft();
	afx_msg void OnBnClickedRight();
	afx_msg void OnBnClickedWinR();
	afx_msg void OnBnClickedWinU();
	afx_msg void OnBnClickedCtrlShift();
	afx_msg void OnBnClickedAltTab();
};
