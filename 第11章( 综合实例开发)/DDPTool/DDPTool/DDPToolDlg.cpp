// DDPToolDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DDPTool.h"
#include "DDPToolDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define HOTKEY_FIND_ONCE	1001
#define HOTKEY_BEGIN_FIND	1002
#define HOTKEY_STOP_FIND	1003


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


// CDDPToolDlg �Ի���




CDDPToolDlg::CDDPToolDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDDPToolDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDDPToolDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CDDPToolDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


// CDDPToolDlg ��Ϣ�������

BOOL CDDPToolDlg::OnInitDialog()
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

	this->bStatus = FALSE ;
	::RegisterHotKey ( this->m_hWnd, HOTKEY_FIND_ONCE, 0, VK_F5 ) ;
	::RegisterHotKey ( this->m_hWnd, HOTKEY_BEGIN_FIND, 0, VK_F6 ) ;
	::RegisterHotKey ( this->m_hWnd, HOTKEY_STOP_FIND, 0, VK_F7 ) ;

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CDDPToolDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CDDPToolDlg::OnPaint()
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
HCURSOR CDDPToolDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


UINT NewThread ( LPVOID lpParam )
{
	CDDPToolDlg* pDlg = (CDDPToolDlg*)lpParam ;

	while ( pDlg->bStatus )
	{
		pDlg->ddp.DDP_Find() ;
		Sleep ( 100 ) ;
	}
	return 0 ;
}


BOOL CDDPToolDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���
	if ( pMsg->message == WM_HOTKEY )
	{
		switch ( pMsg->wParam )
		{
		case HOTKEY_FIND_ONCE:
			if ( this->bStatus == FALSE )
				this->ddp.DDP_Find() ;	
			break ;
		case HOTKEY_BEGIN_FIND:	
			this->bStatus = TRUE ;
			AfxBeginThread ( NewThread, this, THREAD_PRIORITY_HIGHEST ) ;
			break ;
		case HOTKEY_STOP_FIND:
			this->bStatus = FALSE ;
			break ;
		}
	}

	return CDialog::PreTranslateMessage(pMsg);
}
