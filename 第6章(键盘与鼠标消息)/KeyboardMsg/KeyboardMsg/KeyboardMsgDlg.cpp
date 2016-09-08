// KeyboardMsgDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "KeyboardMsg.h"
#include "KeyboardMsgDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define PACE_DIST	5

#define HOTKEY_UP		1001
#define HOTKEY_DOWN		1002
#define HOTKEY_LEFT		1003
#define HOTKEY_RIGHT	1004

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


// CKeyboardMsgDlg �Ի���




CKeyboardMsgDlg::CKeyboardMsgDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CKeyboardMsgDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CKeyboardMsgDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CKeyboardMsgDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_WM_KEYUP()
	ON_BN_CLICKED(IDC_LOCAL, &CKeyboardMsgDlg::OnBnClickedLocal)
	ON_BN_CLICKED(IDC_TOTAL, &CKeyboardMsgDlg::OnBnClickedTotal)
END_MESSAGE_MAP()


// CKeyboardMsgDlg ��Ϣ�������

BOOL CKeyboardMsgDlg::OnInitDialog()
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

	// ��ʼ����Ϊ��Ӧ��������Ϣ

	this->bType = TRUE ;
	((CButton*)this->GetDlgItem(IDC_LOCAL))->SetCheck ( BST_CHECKED ) ;

	this->GetWindowRect ( &this->ValidRect ) ;
	this->ScreenToClient ( &this->ValidRect ) ;
	this->ValidRect.top += 100 ;

	this->FaceBmp.LoadBitmapW ( IDB_FACE ) ;
	BITMAP BmpInfo ;
	this->FaceBmp.GetBitmap ( &BmpInfo ) ;
	this->FaceRect.left = 140 ;
	this->FaceRect.top = 100 ;
	this->FaceRect.right = this->FaceRect.left + BmpInfo.bmWidth ;
	this->FaceRect.bottom = this->FaceRect.top + BmpInfo.bmHeight ;

	::RegisterHotKey ( this->m_hWnd, HOTKEY_UP, 0, VK_UP ) ;
	::RegisterHotKey ( this->m_hWnd, HOTKEY_DOWN, 0, VK_DOWN ) ;
	::RegisterHotKey ( this->m_hWnd, HOTKEY_LEFT, 0, VK_LEFT ) ;
	::RegisterHotKey ( this->m_hWnd, HOTKEY_RIGHT, 0, VK_RIGHT ) ;

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CKeyboardMsgDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CKeyboardMsgDlg::OnPaint()
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
		CClientDC	cdc(this) ;
		CDC			mdc, TempDc ;
		CBitmap		bmp ;
		CBrush		BkBrush ;
		CRect		WndRect ;
		this->GetWindowRect ( &WndRect ) ;

		mdc.CreateCompatibleDC ( &cdc ) ;
		TempDc.CreateCompatibleDC ( &cdc ) ;
		bmp.CreateCompatibleBitmap ( &cdc, WndRect.Width(), WndRect.Height() ) ;
		mdc.SelectObject ( &bmp ) ;

		BkBrush.CreateSolidBrush ( RGB(255,255,255) ) ;
		mdc.SelectObject ( &BkBrush ) ;
		mdc.Rectangle ( &this->ValidRect ) ;

		TempDc.SelectObject ( &this->FaceBmp ) ;
		mdc.BitBlt ( this->FaceRect.left, this->FaceRect.top, this->FaceRect.Width(), \
			this->FaceRect.Height(), &TempDc, 0, 0, SRCCOPY ) ;


		cdc.BitBlt ( this->ValidRect.left, this->ValidRect.top,this->ValidRect.Width(),\
			this->ValidRect.Height(), &mdc, this->ValidRect.left, this->ValidRect.top+1, SRCCOPY ) ;

		bmp.DeleteObject () ;
		BkBrush.DeleteObject () ;
		TempDc.DeleteDC () ;
		mdc.DeleteDC () ;

		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù����ʾ��
//
HCURSOR CKeyboardMsgDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CKeyboardMsgDlg::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CDialog::OnKeyUp(nChar, nRepCnt, nFlags);
}

BOOL CKeyboardMsgDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���

	switch ( pMsg->message )
	{
	case WM_KEYDOWN:
		if ( this->bType == TRUE )
		{
			switch ( pMsg->wParam )
			{
			case 'W':	this->MoveFace ( 0 ) ;	break ;
			case 'S':	this->MoveFace ( 1 ) ;	break ;
			case 'A':	this->MoveFace ( 2 ) ;	break ;
			case 'D':	this->MoveFace ( 3 ) ;	break ;
			}
		}
		break ;
	case WM_HOTKEY:
		if ( this->bType == FALSE )
		{
			switch ( pMsg->wParam )
			{
			case HOTKEY_UP:		this->MoveFace ( 0 ) ;	break ;
			case HOTKEY_DOWN:	this->MoveFace ( 1 ) ;	break ;
			case HOTKEY_LEFT:	this->MoveFace ( 2 ) ;	break ;
			case HOTKEY_RIGHT:	this->MoveFace ( 3 ) ;	break ;
			}
		}
		break ;
	}


	return CDialog::PreTranslateMessage(pMsg);
}

VOID CKeyboardMsgDlg::MoveFace ( UINT nDir )
{
	switch ( nDir )
	{
	case 0:		// ��
		if ( this->FaceRect.top >= this->ValidRect.top + PACE_DIST )
		{
			this->FaceRect.top -= PACE_DIST ;
			this->FaceRect.bottom -= PACE_DIST ;
		}
		break ;
	case 1:		// ��
		if ( this->FaceRect.bottom <= this->ValidRect.bottom - PACE_DIST )
		{
			this->FaceRect.top += PACE_DIST ;
			this->FaceRect.bottom += PACE_DIST ;
		}
		break ;
	case 2:		// ��
		if ( this->FaceRect.left >= this->ValidRect.left + PACE_DIST )
		{
			this->FaceRect.left -= PACE_DIST ;
			this->FaceRect.right -= PACE_DIST ;
		}
		break ;
	case 3:		// ��
		if ( this->FaceRect.right <= this->ValidRect.right - PACE_DIST  )
		{
			this->FaceRect.left += PACE_DIST ;
			this->FaceRect.right += PACE_DIST ;
		}
		break ;
	}
	this->Invalidate ( FALSE ) ;
}
void CKeyboardMsgDlg::OnBnClickedLocal()
{
	this->bType = TRUE ;
}

void CKeyboardMsgDlg::OnBnClickedTotal()
{
	this->bType = FALSE ;
}
