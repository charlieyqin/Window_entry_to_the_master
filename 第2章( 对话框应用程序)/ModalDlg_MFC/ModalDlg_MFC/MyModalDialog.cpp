// MyModalDialog.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ModalDlg_MFC.h"
#include "MyModalDialog.h"


// CMyModalDialog �Ի���

IMPLEMENT_DYNAMIC(CMyModalDialog, CDialog)

CMyModalDialog::CMyModalDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CMyModalDialog::IDD, pParent)
{

}

CMyModalDialog::~CMyModalDialog()
{
}

void CMyModalDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CMyModalDialog, CDialog)
END_MESSAGE_MAP()


// CMyModalDialog ��Ϣ�������
