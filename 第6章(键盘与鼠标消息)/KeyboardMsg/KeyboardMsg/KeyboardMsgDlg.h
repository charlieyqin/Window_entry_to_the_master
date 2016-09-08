// KeyboardMsgDlg.h : ͷ�ļ�
//

#pragma once


// CKeyboardMsgDlg �Ի���
class CKeyboardMsgDlg : public CDialog
{
// ����
public:
	CKeyboardMsgDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_KEYBOARDMSG_DIALOG };

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
	BOOL	bType ;		// ��ʶ��Ӧ��������Ϣ����ȫ����Ϣ
	CRect	ValidRect ;	// ���ƶ�����Ч����
	CBitmap FaceBmp ;	// ����λͼ����
	CRect	FaceRect ;	// ����λͼ�ĵ�ǰ����
	VOID	MoveFace ( UINT nDir ) ;
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedLocal();
	afx_msg void OnBnClickedTotal();
};
