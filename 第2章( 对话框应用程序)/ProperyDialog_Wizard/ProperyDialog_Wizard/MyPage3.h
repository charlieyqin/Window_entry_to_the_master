#pragma once


// CMyPage3 �Ի���

class CMyPage3 : public CPropertyPage
{
	DECLARE_DYNAMIC(CMyPage3)

public:
	CMyPage3();
	virtual ~CMyPage3();

// �Ի�������
	enum { IDD = IDD_PROPPAGE_3 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnSetActive();
};
