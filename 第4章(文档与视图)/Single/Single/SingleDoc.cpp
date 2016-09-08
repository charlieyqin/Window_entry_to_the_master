// SingleDoc.cpp : CSingleDoc ���ʵ��
//

#include "stdafx.h"
#include "Single.h"

#include "SingleDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSingleDoc

IMPLEMENT_DYNCREATE(CSingleDoc, CDocument)

BEGIN_MESSAGE_MAP(CSingleDoc, CDocument)
END_MESSAGE_MAP()


// CSingleDoc ����/����

CSingleDoc::CSingleDoc()
{
	// TODO: �ڴ����һ���Թ������
	this->ResetGrid () ;
}

CSingleDoc::~CSingleDoc()
{
}

//BOOL CSingleDoc::OnNewDocument()
//{
//	if (!CDocument::OnNewDocument())
//		return FALSE;
//
//	// TODO: �ڴ�������³�ʼ������
//	// (SDI �ĵ������ø��ĵ�)
//
//	return TRUE;
//}




// CSingleDoc ���л�

void CSingleDoc::Serialize(CArchive& ar)
{	
	if (ar.IsStoring())
	{
		for ( int i = 0; i < MAX_X_NUM; i++ )
		{
			for ( int j = 0; j < MAX_Y_NUM; j++) 
				ar << this->grid[i][j] ;
		}
	}
	else
	{
		for ( int i = 0; i < MAX_X_NUM; i++ )
		{
			for ( int j = 0; j < MAX_Y_NUM; j++) 
				ar >> this->grid[i][j] ;
		}
	}
}


// CSingleDoc ���

#ifdef _DEBUG
void CSingleDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CSingleDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CSingleDoc ����
void CSingleDoc::SetGrid ( int x, int y )
{
	if ( x < 0 || x >= MAX_X_NUM )
		return ;
	if ( y < 0 || y >= MAX_Y_NUM )
		return ;

	this->grid[x][y] = !this->grid[x][y] ;
}

BOOL CSingleDoc::GetGridStatus ( int x, int y )
{
	if ( x < 0 || x >= MAX_X_NUM )
		return FALSE;
	if ( y < 0 || y >= MAX_Y_NUM )
		return FALSE;
	return this->grid[x][y] ;
}

VOID CSingleDoc::ResetGrid ()
{
	memset ( this->grid, 0, sizeof(this->grid) ) ;
}
void CSingleDoc::SetTitle(LPCTSTR lpszTitle)
{
	// TODO: �ڴ����ר�ô����/����û���
	lpszTitle = L"[��4��]���ĵ�Ӧ�ó������ĵ����л�" ;
	CDocument::SetTitle(lpszTitle);
}

BOOL CSingleDoc::OnNewDocument()
{
	// TODO: �ڴ����ר�ô����/����û���
	this->ResetGrid () ;
	return CDocument::OnNewDocument();
}
