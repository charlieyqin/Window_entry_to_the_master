#pragma once


// CMyModalDialog �Ի���

class CMyModalDialog : public CDialog
{
	DECLARE_DYNAMIC(CMyModalDialog)

public:
	CMyModalDialog(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CMyModalDialog();

// �Ի�������
	enum { IDD = IDD_MODAL_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
