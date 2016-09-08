// PipeDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Pipe.h"
#include "PipeDlg.h"

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


// CPipeDlg �Ի���




CPipeDlg::CPipeDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPipeDlg::IDD, pParent)
	, szParam(_T(""))
	, szOutput(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPipeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_PARAM, szParam);
	DDV_MaxChars(pDX, szParam, 256);
	DDX_Text(pDX, IDC_OUTPUT_INFO, szOutput);
}

BEGIN_MESSAGE_MAP(CPipeDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_EN_CHANGE(IDC_PARAM, &CPipeDlg::OnEnChangeParam)
	ON_BN_CLICKED(IDC_EXECUTE, &CPipeDlg::OnBnClickedExecute)
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CPipeDlg ��Ϣ�������

BOOL CPipeDlg::OnInitDialog()
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

void CPipeDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CPipeDlg::OnPaint()
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
HCURSOR CPipeDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CPipeDlg::OnEnChangeParam()
{
	this->UpdateData () ;
}

// �����߳�
DWORD WINAPI NewThread ( LPVOID lParam )
{
	CPipeDlg* pDlg = (CPipeDlg*)lParam ;
	WCHAR szSysDir[1024] ;
	CString szCommand ;
	// ȡ��ϵͳĿ¼
	GetSystemDirectory ( szSysDir, sizeof(szSysDir) ) ;
	// ��ʽ�������в���
	szCommand.Format ( L"%s\\ping.exe ", szSysDir ) ;
	szCommand += pDlg->szParam ;

	HANDLE	hRead, hWrite ;
	SECURITY_ATTRIBUTES saAttr;			// ���尲ȫ������
	saAttr.nLength = sizeof(SECURITY_ATTRIBUTES); 
	saAttr.bInheritHandle = TRUE; 
	saAttr.lpSecurityDescriptor = NULL; 
	// �����ܵ��������ض���ping����������Ϣ
	if ( !CreatePipe(&hRead, &hWrite, &saAttr, 0) ) 
	{
		OutputDebugStringA ( "[ERROR]CreatePipe failed!" ) ;
		return 0 ;
	}
	
	// ���ô����ӽ��̵Ĳ���
	PROCESS_INFORMATION pi ;
	STARTUPINFO si = { sizeof(STARTUPINFO) } ;
	si.dwFlags = STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW ;
	si.hStdOutput = hWrite ;
	si.hStdError = hWrite ;
	si.wShowWindow = SW_HIDE ;
	// �����ӽ���
	LPWSTR lpCommand = szCommand.GetBuffer(szCommand.GetLength()) ;
	if ( CreateProcess ( NULL, lpCommand, NULL, NULL, TRUE, 0, NULL, szSysDir, &si, &pi ) )
	{
		// �ܵ���д����Ѿ����ݸ��ӽ��̣����Թر��ڱ����̵ľ��
		CloseHandle ( hWrite ) ;

		// �ӹܵ���ȡ����
		// ��ʱ�ӽ���ʹ��д�����ܵ�д�����ݣ�������ʹ�ö�ȡ�˴ӹܵ���ȡ����
		DWORD dwTotalBytes = 0, dwReadBytes ;
		char  pBuf[1024] ={0} ;
		pDlg->szOutput += "=======================================================\n" ;
		while ( TRUE )
		{
			memset ( pBuf, 0, sizeof(pBuf) ) ;
			if ( !ReadFile ( hRead, pBuf, sizeof(pBuf)-1, &dwReadBytes, NULL ) )
				break ;
			if ( dwReadBytes > 0 ) 
			{
				pDlg->szOutput += pBuf ;
				pDlg->UpdateData ( FALSE ) ;
			}
		}
	}

	CloseHandle ( hRead ) ;
	return 0;
}

void CPipeDlg::OnBnClickedExecute()
{
	CreateThread ( NULL, 0, NewThread, this, 0, NULL ) ;
}

void CPipeDlg::OnDestroy()
{
	CDialog::OnDestroy();
}
