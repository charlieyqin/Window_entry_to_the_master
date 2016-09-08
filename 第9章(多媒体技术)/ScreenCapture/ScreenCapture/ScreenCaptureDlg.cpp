// ScreenCaptureDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ScreenCapture.h"
#include "ScreenCaptureDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include "vfw.h"
#pragma comment ( lib, "vfw32.lib" )

#define HOTKEY_START	1001
#define HOTKEY_STOP		1002
#define DEF_BUF_SIZE	2048

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


// CScreenCaptureDlg �Ի���




CScreenCaptureDlg::CScreenCaptureDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CScreenCaptureDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	this->bStatus = FALSE ;
}

void CScreenCaptureDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CScreenCaptureDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


// CScreenCaptureDlg ��Ϣ�������

BOOL CScreenCaptureDlg::OnInitDialog()
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

	RegisterHotKey ( this->m_hWnd, HOTKEY_START, MOD_CONTROL, VK_F5 ) ;
	RegisterHotKey ( this->m_hWnd, HOTKEY_STOP, MOD_CONTROL, VK_F6 ) ;

	CRect DesktopWnd ;
	GetDesktopWindow()->GetWindowRect ( &DesktopWnd ) ;

	this->nWidth = DesktopWnd.Width() ;
	this->nHeight = DesktopWnd.Height() ;

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CScreenCaptureDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CScreenCaptureDlg::OnPaint()
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
HCURSOR CScreenCaptureDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

DWORD WINAPI CaptureThread ( LPVOID lParam )
{
	CScreenCaptureDlg* pDlg = (CScreenCaptureDlg*)lParam ;

	// ȡ�õ�ǰĿ¼·��
	WCHAR szFilePath[DEF_BUF_SIZE] = {0} ;
	GetCurrentDirectoryW( DEF_BUF_SIZE, szFilePath ) ;

	// ȡ��ʱ��
	SYSTEMTIME	LocalTime ;
	GetLocalTime ( &LocalTime ) ;

	// ���ݴ���ʱ������Ŀ��AVI�ļ���
	int nPathLen = wcslen ( szFilePath ) ;
	wsprintf ( &szFilePath[nPathLen], L"\\[%04d-%02d-%02d] %02d-%02d-%02d .avi", LocalTime.wYear, \
		LocalTime.wMonth, LocalTime.wDay, LocalTime.wHour, LocalTime.wMinute, LocalTime.wSecond ) ;

	// ��ʼ��
	AVIFileInit () ;

	// ����AVI�ļ�
	PAVIFILE	pAviFile ;
	AVIFileOpen ( &pAviFile, szFilePath, OF_CREATE|OF_WRITE, NULL ) ;
	if ( pAviFile == NULL )
		return 0;

	//����λͼ��Ϣͷ
	BITMAPINFOHEADER BmpInfoHeader = {0} ;
	BmpInfoHeader.biSize		= sizeof(BITMAPINFOHEADER); 
	BmpInfoHeader.biWidth		= pDlg->nWidth ;
	BmpInfoHeader.biHeight		= pDlg->nHeight ;
	BmpInfoHeader.biPlanes		= 1 ;
	BmpInfoHeader.biBitCount	= 32 ;
	BmpInfoHeader.biCompression	= BI_RGB ;
	BmpInfoHeader.biSizeImage	= pDlg->nWidth * pDlg->nHeight *4 ;

	// ����AVI����Ϣ
	AVISTREAMINFO	AviStreamInfo = {0} ;
	AviStreamInfo.fccType = streamtypeVIDEO;
	AviStreamInfo.dwScale = 1 ;
	AviStreamInfo.dwRate = 15 ;
	AviStreamInfo.dwSuggestedBufferSize = BmpInfoHeader.biSizeImage ;
	SetRect ( &AviStreamInfo.rcFrame, 0, 0, pDlg->nWidth, pDlg->nHeight ) ;

	// ����AVI��
	PAVISTREAM	pAviStream ;
	AVIFileCreateStream ( pAviFile, &pAviStream, &AviStreamInfo ) ;
	if ( pAviStream == NULL )
		return 0 ;

	//������ʱ�洢����
	LPVOID lpBmpBuf = VirtualAlloc ( NULL, BmpInfoHeader.biSizeImage, MEM_COMMIT, PAGE_READWRITE ) ;
	if ( lpBmpBuf == NULL )
		return 0;

	// ȡ����Ļλͼ��ָ��
	CDC sdc ;
	sdc.CreateDC (  L"DISPLAY", NULL, NULL, NULL ) ;
	CBitmap* pCurBmp = sdc.GetCurrentBitmap() ;

	UINT nFrameIndex = 0 ;
	while ( pDlg->bStatus )
	{
		//��λͼ���ݿ�������ʱ������
		GetDIBits ( sdc.m_hDC, (HBITMAP)pCurBmp->m_hObject, 0, pDlg->nHeight, lpBmpBuf, (LPBITMAPINFO)&BmpInfoHeader, DIB_RGB_COLORS);
		// ��������ʽ
		AVIStreamSetFormat ( pAviStream, nFrameIndex, &BmpInfoHeader, sizeof(BITMAPINFOHEADER) ) ;
		// д��������
		AVIStreamWrite ( pAviStream, nFrameIndex, 1, lpBmpBuf, BmpInfoHeader.biSizeImage, AVIIF_KEYFRAME, NULL, NULL ) ;
		// ֡����1
		nFrameIndex ++ ;
	}

	sdc.DeleteDC () ;
	VirtualFree ( lpBmpBuf, BmpInfoHeader.biSizeImage, MEM_RELEASE ) ;

	if ( pAviStream )
		AVIStreamClose ( pAviStream ) ;
	if ( pAviFile )
		AVIFileRelease ( pAviFile ) ;
	AVIFileExit () ;

	CString msg ;
	msg.Format ( L"%s", szFilePath ) ;
	MessageBox ( 0, msg, L"���浽·����", 0 ) ;

	return 0 ;
}

BOOL CScreenCaptureDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���
	if ( pMsg->message == WM_HOTKEY )
	{
		switch ( pMsg->wParam )
		{
		case HOTKEY_START:	
			if ( this->bStatus == FALSE )
			{
				this->bStatus = TRUE ;
				this->CloseWindow () ;
				if ( CreateThread ( NULL, 0, CaptureThread, this, 0, NULL ) == NULL )
				{
					this->MessageBox ( L"�޷����������̣߳�" ) ;
					this->bStatus = FALSE ;
				}
			}
			break ;
		case HOTKEY_STOP:
			{
				this->bStatus = FALSE ;
			}
			break ;
		}
	}
	return CDialog::PreTranslateMessage(pMsg);
}
