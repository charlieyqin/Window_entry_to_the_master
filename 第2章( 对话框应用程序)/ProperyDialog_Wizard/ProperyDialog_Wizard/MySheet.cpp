// MySheet.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ProperyDialog_Wizard.h"
#include "MySheet.h"


// CMySheet

IMPLEMENT_DYNAMIC(CMySheet, CPropertySheet)

CMySheet::CMySheet(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{

}

CMySheet::CMySheet(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
	this->AddPage ( &page1 ) ;
	this->AddPage ( &page2 ) ;
	this->AddPage ( &page3 ) ;
}

CMySheet::~CMySheet()
{
}


BEGIN_MESSAGE_MAP(CMySheet, CPropertySheet)
END_MESSAGE_MAP()


// CMySheet ��Ϣ�������

INT_PTR CMySheet::DoModal()
{
	// TODO: �ڴ����ר�ô����/����û���
	return CPropertySheet::DoModal();
}
