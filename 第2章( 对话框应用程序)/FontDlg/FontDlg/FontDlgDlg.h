// FontDlgDlg.h : ͷ�ļ�
//

#pragma once


// CFontDlgDlg �Ի���
class CFontDlgDlg : public CDialog
{
// ���� 
public:
	CFontDlgDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_FONTDLG_DIALOG };

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
	afx_msg void OnBnClickedSetFont();

private:
	COLORREF	color ;
	LOGFONT		LogFont ;
};
