// SnifferDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Sniffer.h"
#include "SnifferDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include <winsock2.h>
#pragma comment ( lib, "ws2_32.lib" ) 

#define   SIO_RCVALL   _WSAIOW(IOC_VENDOR,1) 

#define DEF_BUF_SIZE 2048

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


// CSnifferDlg �Ի���




CSnifferDlg::CSnifferDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSnifferDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	this->isMonitor = FALSE ;
}

void CSnifferDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PACK_LIST, m_PackList);
}

BEGIN_MESSAGE_MAP(CSnifferDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_START, &CSnifferDlg::OnBnClickedStart)
	ON_BN_CLICKED(IDC_STOP, &CSnifferDlg::OnBnClickedStop)
	ON_BN_CLICKED(IDC_EMPTY, &CSnifferDlg::OnBnClickedEmpty)
END_MESSAGE_MAP()


// CSnifferDlg ��Ϣ�������

BOOL CSnifferDlg::OnInitDialog()
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
	this->m_PackList.InsertColumn ( 0, L"ID",		LVCFMT_CENTER, 30 ) ;
	this->m_PackList.InsertColumn ( 1, L"����",		LVCFMT_CENTER, 60 ) ;
	this->m_PackList.InsertColumn ( 2, L"����",		LVCFMT_CENTER, 40 ) ;
	this->m_PackList.InsertColumn ( 3, L"ԴIP",		LVCFMT_CENTER, 120 ) ;
	this->m_PackList.InsertColumn ( 4, L"Դ�˿�",	LVCFMT_CENTER, 60 ) ;
	this->m_PackList.InsertColumn ( 5, L"Ŀ��IP",	LVCFMT_CENTER, 120 ) ;
	this->m_PackList.InsertColumn ( 6, L"Ŀ�Ķ˿�", LVCFMT_CENTER, 60 ) ;
	this->m_PackList.SetExtendedStyle ( this->m_PackList.GetExtendedStyle()|LVS_EX_FULLROWSELECT ) ;

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CSnifferDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CSnifferDlg::OnPaint()
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
HCURSOR CSnifferDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CSnifferDlg::OnBnClickedStart()
{
	if ( this->isMonitor )
	{
		this->MessageBox ( L"�Ѿ��ڹ�����" ) ;
		return ;
	}

	HANDLE hThread = CreateThread ( NULL, 0, MonitorThread, this, 0, NULL ) ;
	if ( hThread == NULL )
	{
		this->MessageBox ( L"����������ʧ��!" ) ;
	}
	else
		this->isMonitor = TRUE ;
}

void CSnifferDlg::OnBnClickedStop()
{
	this->isMonitor = FALSE ;
}

void CSnifferDlg::OnBnClickedEmpty()
{
	this->m_PackList.DeleteAllItems () ;
}

// ������ݰ���Ϣ
void CSnifferDlg::AddPackInfo ( LPPACK_INFO lpPackInfo )
{
	UINT nCount = this->m_PackList.GetItemCount () ;

	CString TempStr ;
	TempStr.Format ( L"%d", nCount+1 ) ;
	this->m_PackList.InsertItem ( nCount, TempStr ) ;

	TempStr.Format ( L"%d", lpPackInfo->nLength ) ;
	this->m_PackList.SetItemText ( nCount, 1, TempStr ) ;

	if ( lpPackInfo->nProtocol == IPPROTO_TCP )
		this->m_PackList.SetItemText ( nCount, 2, L"TCP" ) ;
	else if ( lpPackInfo->nProtocol == IPPROTO_UDP )
		this->m_PackList.SetItemText ( nCount, 2, L"UDP" ) ;

	in_addr addr ;
	WCHAR	szTempBufW[DEF_BUF_SIZE] = {0} ;

	addr.S_un.S_addr = lpPackInfo->nSourIp ;
	MultiByteToWideChar (CP_ACP, 0, inet_ntoa(addr), -1, szTempBufW, sizeof(szTempBufW) );
	this->m_PackList.SetItemText ( nCount, 3, szTempBufW ) ;

	TempStr.Format ( L"%d", htons(lpPackInfo->nSourPort) ) ;
	this->m_PackList.SetItemText ( nCount, 4, TempStr ) ;

	addr.S_un.S_addr = lpPackInfo->nDestIp ;
	MultiByteToWideChar (CP_ACP, 0, inet_ntoa(addr), -1, szTempBufW, sizeof(szTempBufW) );
	this->m_PackList.SetItemText ( nCount, 5, szTempBufW ) ;

	TempStr.Format ( L"%d", htons(lpPackInfo->nDestPort) ) ;
	this->m_PackList.SetItemText ( nCount, 6, TempStr ) ;

	this->m_PackList.EnsureVisible( nCount, FALSE ) ;
	this->m_PackList.SetItemState ( nCount, LVIS_SELECTED,LVIS_SELECTED) ;
	if ( nCount > 0 )
		this->m_PackList.SetItemState ( nCount-1, 0, LVIS_SELECTED) ;
	this->m_PackList.SetFocus ( ) ;
}

// �����߳�
DWORD WINAPI MonitorThread ( LPVOID lParam )
{
	PACK_INFO	PackInfo = {0} ;
	int nRecvSize = 0 ;
	char szPackBuf[DEF_BUF_SIZE] = {0} ;

	// ȡ�ô���ָ��
	CSnifferDlg* pDlg = (CSnifferDlg*)lParam ;

	WSADATA wsaData;
	int iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
	if (iResult != NO_ERROR)
		return 0 ;

	// ��ȡ���ص�ַ��Ϣ
	sockaddr_in LocalAddr ;
	char szLocalName[DEF_BUF_SIZE] = {0} ;
	gethostname ( szLocalName, DEF_BUF_SIZE ) ;
	hostent* pHost = gethostbyname ( szLocalName ) ;
	if ( pHost != NULL )
	{
		LocalAddr.sin_family = AF_INET ;
		LocalAddr.sin_port = htons(0) ;
		memcpy ( &(LocalAddr.sin_addr.s_addr), pHost->h_addr_list[0], pHost->h_length ) ;
	}
	else
		return 0 ;

	// ���������׽���
	SOCKET MonSock = socket ( AF_INET, SOCK_RAW, IPPROTO_IP ) ;
	if ( MonSock == INVALID_SOCKET )
		return 0 ;

	// �󶨵�ַ��Ϣ���׽���
	if ( bind ( MonSock, (sockaddr*)&LocalAddr, sizeof(sockaddr) ) == SOCKET_ERROR )
		return 0 ;

	// ����Ϊ����ģʽ��������IP��
	DWORD dwValue = 1 ;
	if ( ioctlsocket ( MonSock, SIO_RCVALL, &dwValue ) != 0 )
		return 0 ;

	// �����Ʊ�־���Ƿ��������
	while ( pDlg->isMonitor )
	{
		// ȡ�����ݰ�
		nRecvSize = recv ( MonSock, szPackBuf, DEF_BUF_SIZE, 0 ) ;
		if ( nRecvSize > 0 )
		{
			// ����IP��ͷ
			PIP_HEADER pIpHeader = (PIP_HEADER)szPackBuf ;
			PackInfo.nLength	= nRecvSize ;
			PackInfo.nProtocol	= (USHORT)pIpHeader->bProtocol ;
			PackInfo.nSourIp	= pIpHeader->nSourIp ;
			PackInfo.nDestIp	= pIpHeader->nDestIp ;
			UINT nIpHeadLength = ( pIpHeader->bVerAndHLen & 0x0F ) * sizeof(UINT) ;			// IP���ݰ�ͷ����

			// ֻ���TCP��UDP��
			switch ( pIpHeader->bProtocol )
			{
			case IPPROTO_TCP:
				{
					// ȡ��TCP���ݰ��˿ں�
					PTCP_HEADER pTcpHeader = (PTCP_HEADER)&szPackBuf[nIpHeadLength] ;
					PackInfo.nSourPort = pTcpHeader->nSourPort ;
					PackInfo.nDestPort = pTcpHeader->nDestPort ;
					pDlg->AddPackInfo ( &PackInfo ) ;	// ���������
				}
				break ;
			case IPPROTO_UDP:
				{
					// ȡ��UDP���ݰ��˿ں�
					PUDP_HEADER pUdpHeader = (PUDP_HEADER)&szPackBuf[nIpHeadLength] ;
					PackInfo.nSourPort = pUdpHeader->nSourPort ;
					PackInfo.nDestPort = pUdpHeader->nDestPort ;
					pDlg->AddPackInfo ( &PackInfo ) ;	// ���������
				}
				break ;
			}
		}
		Sleep ( 100 ) ;
	}
}