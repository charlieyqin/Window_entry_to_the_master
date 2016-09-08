// SingleView.cpp : CSingleView ���ʵ��
//

#include "stdafx.h"
#include "Single.h"

#include "SingleDoc.h"
#include "SingleView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define START_POS_X	20
#define START_POS_Y 20
#define GRID_SIZE	8


// CSingleView

IMPLEMENT_DYNCREATE(CSingleView, CView)

BEGIN_MESSAGE_MAP(CSingleView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_LBUTTONUP()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

// CSingleView ����/����

CSingleView::CSingleView()
{
	// TODO: �ڴ˴���ӹ������

}

CSingleView::~CSingleView()
{
}

BOOL CSingleView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CSingleView ����

void CSingleView::OnDraw(CDC* pDC)
{
	CSingleDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
	// ȡ�ÿͻ����򣬲�ת��Ϊ�������
	CRect WndRect ;
	this->GetWindowRect ( &WndRect ) ;
	this->ScreenToClient ( &WndRect ) ;

	CDC		mdc ;			// �ڴ�DC
	CBitmap bmp ;			// ��ʱλͼ��Ϊ�ڴ�DC�ṩ��ͼ����
	CPen	FramePen ;		// �����ο�ʹ�û���
	CPen	PtPen ;			// ����ʱʹ�õĻ���
	CBrush	BkBrush ;		// ������ˢ����ɫ
	CBrush	PtBrush ;		// �����õĻ�ˢ����ɫ

	// ��ʼ��GDI����
	mdc.CreateCompatibleDC ( pDC ) ;
	bmp.CreateCompatibleBitmap ( pDC, WndRect.Width(), WndRect.Height() ) ;
	mdc.SelectObject ( &bmp ) ;
	FramePen.CreatePen ( PS_SOLID, 3, RGB(0,0,0) ) ;
	mdc.SelectObject ( &FramePen ) ;
	BkBrush.CreateSolidBrush ( RGB(128,128,128) ) ;

	// ���ƻ�ɫ�ı�������
	mdc.FillRect ( &WndRect, &BkBrush ) ;

	// ���ƾ�������
	int width = MAX_X_NUM * GRID_SIZE, height = MAX_Y_NUM * GRID_SIZE ;
	mdc.Rectangle ( START_POS_X, START_POS_Y, width+START_POS_X, height+START_POS_Y ) ;

	PtPen.CreatePen ( PS_SOLID, 1, RGB(0,0,0) ) ;
	mdc.SelectObject ( &PtPen ) ;
	PtBrush.CreateSolidBrush ( RGB(255,0,0) ) ;
	mdc.SelectObject ( &PtBrush ) ;

	// ö��CSingleDoc���еĵ㼯����
	int i, j ;
	for ( i = 0; i < MAX_X_NUM; i++ )
	{
		for ( j = 0; j < MAX_Y_NUM; j++ )
		{
			// ���ָ�����״̬�����ΪTRUE����ָ��λ�û��ƺ��
			if ( pDoc->GetGridStatus(i,j) )
			{
				int x = START_POS_X + GRID_SIZE * i ;
				int y = START_POS_Y + GRID_SIZE * j ;
				mdc.Ellipse ( x, y, x + GRID_SIZE, y + GRID_SIZE ) ;
			}
		}
	}

	// ���ڴ�DC���Ƶ���ĻDC
	pDC->BitBlt( 0, 0, WndRect.Width(), WndRect.Height(), &mdc, 0, 0, SRCCOPY ) ;

	//ɾ����ʱGDI����
	bmp.DeleteObject () ;
	FramePen.DeleteObject () ;
	PtPen.DeleteObject () ;
	BkBrush.DeleteObject () ;
	PtBrush.DeleteObject () ;
	mdc.DeleteDC() ;
}


// CSingleView ��ӡ

BOOL CSingleView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CSingleView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CSingleView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}


// CSingleView ���

#ifdef _DEBUG
void CSingleView::AssertValid() const
{
	CView::AssertValid();
}

void CSingleView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSingleDoc* CSingleView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSingleDoc)));
	return (CSingleDoc*)m_pDocument;
}
#endif //_DEBUG


// CSingleView ��Ϣ�������

void CSingleView::OnLButtonUp(UINT nFlags, CPoint point)
{
	if ( point.x < START_POS_X || point.x >= START_POS_X+GRID_SIZE*MAX_X_NUM )
		return ;
	if ( point.y < START_POS_Y || point.y >= START_POS_Y+GRID_SIZE*MAX_Y_NUM )
		return ;

	CSingleDoc* pDoc = GetDocument();
	if ( pDoc )
	{
		int x = ( point.x - START_POS_X ) / GRID_SIZE ;
		int y = ( point.y - START_POS_Y ) / GRID_SIZE ;
		pDoc->SetGrid ( x, y ) ;
		pDoc->SetModifiedFlag () ;
		this->Invalidate ( FALSE ) ;
	}
	else
	{
		this->MessageBox ( L"Error!" ) ;
	}
	CView::OnLButtonUp(nFlags, point);
}

BOOL CSingleView::OnEraseBkgnd(CDC* pDC)
{
	return TRUE ;
}
