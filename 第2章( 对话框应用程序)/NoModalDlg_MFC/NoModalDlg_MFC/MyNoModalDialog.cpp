// MyNoModalDialog.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "NoModalDlg_MFC.h"
#include "MyNoModalDialog.h"


// CMyNoModalDialog �Ի���

IMPLEMENT_DYNAMIC(CMyNoModalDialog, CDialog)

CMyNoModalDialog::CMyNoModalDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CMyNoModalDialog::IDD, pParent)
{

}

CMyNoModalDialog::~CMyNoModalDialog()
{
}

void CMyNoModalDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CMyNoModalDialog, CDialog)
END_MESSAGE_MAP()


// CMyNoModalDialog ��Ϣ�������
