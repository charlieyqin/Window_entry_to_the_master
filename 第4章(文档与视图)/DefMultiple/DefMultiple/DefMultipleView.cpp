// DefMultipleView.cpp : CDefMultipleView ���ʵ��
//

#include "stdafx.h"
#include "DefMultiple.h"

#include "DefMultipleDoc.h"
#include "DefMultipleView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDefMultipleView

IMPLEMENT_DYNCREATE(CDefMultipleView, CView)

BEGIN_MESSAGE_MAP(CDefMultipleView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CDefMultipleView ����/����

CDefMultipleView::CDefMultipleView()
{
	// TODO: �ڴ˴���ӹ������

}

CDefMultipleView::~CDefMultipleView()
{
}

BOOL CDefMultipleView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CDefMultipleView ����

void CDefMultipleView::OnDraw(CDC* /*pDC*/)
{
	CDefMultipleDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CDefMultipleView ��ӡ

BOOL CDefMultipleView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CDefMultipleView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CDefMultipleView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}


// CDefMultipleView ���

#ifdef _DEBUG
void CDefMultipleView::AssertValid() const
{
	CView::AssertValid();
}

void CDefMultipleView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDefMultipleDoc* CDefMultipleView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDefMultipleDoc)));
	return (CDefMultipleDoc*)m_pDocument;
}
#endif //_DEBUG


// CDefMultipleView ��Ϣ�������
