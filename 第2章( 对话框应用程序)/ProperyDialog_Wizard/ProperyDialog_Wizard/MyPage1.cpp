// MyPage1.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ProperyDialog_Wizard.h"
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

LRESULT CMyPage1::OnWizardBack()
{
	// TODO: �ڴ����ר�ô����/����û���

	return CPropertyPage::OnWizardBack();
}

BOOL CMyPage1::OnWizardFinish()
{
	// TODO: �ڴ����ר�ô����/����û���

	return CPropertyPage::OnWizardFinish();
}

LRESULT CMyPage1::OnWizardNext()
{
	// TODO: �ڴ����ר�ô����/����û���

	return CPropertyPage::OnWizardNext();
}

BOOL CMyPage1::OnSetActive()
{
	// TODO: �ڴ����ר�ô����/����û���
	((CPropertySheet*)this->GetParent())->SetWizardButtons ( PSWIZB_NEXT ) ;
	return CPropertyPage::OnSetActive();
}

INT_PTR CMyPage1::DoModal()
{
	// TODO: �ڴ����ר�ô����/����û���
	return CPropertyPage::DoModal();
}
