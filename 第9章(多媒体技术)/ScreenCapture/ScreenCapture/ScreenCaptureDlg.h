// ScreenCaptureDlg.h : ͷ�ļ�
//

#pragma once


// CScreenCaptureDlg �Ի���
class CScreenCaptureDlg : public CDialog
{
// ����
public:
	CScreenCaptureDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_SCREENCAPTURE_DIALOG };

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
	BOOL	bStatus ;
	UINT	nWidth, nHeight ;
	virtual BOOL PreTranslateMessage(MSG* pMsg);

public:
	friend DWORD WINAPI CaptureThread ( LPVOID lParam ) ;
};
