// DefMultipleDoc.cpp : CDefMultipleDoc ���ʵ��
//

#include "stdafx.h"
#include "DefMultiple.h"

#include "DefMultipleDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDefMultipleDoc

IMPLEMENT_DYNCREATE(CDefMultipleDoc, CDocument)

BEGIN_MESSAGE_MAP(CDefMultipleDoc, CDocument)
END_MESSAGE_MAP()


// CDefMultipleDoc ����/����

CDefMultipleDoc::CDefMultipleDoc()
{
	// TODO: �ڴ����һ���Թ������

}

CDefMultipleDoc::~CDefMultipleDoc()
{
}

BOOL CDefMultipleDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}




// CDefMultipleDoc ���л�

void CDefMultipleDoc::Serialize(CArchive& ar)
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


// CDefMultipleDoc ���

#ifdef _DEBUG
void CDefMultipleDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CDefMultipleDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CDefMultipleDoc ����

void CDefMultipleDoc::SetTitle(LPCTSTR lpszTitle)
{
	// TODO: �ڴ����ר�ô����/����û���
	lpszTitle = L"[��4��]���ĵ�Ӧ�ó���ʾ��" ;

	CDocument::SetTitle(lpszTitle);
}
