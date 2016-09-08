// EightPuzzleDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "EightPuzzle.h"
#include "EightPuzzleDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define MOVE_MESSAGE_UP		1001
#define MOVE_MESSAGE_DOWN	1002
#define MOVE_MESSAGE_LEFT	1003
#define MOVE_MESSAGE_RIGHT	1004

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


// CEightPuzzleDlg �Ի���




CEightPuzzleDlg::CEightPuzzleDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CEightPuzzleDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CEightPuzzleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CEightPuzzleDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_RANDOM_BEG, &CEightPuzzleDlg::OnBnClickedRandomBeg)
	ON_BN_CLICKED(IDC_RESTART, &CEightPuzzleDlg::OnBnClickedRestart)
	ON_BN_CLICKED(IDC_BEG_SHOW, &CEightPuzzleDlg::OnBnClickedBegShow)
	ON_BN_CLICKED(IDC_END_SHOW, &CEightPuzzleDlg::OnBnClickedEndShow)
	ON_WM_KEYUP()
END_MESSAGE_MAP()

// CEightPuzzleDlg ��Ϣ�������

BOOL CEightPuzzleDlg::OnInitDialog()
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
	this->isShowing = FALSE ;
	this->pNewThread = NULL ;

	::RegisterHotKey ( this->m_hWnd, MOVE_MESSAGE_UP, 0, VK_UP ) ;
	::RegisterHotKey ( this->m_hWnd, MOVE_MESSAGE_DOWN, 0, VK_DOWN ) ;
	::RegisterHotKey ( this->m_hWnd, MOVE_MESSAGE_LEFT, 0, VK_LEFT ) ;
	::RegisterHotKey ( this->m_hWnd, MOVE_MESSAGE_RIGHT, 0, VK_RIGHT ) ;

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CEightPuzzleDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CEightPuzzleDlg::OnPaint()
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

		CClientDC dc(this) ;
		this->EightPuzzle.PaintBegStatus ( &dc ) ;
		this->EightPuzzle.PaintCurStatus ( &dc ) ;
		this->EightPuzzle.PaintEndStatus ( &dc ) ;
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù����ʾ��
//
HCURSOR CEightPuzzleDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CEightPuzzleDlg::OnBnClickedRandomBeg()
{
	if ( this->isShowing )
		return ;

	this->EightPuzzle.RandomBegStatus () ;

	CClientDC dc(this) ;
	this->EightPuzzle.PaintBegStatus ( &dc ) ;
	this->EightPuzzle.PaintCurStatus ( &dc ) ;
}

void CEightPuzzleDlg::OnBnClickedRestart()
{
	if ( this->isShowing )
		return ;

	this->EightPuzzle.Restart () ;

	CClientDC dc(this) ;
	this->EightPuzzle.PaintCurStatus ( &dc ) ;
}

UINT ShowProc ( LPVOID lpParam )
{
	CEightPuzzleDlg* pDlg = (CEightPuzzleDlg*)lpParam ;
	int nStep = pDlg->EightPuzzle.GetSlove() ;

	CString szSloveInfo ;
	szSloveInfo.Format ( TEXT("��Ҫ%d��"), nStep ) ;
	pDlg->MessageBoxW ( szSloveInfo ) ;
	//pDlg->SetDlgItemTextW ( IDC_SLOVE_INFO, szSloveInfo ) ;

	CClientDC ClientDC(pDlg) ;
	if ( nStep > 0 )
	{
		pDlg->EightPuzzle.DemoShow(&ClientDC) ;
	}

	pDlg->isShowing = FALSE ;
	return 0 ;
}

void CEightPuzzleDlg::OnBnClickedBegShow()
{
	if ( this->isShowing )
		return ;

	this->isShowing = TRUE ;
	this->pNewThread = AfxBeginThread ( ShowProc, this ) ;
}

void CEightPuzzleDlg::OnBnClickedEndShow()
{
	if ( this->isShowing == FALSE )
		return ;

	::TerminateThread ( this->pNewThread->m_hThread, 0 ) ;
	this->isShowing = FALSE ;
}

void CEightPuzzleDlg::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	this->MessageBoxW ( TEXT("")) ;
	CDialog::OnKeyUp(nChar, nRepCnt, nFlags);
}

void CEightPuzzleDlg::MoveUp()
{
	this->EightPuzzle.SingleMove ( 0 ) ;
	this->Invalidate ( FALSE ) ;
	if ( this->EightPuzzle.IsFinish() == TRUE )
		this->MessageBox ( TEXT("����Ŀ��״̬��") ) ;
}

void CEightPuzzleDlg::MoveLeft()
{
	this->EightPuzzle.SingleMove ( 1 ) ;
	this->Invalidate ( FALSE ) ;
	if ( this->EightPuzzle.IsFinish() == TRUE )
		this->MessageBox ( TEXT("����Ŀ��״̬��") ) ;
}

void CEightPuzzleDlg::MoveDown()
{
	this->EightPuzzle.SingleMove ( 2 ) ;
	this->Invalidate ( FALSE ) ;
	if ( this->EightPuzzle.IsFinish() == TRUE )
		this->MessageBox ( TEXT("����Ŀ��״̬��") ) ;
}

void CEightPuzzleDlg::MoveRight()
{
	this->EightPuzzle.SingleMove ( 3 ) ;
	this->Invalidate ( FALSE ) ;
	if ( this->EightPuzzle.IsFinish() == TRUE )
		this->MessageBox ( TEXT("����Ŀ��״̬��") ) ;
}

BOOL CEightPuzzleDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���
	if ( pMsg->message == WM_HOTKEY )
	{
		switch ( pMsg->wParam )
		{
		case MOVE_MESSAGE_UP:	this->MoveUp () ;	break ;
		case MOVE_MESSAGE_DOWN:	this->MoveDown () ;	break ;
		case MOVE_MESSAGE_LEFT:	this->MoveLeft () ;	break ;
		case MOVE_MESSAGE_RIGHT:this->MoveRight () ;break ;
		}
	}

	return CDialog::PreTranslateMessage(pMsg);
}
