#pragma once


// CMyNoModalDialog �Ի���

class CMyNoModalDialog : public CDialog
{
	DECLARE_DYNAMIC(CMyNoModalDialog)

public:
	CMyNoModalDialog(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CMyNoModalDialog();

// �Ի�������
	enum { IDD = IDD_NOMODAL_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
