#pragma once


// CAddInfoDlg �Ի���

class CAddInfoDlg : public CDialog
{
	DECLARE_DYNAMIC(CAddInfoDlg)

public:
	CAddInfoDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CAddInfoDlg();

// �Ի�������
	enum { IDD = IDD_ADD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString szName;
public:
	CString szId;
public:
	CString szGender;
public:
	CString szAddr;
public:
	afx_msg void OnBnClickedAdd();
public:
	afx_msg void OnEnChangeName();
public:
	afx_msg void OnEnChangeId();
public:
	afx_msg void OnEnChangeGender();
public:
	afx_msg void OnEnChangeAddr();

public:
	CString NEW_GetName() ;
	CString NEW_GetId () ;
	CString NEW_GetGender () ;
	CString NEW_GetAddr () ;
};
