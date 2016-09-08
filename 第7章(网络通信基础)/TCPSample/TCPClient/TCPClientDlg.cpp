// TCPClientDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TCPClient.h"
#include "TCPClientDlg.h"

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


// CTCPClientDlg �Ի���




CTCPClientDlg::CTCPClientDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTCPClientDlg::IDD, pParent)
	, nDataA(0)
	, nDataB(0)
	, nDataC(0)
	, szSrvIp(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTCPClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_DATA_A, nDataA);
	DDV_MinMaxUInt(pDX, nDataA, 0, 1000000000);
	DDX_Text(pDX, IDC_DATA_B, nDataB);
	DDV_MinMaxUInt(pDX, nDataB, 0, 1000000000);
	DDX_Text(pDX, IDC_DATA_C, nDataC);
	DDX_Text(pDX, IDC_IP, szSrvIp);
	DDV_MaxChars(pDX, szSrvIp, 14);
}

BEGIN_MESSAGE_MAP(CTCPClientDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_EN_CHANGE(IDC_DATA_A, &CTCPClientDlg::OnEnChangeDataA)
	ON_EN_CHANGE(IDC_DATA_B, &CTCPClientDlg::OnEnChangeDataB)
	ON_BN_CLICKED(IDC_SEND, &CTCPClientDlg::OnBnClickedSend)
	ON_EN_CHANGE(IDC_IP, &CTCPClientDlg::OnEnChangeIp)
END_MESSAGE_MAP()


// CTCPClientDlg ��Ϣ�������

BOOL CTCPClientDlg::OnInitDialog()
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
	// ȡ��ԭʼ�����ַ
	
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2,2), &wsaData)  ;

	in_addr addr ;
	char szHostName[DEF_BUF_SIZE] = {0} ;
	gethostname ( szHostName, DEF_BUF_SIZE ) ;
	hostent* pHost = gethostbyname ( szHostName ) ;
	if ( pHost )
	{
		memcpy ( &addr, pHost->h_addr_list[0], pHost->h_length ) ;
		::SetDlgItemTextA ( this->m_hWnd, IDC_IP, inet_ntoa ( addr ) ) ;

	}

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CTCPClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CTCPClientDlg::OnPaint()
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
HCURSOR CTCPClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CTCPClientDlg::OnEnChangeDataA()
{
	this->UpdateData () ;
}

void CTCPClientDlg::OnEnChangeDataB()
{
	this->UpdateData () ;
}

void CTCPClientDlg::OnBnClickedSend()
{
	// ��ʼ��WinSock
	DWORD dwErrorCode = 0 ;
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2,2), &wsaData) != NO_ERROR)
	{
		OutputMessage ( L"��ʼ��ʧ��!", GetLastError() ) ;
		return ;
	}

	// ����ԭʼ������
	SOCKET LocalSock = socket ( AF_INET, SOCK_STREAM, IPPROTO_TCP ) ;
	if ( LocalSock == INVALID_SOCKET )
	{
		OutputMessage ( L"����socketʧ��!", GetLastError() ) ;
		return ;
	}
	
	// ���ó�ʱ��Ϣ
	int nTimeOut = 3000 ;
	::setsockopt(LocalSock,SOL_SOCKET,SO_RCVTIMEO,(char *)&nTimeOut,sizeof(int) ) ;

	// ȡ��ԭʼ�����ַ
	char szSrvIp[DEF_BUF_SIZE] = {0} ;
	::GetDlgItemTextA ( this->m_hWnd, IDC_IP, szSrvIp, DEF_BUF_SIZE ) ;
	sockaddr_in RemoteAddr;
	RemoteAddr.sin_family = AF_INET;
	RemoteAddr.sin_port = htons(12345);
	RemoteAddr.sin_addr.s_addr = inet_addr ( szSrvIp ) ;

	// ���ӷ�����
	if ( connect ( LocalSock, (SOCKADDR*)&RemoteAddr, sizeof(SOCKADDR) ) == SOCKET_ERROR )
	{
		OutputMessage ( L"����ʧ�ܣ�", GetLastError() ) ;
		return ;
	}
	
	// ������������A������B��
	char szData[DEF_BUF_SIZE] = {0} ;
	sprintf ( szData, "%d %d", this->nDataA, this->nDataB ) ;
	int nSendSize = send ( LocalSock, szData, DEF_BUF_SIZE, 0 ) ;
	if ( nSendSize <= 0 )
	{
		OutputMessage ( L"�������ݴ���", GetLastError() ) ;
		return ;
	}

	// ���շ�����������������C��
	int nRecvSize = recv ( LocalSock, (char*)&this->nDataC, sizeof(UINT), 0 ) ;
	if ( nRecvSize <= 0 )
	{
		OutputMessage ( L"�������ݴ���", GetLastError() ) ;
		return ;
	}
	
	// ���½�����Ϣ
	this->UpdateData ( FALSE ) ;
	// �ر��׽��־��
	closesocket ( LocalSock ) ;
	WSACleanup();
}

void CTCPClientDlg::OnEnChangeIp()
{
	this->UpdateData () ;
}

