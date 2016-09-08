// IPC_ClipboardDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "IPC_Clipboard.h"
#include "IPC_ClipboardDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

typedef struct _PERSON_INFO {
	WCHAR	szName[128] ;
	UINT	uAge ;
} PERSON_INFO, *PPERSON_INFO ;


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


// CIPC_ClipboardDlg �Ի���




CIPC_ClipboardDlg::CIPC_ClipboardDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CIPC_ClipboardDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CIPC_ClipboardDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MSG_LIST, MsgList);
}

BEGIN_MESSAGE_MAP(CIPC_ClipboardDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_TEXT, &CIPC_ClipboardDlg::OnBnClickedText)
	ON_BN_CLICKED(IDC_BITMAP, &CIPC_ClipboardDlg::OnBnClickedBitmap)
	ON_BN_CLICKED(IDC_MULT_DATA, &CIPC_ClipboardDlg::OnBnClickedMultData)
	ON_BN_CLICKED(IDC_DELAY_SUBMIT, &CIPC_ClipboardDlg::OnBnClickedDelaySubmit)
	ON_BN_CLICKED(IDC_SELF_DEFINE, &CIPC_ClipboardDlg::OnBnClickedSelfDefine)
	ON_WM_RENDERALLFORMATS()
	ON_WM_RENDERFORMAT()
	ON_WM_DESTROYCLIPBOARD()
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CIPC_ClipboardDlg ��Ϣ�������

BOOL CIPC_ClipboardDlg::OnInitDialog()
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
	this->uDeskopPixelX = ::GetSystemMetrics ( SM_CXSCREEN ) ;
	this->uDeskopPixelY = ::GetSystemMetrics ( SM_CYSCREEN ) ;

	this->uNewFormat = RegisterClipboardFormat ( L"MY_TEST_FORMAT" ) ;
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CIPC_ClipboardDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CIPC_ClipboardDlg::OnPaint()
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
HCURSOR CIPC_ClipboardDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

VOID ShowErrorMsg ( DWORD dwErrorCode )
{
	WCHAR szMsg[128] = {0} ;
	wsprintf ( szMsg, L"���ü���������ʧ�ܣ�(ErrorCode=%d)", dwErrorCode ) ;
	MessageBox ( 0, szMsg, 0, 0 ) ;
}

// д���ı�����
void CIPC_ClipboardDlg::OnBnClickedText()
{	
	// �򿪼�����
	::OpenClipboard ( this->GetSafeHwnd() ) ;

	// ������ռ�����
	::EmptyClipboard();
	
	// ���ü������ı�����
	this->WriteIntoText () ;

	// �رռ�����
	::CloseClipboard();
}

// д��λͼ����
void CIPC_ClipboardDlg::OnBnClickedBitmap()
{
	// �򿪼�����
	::OpenClipboard ( this->GetSafeHwnd() ) ;

	// ������ռ�����
	::EmptyClipboard();

	// ���ü�����λͼ����
	this->WriteIntoBitmap ( ) ;

	// �رռ�����
	::CloseClipboard();
}

void CIPC_ClipboardDlg::OnBnClickedSelfDefine()
{
	// �򿪼�����
	::OpenClipboard ( this->GetSafeHwnd() ) ;

	// ������ռ�����
	::EmptyClipboard();

	// д���Զ�������
	this->WriteIntoSelfDefineData () ;

	// �رռ�����
	::CloseClipboard();
}

// �ӳ��ύ
void CIPC_ClipboardDlg::OnBnClickedDelaySubmit()
{
	// �򿪼�����
	::OpenClipboard ( this->GetSafeHwnd() ) ;

	// ������ռ�����
	::EmptyClipboard();

	// ����Ϊ�ӳ��ύ
	::SetClipboardData ( CF_BITMAP, NULL ) ;

	// �رռ�����
	::CloseClipboard();
}

// �ύ��������
void CIPC_ClipboardDlg::OnBnClickedMultData()
{
	// �򿪼�����
	::OpenClipboard ( this->GetSafeHwnd() ) ;

	// ������ռ�����
	::EmptyClipboard();

	// д��3������
	this->WriteIntoText () ;
	this->WriteIntoBitmap () ;
	this->WriteIntoSelfDefineData () ;

	// �رռ�����
	::CloseClipboard();
}

void CIPC_ClipboardDlg::OnRenderAllFormats()
{
	CDialog::OnRenderAllFormats();

	this->MsgList.AddString ( L"WM_RENDERALLFORMAT" ) ;
	this->MsgList.SetCurSel ( this->MsgList.GetCount()-1 ) ;
}

void CIPC_ClipboardDlg::OnRenderFormat(UINT nFormat)
{
	this->MsgList.AddString ( L"WM_RENDERFORMAT" ) ;
	this->MsgList.SetCurSel ( this->MsgList.GetCount()-1 ) ;

	this->WriteIntoBitmap () ;

	CDialog::OnRenderFormat(nFormat);
}

void CIPC_ClipboardDlg::OnDestroyClipboard()
{
	CDialog::OnDestroyClipboard();

	this->MsgList.AddString ( L"WM_DESTORYCLIPBOARD" ) ;
	this->MsgList.SetCurSel ( this->MsgList.GetCount()-1 ) ;
}

void CIPC_ClipboardDlg::OnDestroy()
{
	CDialog::OnDestroy();

	// TODO: �ڴ˴������Ϣ����������
}

// д���ı�����
VOID CIPC_ClipboardDlg::WriteIntoText ()
{
	// ��ʼ���ı���Ϣ
	const char szText[] = "�ı�������ʹ��ʾ����" ;
	DWORD dwTextLen = strlen ( szText ) ;
	HANDLE hMem = GlobalAlloc ( GHND, dwTextLen + 1 ) ;
	if ( hMem )
	{
		LPBYTE lpData = (LPBYTE)GlobalLock ( hMem ) ;
		memcpy ( lpData, szText, dwTextLen ) ;
		lpData[dwTextLen] = 0 ;
		GlobalUnlock ( hMem ) ;

		// ���ü������ı�����
		if ( ::SetClipboardData ( CF_TEXT, hMem ) == NULL )
			ShowErrorMsg ( GetLastError () ) ;
	}
	else
		this->MessageBox ( L"[ERROR]GlobalAlloc!" ) ;
}

// д��λͼ����
VOID CIPC_ClipboardDlg::WriteIntoBitmap ()
{	
	// ȡ�õ�ǰ��Ļλͼ
	CDC			dc, ScreenDc ;
	CBitmap		ScreenBmp ;
	dc.CreateDC ( L"DISPLAY", NULL, NULL, NULL ) ;
	ScreenDc.CreateCompatibleDC ( &dc ) ;
	ScreenBmp.CreateCompatibleBitmap ( &dc, uDeskopPixelX, uDeskopPixelY ) ;
	ScreenDc.SelectObject ( &ScreenBmp ) ;
	ScreenDc.BitBlt ( 0, 0, uDeskopPixelX, uDeskopPixelY, &dc, 0, 0, SRCCOPY ) ;

	// ���ü������ı�����
	if ( ::SetClipboardData ( CF_BITMAP, ScreenBmp.GetSafeHandle() ) == NULL )
		ShowErrorMsg ( GetLastError () ) ;

	ScreenBmp.DeleteObject () ;
	ScreenDc.DeleteDC () ;
}

// д���Զ�������
VOID CIPC_ClipboardDlg::WriteIntoSelfDefineData ()
{	
	PERSON_INFO PersonInfo = { L"zhang", 23 } ;

	// ��ʼ���Զ����ʽ
	DWORD dwLen = sizeof(PERSON_INFO) ;
	HANDLE hMem = GlobalAlloc ( GHND, dwLen + 1 ) ;
	if ( hMem )
	{
		LPBYTE lpData = (LPBYTE)GlobalLock ( hMem ) ;
		memcpy ( lpData, &PersonInfo, dwLen ) ;
		lpData[dwLen] = 0 ;
		GlobalUnlock ( hMem ) ;

		::SetClipboardData ( this->uNewFormat, hMem ) ;
	}
}