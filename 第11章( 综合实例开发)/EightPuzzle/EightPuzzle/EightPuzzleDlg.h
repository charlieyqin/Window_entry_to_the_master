// EightPuzzleDlg.h : ͷ�ļ�
//

#pragma once

#include "EightPuzzleGame.h"


// CEightPuzzleDlg �Ի���
class CEightPuzzleDlg : public CDialog
{
// ����
public:
	CEightPuzzleDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_EIGHTPUZZLE_DIALOG };

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
	CWinThread*			pNewThread ;
	BOOL				isShowing ;
	CEightPuzzleGame	EightPuzzle ;
	friend UINT ShowProc ( LPVOID lpParam ) ;

public:
	afx_msg void OnBnClickedRandomBeg();
	afx_msg void OnBnClickedRestart();
	afx_msg void OnBnClickedBegShow();
	afx_msg void OnBnClickedEndShow();
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);

public:
	void MoveUp();
	void MoveLeft();
	void MoveDown();
	void MoveRight();
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
