// MyDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DAOSample.h"
#include "MyDlg.h"


// CMyDlg �Ի���

IMPLEMENT_DYNAMIC(CMyDlg, CDialog)

CMyDlg::CMyDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMyDlg::IDD, pParent)
	, szBookName(_T(""))
	, szAuthor(_T(""))
	, szPublish(_T(""))
	, nPrice(0)
{

}

CMyDlg::~CMyDlg()
{
}

void CMyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_BOOKNAME, szBookName);
	DDX_Text(pDX, IDC_AUTHOR, szAuthor);
	DDX_Text(pDX, IDC_PUBLISH, szPublish);
	DDX_Text(pDX, IDC_PRICE, nPrice);
}


BEGIN_MESSAGE_MAP(CMyDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CMyDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CMyDlg ��Ϣ�������

void CMyDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	this->UpdateData () ;
	if ( this->szBookName.IsEmpty() || this->szAuthor.IsEmpty() || this->szPublish.IsEmpty() )
	{
		this->MessageBox ( L"��Ϣ����Ϊ�գ�" ) ;
		return ;
	}

	OnOK();
}

BOOL CMyDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	this->SetWindowTextW ( this->bShowMode ? L"����鼮��Ϣ�Ի���" : L"�޸��鼮��Ϣ�Ի���" ) ;
	this->GetDlgItem(IDOK)->SetWindowTextW ( this->bShowMode ? L"���" : L"�޸�" ) ;

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

CString& CMyDlg::GetBookName ()
{
	return this->szBookName ;
}

CString& CMyDlg::GetAuthor ()
{
	return this->szAuthor ;
}

CString& CMyDlg::GetPublish () 
{
	return this->szPublish ;
}

UINT CMyDlg::GetPrice ()
{
	return this->nPrice ;
}

VOID CMyDlg::SetBookName ( CString str )
{
	this->szBookName = str ;
}

VOID CMyDlg::SetAuthor ( CString str ) 
{
	this->szAuthor = str ;
}

VOID CMyDlg::SetPublish ( CString str )
{
	this->szPublish = str ;
}

VOID CMyDlg::SetPrice ( UINT nPrice ) 
{
	this->nPrice = nPrice ;
}

VOID CMyDlg::SetMode ( BOOL bType ) 
{
	this->bShowMode = bType ;
}