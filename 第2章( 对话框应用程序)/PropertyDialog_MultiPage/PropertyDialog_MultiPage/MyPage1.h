#pragma once


// CMyPage1 �Ի���

class CMyPage1 : public CPropertyPage
{
	DECLARE_DYNAMIC(CMyPage1)

public:
	CMyPage1();
	virtual ~CMyPage1();

// �Ի�������
	enum { IDD = IDD_PROPPAGE_1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
