// SockMonDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SockMon.h"
#include "SockMonDlg.h"

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


// CSockMonDlg �Ի���




CSockMonDlg::CSockMonDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSockMonDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSockMonDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SOCK_TREE, SockTree);
}

BEGIN_MESSAGE_MAP(CSockMonDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_INSTALL, &CSockMonDlg::OnBnClickedInstall)
	ON_BN_CLICKED(IDC_UNINSTALL, &CSockMonDlg::OnBnClickedUninstall)
	ON_WM_DESTROY()
	ON_MESSAGE(NOTIFY_MESSAGE,OnNotifyMessage)
	ON_BN_CLICKED(IDC_EMPTY, &CSockMonDlg::OnBnClickedEmpty)
	ON_BN_CLICKED(IDC_FLUSH, &CSockMonDlg::OnBnClickedFlush)
END_MESSAGE_MAP()


// CSockMonDlg ��Ϣ�������

BOOL CSockMonDlg::OnInitDialog()
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

	this->SockData.SetTreeCtrl ( &this->SockTree ) ;

	this->OnBnClickedUninstall () ;
	this->OnBnClickedInstall () ;

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CSockMonDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CSockMonDlg::OnPaint()
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
HCURSOR CSockMonDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CSockMonDlg::OnBnClickedInstall()
{
	if ( this->bStatus )
	{
		this->MessageBox ( L"�Ѿ���װ��" ) ;
		return ;
	}
	else
	{
		this->bStatus = TRUE ;
		
		WCHAR szPath [ MAX_BUF_SIZE ] = {0} ;
		GetCurrentDirectory ( MAX_BUF_SIZE, szPath ) ;
		wcscat ( szPath, L"\\LSP.dll" ) ;
		if ( this->LSP.InstallProvider ( szPath ) != 0 )
			this->MessageBox ( L"��װʧ�ܣ�" ) ;
	}
}

void CSockMonDlg::OnBnClickedUninstall()
{
	this->LSP.RemoveProvider (); 
	this->bStatus = FALSE ;
}

void CSockMonDlg::OnDestroy()
{
	this->OnBnClickedUninstall () ;
	CDialog::OnDestroy();
}

LRESULT CSockMonDlg::OnNotifyMessage ( WPARAM wParam, LPARAM lParam )
{
	this->SockData.UpdateInfo () ;
	if ( this->SockData.IsFull() )
	{
		if ( this->MessageBox ( L"�洢�ռ��������Ƿ�������ݣ�" ) == IDOK )
			this->SockData.ResetSockData () ;
	}
	return 0 ;
}

void CSockMonDlg::OnBnClickedEmpty()
{
	this->SockData.ResetSockData () ;
}

void CSockMonDlg::OnBnClickedFlush()
{
	this->SockData.FlushSockData () ;
}
