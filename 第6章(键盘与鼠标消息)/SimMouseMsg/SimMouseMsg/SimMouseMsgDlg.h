// SimMouseMsgDlg.h : ͷ�ļ�
//

#pragma once


// CSimMouseMsgDlg �Ի���
class CSimMouseMsgDlg : public CDialog
{
// ����
public:
	CSimMouseMsgDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_SIMMOUSEMSG_DIALOG };

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
	afx_msg void OnBnClickedLeftDown();
public:
	afx_msg void OnBnClickedRightDown();
public:
	afx_msg void OnBnClickedMouseMove();

private:
	CRect	PaintRect ;	// �����ͼ����
	CPen	FramePen ;	// ������ο�ı���ʹ�õĻ���
	UINT	nType ;		// ����ģ�����Ϣ���ͣ�1�����������2���Ҽ�������3���ƶ���꣩
	CBrush	RedBrush ;	// ��ɫ��ˢ
	CBrush	GreenBrush ;	// ��ɫ��ˢ
	CBrush	BlueBrush ;	// ��ɫ��ˢ

	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};
