// BrushDlg.h : ͷ�ļ�
//

#pragma once

typedef struct _MY_ELLIPSE {
	CRect	rect ;
	CBrush	brush ;
} MY_ELLIPSE ;


// CBrushDlg �Ի���
class CBrushDlg : public CDialog
{
// ����
public:
	CBrushDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_BRUSH_DIALOG };

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
	MY_ELLIPSE	MyEllipse[8] ;
};
