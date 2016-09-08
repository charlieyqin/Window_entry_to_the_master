// IPC_Clipboard_ReadDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "IPC_Clipboard_Read.h"
#include "IPC_Clipboard_ReadDlg.h"

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


// CIPC_Clipboard_ReadDlg �Ի���




CIPC_Clipboard_ReadDlg::CIPC_Clipboard_ReadDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CIPC_Clipboard_ReadDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CIPC_Clipboard_ReadDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_INFO, InfoList);
}

BEGIN_MESSAGE_MAP(CIPC_Clipboard_ReadDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_GET_TEXT, &CIPC_Clipboard_ReadDlg::OnBnClickedGetText)
	ON_BN_CLICKED(IDC_GET_BITMAP, &CIPC_Clipboard_ReadDlg::OnBnClickedGetBitmap)
	ON_BN_CLICKED(IDC_GET_SELF_DEFINE, &CIPC_Clipboard_ReadDlg::OnBnClickedGetSelfDefine)
	ON_BN_CLICKED(IDC_GET_ALL, &CIPC_Clipboard_ReadDlg::OnBnClickedGetAll)
END_MESSAGE_MAP()


// CIPC_Clipboard_ReadDlg ��Ϣ�������

BOOL CIPC_Clipboard_ReadDlg::OnInitDialog()
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

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CIPC_Clipboard_ReadDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CIPC_Clipboard_ReadDlg::OnPaint()
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
HCURSOR CIPC_Clipboard_ReadDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CIPC_Clipboard_ReadDlg::OnBnClickedGetText()
{
	CString TempStr ;
	this->InfoList.ResetContent () ;
	::OpenClipboard ( this->GetSafeHwnd() ) ;
	this->ReadOutText () ;
	::CloseClipboard () ;
}

void CIPC_Clipboard_ReadDlg::OnBnClickedGetBitmap()
{
	CString TempStr ;
	this->InfoList.ResetContent () ;
	::OpenClipboard ( this->GetSafeHwnd() ) ;
	this->ReadOutBitmap () ;
	::CloseClipboard () ;
}

void CIPC_Clipboard_ReadDlg::OnBnClickedGetSelfDefine()
{
	CString TempStr = L"[�Զ���]" ;
	this->InfoList.ResetContent () ;
	::OpenClipboard ( this->GetSafeHwnd() ) ;
	this->ReadOutSelfDefineData () ;
	::CloseClipboard () ;
}

void CIPC_Clipboard_ReadDlg::OnBnClickedGetAll()
{
	this->InfoList.ResetContent () ;

	// �򿪼�����
	::OpenClipboard ( this->GetSafeHwnd() ) ;

	// ѭ��ö��
	UINT format = 0;	// �ӵ�һ�ָ�ʽֵ��ʼö��
	UINT uNewFormat = RegisterClipboardFormat ( L"MY_TEST_FORMAT" ) ;
	while ( format = EnumClipboardFormats ( format ) )
	{
		// ����ֻ������3�ָ�ʽ
		if ( format == CF_TEXT )
			this->ReadOutText () ;
		else if ( format == CF_BITMAP )
			this->ReadOutBitmap () ;
		else if ( format == uNewFormat )
			this->ReadOutSelfDefineData () ;
	}
	::CloseClipboard (); 
}


VOID CIPC_Clipboard_ReadDlg::ReadOutText ()
{
	CString TempStr ;
	HANDLE hMem = ::GetClipboardData ( CF_TEXT ) ;
	if ( hMem )
	{
		TempStr = L"[�ı�]" ;
		TempStr +=(LPSTR)GlobalLock ( hMem ) ;
		GlobalUnlock ( hMem ) ;
		this->InfoList.AddString ( TempStr ) ;
	}
}

VOID CIPC_Clipboard_ReadDlg::ReadOutBitmap ()
{
	CString TempStr ;
	HBITMAP hBitmap = (HBITMAP)::GetClipboardData ( CF_BITMAP ) ;
	if ( hBitmap )
	{
		BITMAP BmpInfo ;
		::GetObject ( hBitmap, sizeof(BITMAP), &BmpInfo ) ;
		TempStr.Format ( L"[λͼ]Size=(%d,%d)", BmpInfo.bmWidth, BmpInfo.bmHeight ) ;
		this->InfoList.AddString ( TempStr ) ;
	}
}

VOID CIPC_Clipboard_ReadDlg::ReadOutSelfDefineData ()
{
	CString TempStr ;
	UINT uNewFormat = RegisterClipboardFormat ( L"MY_TEST_FORMAT" ) ;
	HANDLE hMem = ::GetClipboardData ( uNewFormat ) ;
	if ( hMem )
	{
		PPERSON_INFO pInfo = (PPERSON_INFO)GlobalLock ( hMem ) ;
		TempStr.Format ( L"[�Զ���]Name=%s Age=%d", pInfo->szName, pInfo->uAge ) ;
		GlobalUnlock ( hMem ) ;
		this->InfoList.AddString ( TempStr ) ;
	}
}