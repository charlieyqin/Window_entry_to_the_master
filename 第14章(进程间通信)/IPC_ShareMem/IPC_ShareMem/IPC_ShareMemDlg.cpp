// IPC_ShareMemDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "IPC_ShareMem.h"
#include "IPC_ShareMemDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define DEF_DATA_SIZE		4096
#define SHARE_MEM_NOTIFY	WM_USER+1


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


// CIPC_ShareMemDlg �Ի���




CIPC_ShareMemDlg::CIPC_ShareMemDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CIPC_ShareMemDlg::IDD, pParent)
	, szData(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CIPC_ShareMemDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_DATA, szData);
}

BEGIN_MESSAGE_MAP(CIPC_ShareMemDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_CREATE, &CIPC_ShareMemDlg::OnBnClickedCreate)
	ON_BN_CLICKED(IDC_CLOSE, &CIPC_ShareMemDlg::OnBnClickedClose)
	ON_BN_CLICKED(IDC_WRITE, &CIPC_ShareMemDlg::OnBnClickedWrite)
	ON_EN_CHANGE(IDC_DATA, &CIPC_ShareMemDlg::OnEnChangeData)
END_MESSAGE_MAP()


// CIPC_ShareMemDlg ��Ϣ�������

BOOL CIPC_ShareMemDlg::OnInitDialog()
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
	this->hMapFile = NULL ;
	this->lpData = NULL ;

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CIPC_ShareMemDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CIPC_ShareMemDlg::OnPaint()
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
HCURSOR CIPC_ShareMemDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CIPC_ShareMemDlg::OnBnClickedCreate()
{	
	if ( this->lpData )
	{
		this->MessageBox ( L"�����ڴ��Ѿ����ڣ�" ) ;
		return ;
	}

	// ���������ڴ�
	this->hMapFile = CreateFileMapping ( INVALID_HANDLE_VALUE, \
		NULL,PAGE_READWRITE | SEC_COMMIT,0,DEF_DATA_SIZE,L"ShareMemSample" ) ;
	
	// ӳ�乲���ڴ�
	if ( hMapFile )
		this->lpData = MapViewOfFile ( hMapFile, FILE_MAP_READ|FILE_MAP_WRITE,0,0,0 ) ;

	if ( this->hMapFile == NULL || this->lpData == NULL )
		this->MessageBox ( L"���������ڴ�ӳ���ļ�ʧ��!" ) ;
}

void CIPC_ShareMemDlg::OnBnClickedClose()
{
	// ����ӳ��Ĺ����ڴ�
	if ( this->lpData )
		UnmapViewOfFile ( this->lpData ) ;

	// �رչ����ڴ�
	if ( this->hMapFile )
		CloseHandle ( this->hMapFile ) ;
}

void CIPC_ShareMemDlg::OnBnClickedWrite()
{
	if ( this->lpData == NULL )
	{
		this->MessageBox ( L"д��ʧ�ܣ�" ) ;
		return ;
	}

	UINT	nLen = this->szData.GetLength()*2+2 ;
	LPWSTR	lpBuf = this->szData.GetBuffer( nLen ) ;

	// д�빲���ڴ�
	memcpy ( this->lpData, (char*)lpBuf, nLen ) ;

	// ����Ƿ���Ҫ֪ͨ���ͻ���
	if ( ((CButton*)this->GetDlgItem(IDC_AUTO_NOTIFY))->GetCheck() == BST_CHECKED )
	{
		HWND hWnd = ::FindWindow ( NULL, L"[��14��]���̼�ͨ��֮�����ڴ桪����ȡ��" ) ;
		if ( hWnd )
		{
			// ʹ���Զ�����Ϣ
			::PostMessage ( hWnd, SHARE_MEM_NOTIFY, 0, 0 ) ;
		}
	}
}

void CIPC_ShareMemDlg::OnEnChangeData()
{
	this->UpdateData () ;
}
