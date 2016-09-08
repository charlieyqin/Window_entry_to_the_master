// DefSingleView.cpp : CDefSingleView ���ʵ��
//

#include "stdafx.h"
#include "DefSingle.h"

#include "DefSingleDoc.h"
#include "DefSingleView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDefSingleView

IMPLEMENT_DYNCREATE(CDefSingleView, CView)

BEGIN_MESSAGE_MAP(CDefSingleView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CDefSingleView ����/����

CDefSingleView::CDefSingleView()
{
	// TODO: �ڴ˴���ӹ������

}

CDefSingleView::~CDefSingleView()
{
}

BOOL CDefSingleView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CDefSingleView ����

void CDefSingleView::OnDraw(CDC* /*pDC*/)
{
	CDefSingleDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CDefSingleView ��ӡ

BOOL CDefSingleView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CDefSingleView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CDefSingleView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}


// CDefSingleView ���

#ifdef _DEBUG
void CDefSingleView::AssertValid() const
{
	CView::AssertValid();
}

void CDefSingleView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDefSingleDoc* CDefSingleView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDefSingleDoc)));
	return (CDefSingleDoc*)m_pDocument;
}
#endif //_DEBUG


// CDefSingleView ��Ϣ�������
