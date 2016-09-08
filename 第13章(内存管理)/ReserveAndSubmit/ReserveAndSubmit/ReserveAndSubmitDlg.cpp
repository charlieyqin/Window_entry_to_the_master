// ReserveAndSubmitDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ReserveAndSubmit.h"
#include "ReserveAndSubmitDlg.h"

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


// CReserveAndSubmitDlg �Ի���




CReserveAndSubmitDlg::CReserveAndSubmitDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CReserveAndSubmitDlg::IDD, pParent)
	, szBaseAddr(_T(""))
	, szCurAddr(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CReserveAndSubmitDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_BASE_ADDR, szBaseAddr);
	DDX_Text(pDX, IDC_CUR_ADDR, szCurAddr);
}

BEGIN_MESSAGE_MAP(CReserveAndSubmitDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_ALLOC, &CReserveAndSubmitDlg::OnBnClickedAlloc)
	ON_BN_CLICKED(IDC_RELEASE, &CReserveAndSubmitDlg::OnBnClickedRelease)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()


// CReserveAndSubmitDlg ��Ϣ�������

BOOL CReserveAndSubmitDlg::OnInitDialog()
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
	this->PaintRegion.InitialRect ( CRect(20,30,380,70) ) ;
	this->WhiteBrush.CreateSolidBrush ( RGB(255,255,255) ) ;
	this->GreyBrush.CreateSolidBrush ( RGB(128,128,128) ) ;
	this->BlackBrush.CreateSolidBrush ( RGB(0,0,0) ) ;

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CReserveAndSubmitDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CReserveAndSubmitDlg::OnPaint()
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
		CRect rect ;
		this->GetWindowRect( &rect ) ;
		this->ScreenToClient ( &rect ) ;

		CClientDC dc(this) ;
		CDC	mdc ;
		mdc.CreateCompatibleDC ( &dc ) ;
		CBitmap bmp ;
		bmp.CreateCompatibleBitmap ( &dc, rect.Width(), rect.Height() ) ;
		CBitmap* pOldBmp = mdc.SelectObject ( &bmp ) ;
		CBrush* pOldBrush ;

		pOldBrush = mdc.SelectObject ( &this->WhiteBrush ) ;
		mdc.Rectangle ( this->PaintRegion.GetStautsRect() ) ;
		
		if ( this->PaintRegion.IsValid() )
		{
			for ( int i = 0; i < MAX_PAGE_NUM; i++ )
			{
				if ( this->PaintRegion.GetStatusByIndex(i) )
					mdc.SelectObject ( &this->BlackBrush ) ;
				else
					mdc.SelectObject ( &this->GreyBrush ) ;
				mdc.Rectangle ( this->PaintRegion.GetRectByIndex(i) ) ;
			}
		}
		
		CRect StatusRect = this->PaintRegion.GetStautsRect() ;
		dc.BitBlt ( StatusRect.left, StatusRect.top, StatusRect.Width(), \
			StatusRect.Height(), &mdc, StatusRect.left, StatusRect.top, SRCCOPY ) ;

		dc.SelectObject ( pOldBrush ) ;
		dc.SelectObject ( pOldBmp ) ;
		bmp.DeleteObject () ;
		mdc.DeleteDC () ;

		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù����ʾ��
//
HCURSOR CReserveAndSubmitDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CReserveAndSubmitDlg::OnBnClickedAlloc()
{
	if ( this->PaintRegion.IsValid() )
		return ;
	this->PaintRegion.SetValid ( TRUE ) ;
	this->Invalidate ( FALSE ) ;
	this->szBaseAddr.Format ( L"0x%08X", this->PaintRegion.GetBaseAddr () ) ;
	this->UpdateData ( FALSE ) ;
}

void CReserveAndSubmitDlg::OnBnClickedRelease()
{
	if ( this->PaintRegion.IsValid() == FALSE )
		return ;
	this->PaintRegion.SetValid ( FALSE ) ;
	this->Invalidate ( FALSE ) ;
	this->szBaseAddr = L"" ;
	this->UpdateData ( FALSE ) ;
}

void CReserveAndSubmitDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if ( this->PaintRegion.IsValid () )
	{
		this->PaintRegion.ChangeStatusByPt ( point ) ;
		this->Invalidate ( FALSE ) ;
	}
	CDialog::OnLButtonDown(nFlags, point);
}

void CReserveAndSubmitDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if ( this->PaintRegion.IsValid () )
	{
		DWORD dwPageAddr = this->PaintRegion.GetAddrByStatus (point) ;
		if ( dwPageAddr == 0 )
			this->szCurAddr = L"" ;
		else
			this->szCurAddr.Format ( L"0x%08X", dwPageAddr ) ;
		this->UpdateData ( FALSE ) ;
	}

	CDialog::OnMouseMove(nFlags, point);
}
