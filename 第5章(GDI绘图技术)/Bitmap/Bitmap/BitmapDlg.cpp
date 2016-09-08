// BitmapDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Bitmap.h"
#include "BitmapDlg.h"

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


// CBitmapDlg �Ի���
CBitmapDlg::CBitmapDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBitmapDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	// �����ͼ����Ŀ�ȡ��߶ȡ����
	const UINT nWidth = 80, nHeight = 60, nDist = 25 ;

	// ����ǰ4��ͼ�εĻ�������
	CPoint StartPt ( 20, 20 ) ;
	for ( int i = 1; i <= 4; i++ )
	{
		this->MyBmp[i].rect.left = StartPt.x ;
		this->MyBmp[i].rect.top = StartPt.y ;
		this->MyBmp[i].rect.right = this->MyBmp[i].rect.left + nWidth ;
		this->MyBmp[i].rect.bottom = this->MyBmp[i].rect.top + nHeight ;
		StartPt.x += nWidth + nDist ;
	}

	// ���ú�4��ͼ�εĻ�������
	for ( int i = 5; i <= 8; i++ )
	{
		this->MyBmp[i].rect.left = this->MyBmp[i-4].rect.left ;
		this->MyBmp[i].rect.top = this->MyBmp[i-4].rect.top + nHeight + nDist ;
		this->MyBmp[i].rect.right = this->MyBmp[i].rect.left + nWidth ;
		this->MyBmp[i].rect.bottom = this->MyBmp[i].rect.top + nHeight ;
	}

	// ����λͼ
	this->MyBmp[0].bmp.LoadBitmapW ( IDB_BKGROUND ) ;
	this->MyBmp[1].bmp.LoadBitmapW ( IDB_BITMAP1 ) ;
	this->MyBmp[2].bmp.LoadBitmapW ( IDB_BITMAP2 ) ;
	this->MyBmp[3].bmp.LoadBitmapW ( IDB_BITMAP3 ) ;
	this->MyBmp[4].bmp.LoadBitmapW ( IDB_BITMAP4 ) ;
	this->MyBmp[5].bmp.LoadBitmapW ( IDB_BITMAP5 ) ;
	this->MyBmp[6].bmp.LoadBitmapW ( IDB_BITMAP6 ) ;
	this->MyBmp[7].bmp.LoadBitmapW ( IDB_BITMAP7 ) ;
	this->MyBmp[8].bmp.LoadBitmapW ( IDB_BITMAP8 ) ;
}

void CBitmapDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CBitmapDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


// CBitmapDlg ��Ϣ�������

BOOL CBitmapDlg::OnInitDialog()
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

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CBitmapDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CBitmapDlg::OnPaint()
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
		// ȡ�ô��ڿͻ������С
		CRect WndRect ;
		this->GetWindowRect ( &WndRect ) ;
		this->ScreenToClient ( &WndRect ) ;

		CClientDC cdc(this) ;
		CDC		mdc, TempDc ;		// �ڴ�DC
		BITMAP	BmpInfo ;
		CBitmap ClientBmp, *pOldBmp ;
		// �������豸DC���ݵ��ڴ�DC
		mdc.CreateCompatibleDC ( &cdc ) ;
		TempDc.CreateCompatibleDC ( &cdc ) ;
		// �������豸DC���ݵ�λͼ����
		ClientBmp.CreateCompatibleBitmap ( &cdc, WndRect.right, WndRect.bottom ) ;
		mdc.SelectObject ( &ClientBmp ) ;

		// ���ΰ�λͼ�����ڴ�DC
		for ( int i = 0; i <= 8; i++ )
		{
			TempDc.SelectObject ( &this->MyBmp[i].bmp ) ;
			this->MyBmp[i].bmp.GetBitmap ( &BmpInfo ) ;

			if ( i == 0 )
				mdc.BitBlt (0, 0, WndRect.Width(), WndRect.Height(), &TempDc, 0, 0, SRCCOPY ) ;
			else
				mdc.TransparentBlt ( this->MyBmp[i].rect.left, \
					this->MyBmp[i].rect.top, BmpInfo.bmWidth, BmpInfo.bmHeight, \
					&TempDc, 0, 0, BmpInfo.bmWidth, BmpInfo.bmHeight, RGB(255,255,255) ) ;
		}

		// ���ڴ�DC�����豸DC��
		cdc.BitBlt ( 0, 0, WndRect.right, WndRect.bottom, &mdc, 0, 0, SRCCOPY ) ;

		// ��������
		ClientBmp.DeleteObject () ;
		mdc.DeleteDC () ;
		
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù����ʾ��
//
HCURSOR CBitmapDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


BOOL CBitmapDlg::OnEraseBkgnd(CDC* pDC)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	return TRUE ;

	return CDialog::OnEraseBkgnd(pDC);
}
