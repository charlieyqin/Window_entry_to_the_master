// DefSingleDoc.cpp : CDefSingleDoc ���ʵ��
//

#include "stdafx.h"
#include "DefSingle.h"

#include "DefSingleDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDefSingleDoc

IMPLEMENT_DYNCREATE(CDefSingleDoc, CDocument)

BEGIN_MESSAGE_MAP(CDefSingleDoc, CDocument)
END_MESSAGE_MAP()


// CDefSingleDoc ����/����

CDefSingleDoc::CDefSingleDoc()
{
	// TODO: �ڴ����һ���Թ������

}

CDefSingleDoc::~CDefSingleDoc()
{
}

BOOL CDefSingleDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}




// CDefSingleDoc ���л�

void CDefSingleDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: �ڴ���Ӵ洢����
	}
	else
	{
		// TODO: �ڴ���Ӽ��ش���
	}
}


// CDefSingleDoc ���

#ifdef _DEBUG
void CDefSingleDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CDefSingleDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CDefSingleDoc ����

void CDefSingleDoc::SetTitle(LPCTSTR lpszTitle)
{
	// TODO: �ڴ����ר�ô����/����û���
	lpszTitle = L"[��4��]���ĵ�Ӧ�ó���ʾ��" ;

	CDocument::SetTitle(lpszTitle);
}
