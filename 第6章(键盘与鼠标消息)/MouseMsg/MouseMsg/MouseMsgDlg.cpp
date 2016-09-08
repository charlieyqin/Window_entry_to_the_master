// MouseMsgDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MouseMsg.h"
#include "MouseMsgDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CMouseMsgDlg �Ի���




CMouseMsgDlg::CMouseMsgDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMouseMsgDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMouseMsgDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMouseMsgDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_WM_ERASEBKGND()
	ON_WM_MOUSEMOVE()
	ON_WM_DESTROY()
	ON_WM_LBUTTONDBLCLK()
END_MESSAGE_MAP()


// CMouseMsgDlg ��Ϣ�������

BOOL CMouseMsgDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	this->BkBrush.CreateSolidBrush( RGB(255,255,255) ) ;
	this->pen.CreatePen ( PS_SOLID, 5, RGB(0,0,255) ) ;

	this->pdc = new CClientDC (this) ;
	this->pdc->SelectObject ( &this->pen ) ;

	this->GetWindowRect ( &this->WndRect ) ;
	this->OldPt.x = this->OldPt.y = 0 ;

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CMouseMsgDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMouseMsgDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ��������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù����ʾ��
//
HCURSOR CMouseMsgDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


BOOL CMouseMsgDlg::OnEraseBkgnd(CDC* pDC)
{
	CBrush* pOldBrush = pDC->SelectObject ( &this->BkBrush ) ;
	pDC->Rectangle ( &this->WndRect ) ;
	pDC->SelectObject ( pOldBrush ) ;
	return TRUE ;
}

// ��Ӧ����ƶ���Ϣ
// ����nFlags������ƶ�ʱ��״̬��Ϣ
// ����point����ǰ����λ��
void CMouseMsgDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// ������״̬�����������ƶ���������Ƿ��ڰ��µ�״̬
	if ( nFlags & MK_LBUTTON )
	{
		// pdc��Ԥ�ȱ���ĶԻ���ͻ�����DC
		// ʹ��MoveTo��LineTo��������
		this->pdc->MoveTo ( this->OldPt.x, this->OldPt.y ) ;
		this->pdc->LineTo ( point.x, point.y ) ;
	}
	// ���浱ǰ��
	this->OldPt = point ;	
	CDialog::OnMouseMove(nFlags, point);
}

void CMouseMsgDlg::OnDestroy()
{
	CDialog::OnDestroy();

	// TODO: �ڴ˴������Ϣ����������
	this->pdc->DeleteDC () ;
}

// ��Ӧ������˫����Ϣ
void CMouseMsgDlg::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	CClientDC cdc ( this ) ;
	// BkBrush��Ԥ�ȴ����İ�ɫ��ˢ
	CBrush* pOldBrush = cdc.SelectObject ( &this->BkBrush ) ;
	// ʹ�ð�ɫ��ˢ���������ͻ����򣬴ﵽ�����Ч��
	cdc.Rectangle ( &this->WndRect ) ;
	cdc.SelectObject ( pOldBrush ) ;
	CDialog::OnLButtonDblClk(nFlags, point);
}
