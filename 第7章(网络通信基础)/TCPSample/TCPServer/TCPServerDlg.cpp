// TCPServerDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TCPServer.h"
#include "TCPServerDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include <winsock2.h>
#pragma comment ( lib, "ws2_32.lib" )

#define DEF_BUF_SIZE 1024

inline VOID OutputMessage ( LPWSTR lpMessage, DWORD dwErrorCode )
{
	WCHAR szMsg[DEF_BUF_SIZE] = {0} ;
	wsprintf ( szMsg, L"%s, ErrorCode=%d", lpMessage, dwErrorCode ) ;
	::MessageBox ( 0, szMsg, 0, 0 ) ;
}

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


// CTCPServerDlg �Ի���




CTCPServerDlg::CTCPServerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTCPServerDlg::IDD, pParent)
	, nDataA(0)
	, nDataB(0)
	, nDataC(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTCPServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_DATA_A, nDataA);
	DDX_Text(pDX, IDC_DATA_B, nDataB);
	DDX_Text(pDX, IDC_DATA_C, nDataC);
}

BEGIN_MESSAGE_MAP(CTCPServerDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


// CTCPServerDlg ��Ϣ�������

BOOL CTCPServerDlg::OnInitDialog()
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
	this->bStatus = TRUE ;
	this->hThread = CreateThread ( NULL, 0, ServerThread, this, NULL, NULL ) ;
	if ( this->hThread == NULL )
	{
		this->MessageBox ( L"���������߳�ʧ�ܣ�" ) ;
		this->bStatus = FALSE ;
	}

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CTCPServerDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CTCPServerDlg::OnPaint()
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
HCURSOR CTCPServerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

DWORD WINAPI ServerThread ( LPVOID lParam )
{
	// �������ָ��
	CTCPServerDlg* pDlg = (CTCPServerDlg*)lParam ;

	// ��ʼ��WinSock
	DWORD dwErrorCode = 0 ;
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2,2), &wsaData) != NO_ERROR)
	{
		OutputMessage ( L"��ʼ��ʧ�ܣ�", GetLastError() ) ;
		return 0 ;
	}

	// �����׽���
	SOCKET LocalSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (LocalSocket == INVALID_SOCKET )
	{
		OutputMessage ( L"����socketʧ�ܣ�", GetLastError() ) ;
		return 0;
	}

	// ȡ�ñ��ص�ַ��Ϣ
	char szHostName[DEF_BUF_SIZE] = {0} ;
	gethostname ( szHostName, DEF_BUF_SIZE ) ;
	hostent* pHost = gethostbyname ( szHostName ) ;
	if ( pHost == NULL )
		return FALSE ;

	sockaddr_in SrvAddr;
	SrvAddr.sin_family = AF_INET;
	SrvAddr.sin_port = htons(12345);
	memcpy ( &(SrvAddr.sin_addr.s_addr), pHost->h_addr_list[0], pHost->h_length ) ;

	// �󶨵�ַ��Ϣ���׽���
	if ( bind ( LocalSocket, (SOCKADDR*)&SrvAddr, sizeof(SOCKADDR) ) == SOCKET_ERROR )
	{
		OutputMessage ( L"�󶨵�ַ��Ϣʧ��!", GetLastError() ) ;
		return 0;
	}

	// ����
	if ( listen(LocalSocket,SOMAXCONN) == SOCKET_ERROR )
	{
		OutputMessage ( L"����ʧ�ܣ�", GetLastError() ) ;
		return 0;
	}

	while ( TRUE )
	{
		int len = sizeof(SOCKADDR) ;
		sockaddr_in ConnAddr ;
		// ��������
		SOCKET ConnSock = accept ( LocalSocket, (SOCKADDR*)&ConnAddr, &len ) ;
		if ( ConnSock == INVALID_SOCKET )
		{
			OutputMessage ( L"��������ʧ�ܣ�", GetLastError() ) ;
			continue ;
		}

		// ��������
		char szData[DEF_BUF_SIZE] = {0} ;
		int nRecvSize = recv ( ConnSock, szData, DEF_BUF_SIZE, 0 ) ;
		if ( nRecvSize <= 0 )
		{
			OutputMessage ( L"�������ݴ���", GetLastError() ) ;
			continue ;
		}

		// ���������ṩ�ķ��������Ǽ򵥵ļӷ�����
		sscanf ( szData, "%d %d", &pDlg->nDataA, &pDlg->nDataB ) ;
		pDlg->nDataC = pDlg->nDataA + pDlg->nDataB ;
		pDlg->SetDlgItemInt ( IDC_DATA_A, pDlg->nDataA ) ;
		pDlg->SetDlgItemInt ( IDC_DATA_B, pDlg->nDataB ) ;
		pDlg->SetDlgItemInt ( IDC_DATA_C, pDlg->nDataC ) ;

		// ��������
		int nSendSize = send ( ConnSock, (char*)&pDlg->nDataC, sizeof(UINT), 0 ) ;
		if ( nSendSize <= 0 )
		{
			OutputMessage ( L"�������ݴ���", GetLastError() ) ;
			continue ;
		}

		closesocket ( ConnSock ) ;
	}

	closesocket ( LocalSocket ) ;
	WSACleanup();

	return 0 ;
}