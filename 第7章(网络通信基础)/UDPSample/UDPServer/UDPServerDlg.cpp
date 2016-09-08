// UDPServerDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "UDPServer.h"
#include "UDPServerDlg.h"

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


// CUDPServerDlg �Ի���




CUDPServerDlg::CUDPServerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CUDPServerDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CUDPServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CUDPServerDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


// CUDPServerDlg ��Ϣ�������

BOOL CUDPServerDlg::OnInitDialog()
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
	this->hThread = CreateThread ( NULL, 0, ServerThread, this, 0, NULL ) ;

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CUDPServerDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CUDPServerDlg::OnPaint()
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
HCURSOR CUDPServerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

DWORD WINAPI ServerThread ( LPVOID lParam )
{
	CUDPServerDlg* pDlg = (CUDPServerDlg*)lParam ;

	// ��ʼ��WinSock
	DWORD dwErrorCode = 0 ;
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2,2), &wsaData) != NO_ERROR)
	{
		OutputMessage ( L"��ʼ��ʧ��!", GetLastError() ) ;
		return 0;
	}

	// �����׽���
	SOCKET LocalSock = socket ( AF_INET, SOCK_DGRAM, IPPROTO_UDP ) ;
	if ( LocalSock == INVALID_SOCKET )
	{
		OutputMessage ( L"����socketʧ��!", GetLastError() ) ;
		return 0;
	}
	
	// ȡ�ñ��ص�ַ��Ϣ
	char szHostName[DEF_BUF_SIZE] = {0} ;
	gethostname ( szHostName, DEF_BUF_SIZE ) ;
	hostent* pHost = gethostbyname ( szHostName ) ;
	if ( pHost == NULL )
		return 0 ;

	sockaddr_in SrvAddr, ClientAddr ;
	SrvAddr.sin_family = AF_INET;
	SrvAddr.sin_port = htons(34567);
	memcpy ( &(SrvAddr.sin_addr.s_addr), pHost->h_addr_list[0], pHost->h_length ) ;

	if ( bind ( LocalSock, (sockaddr*)&SrvAddr, sizeof(sockaddr) ) == SOCKET_ERROR )
	{
		OutputMessage ( L"��ʧ��!", GetLastError() ) ;
		return 0;
	}

	// �������ݣ����512�ֽڣ�
	char szData[DEF_BUF_SIZE] = {0} ;
	while ( TRUE )
	{
		int len = sizeof(sockaddr) ;
		int nSendSize = recvfrom ( LocalSock, szData, DEF_BUF_SIZE, 0, (sockaddr*)&ClientAddr, &len ) ;
		if ( nSendSize <= 0 )
		{
			OutputMessage ( L"�������ݴ���", GetLastError() ) ;
		}
		else
			::SetDlgItemTextA ( pDlg->m_hWnd, IDC_DATA, szData ) ;
	}

	// �ر��׽��־��
	closesocket ( LocalSock ) ;
	WSACleanup();
	return 0 ;
}
