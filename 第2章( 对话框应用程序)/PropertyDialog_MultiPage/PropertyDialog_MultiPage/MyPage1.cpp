// MyPage1.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PropertyDialog_MultiPage.h"
#include "MyPage1.h"


// CMyPage1 �Ի���

IMPLEMENT_DYNAMIC(CMyPage1, CPropertyPage)

CMyPage1::CMyPage1()
	: CPropertyPage(CMyPage1::IDD)
{

}

CMyPage1::~CMyPage1()
{
}

void CMyPage1::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CMyPage1, CPropertyPage)
END_MESSAGE_MAP()


// CMyPage1 ��Ϣ�������
