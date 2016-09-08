// BitmapDlg.h : ͷ�ļ�
//

#pragma once

typedef struct _MY_BITMAP { 
	CRect	rect ;
	CBitmap bmp ;
} MY_BITMAP ;

// CBitmapDlg �Ի���
class CBitmapDlg : public CDialog
{
// ����
public:
	CBitmapDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_BITMAP_DIALOG };

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
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);

private:
	MY_BITMAP MyBmp[9] ;
};
