// MyPage3.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ProperyDialog_Wizard.h"
#include "MyPage3.h"


// CMyPage3 �Ի���

IMPLEMENT_DYNAMIC(CMyPage3, CPropertyPage)

CMyPage3::CMyPage3()
	: CPropertyPage(CMyPage3::IDD)
{

}

CMyPage3::~CMyPage3()
{
}

void CMyPage3::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CMyPage3, CPropertyPage)
END_MESSAGE_MAP()


// CMyPage3 ��Ϣ�������

BOOL CMyPage3::OnSetActive()
{
	// TODO: �ڴ����ר�ô����/����û���
	((CPropertySheet*)this->GetParent())->SetWizardButtons ( PSWIZB_BACK|PSWIZB_FINISH ) ;
	return CPropertyPage::OnSetActive();
}
