// MyPage2.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PropertyDialog_MultiPage.h"
#include "MyPage2.h"


// CMyPage2 �Ի���

IMPLEMENT_DYNAMIC(CMyPage2, CPropertyPage)

CMyPage2::CMyPage2()
	: CPropertyPage(CMyPage2::IDD)
{

}

CMyPage2::~CMyPage2()
{
}

void CMyPage2::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CMyPage2, CPropertyPage)
END_MESSAGE_MAP()


// CMyPage2 ��Ϣ�������
