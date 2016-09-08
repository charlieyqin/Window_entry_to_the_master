// IPC_Mailslot_ClientDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "IPC_Mailslot_Client.h"
#include "IPC_Mailslot_ClientDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define MAILSLOT_NAME	L"\\\\.\\mailslot\\test_mailslot"

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


// CIPC_Mailslot_ClientDlg �Ի���




CIPC_Mailslot_ClientDlg::CIPC_Mailslot_ClientDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CIPC_Mailslot_ClientDlg::IDD, pParent)
	, szData(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CIPC_Mailslot_ClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_DATA, szData);
}

BEGIN_MESSAGE_MAP(CIPC_Mailslot_ClientDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_SEND, &CIPC_Mailslot_ClientDlg::OnBnClickedSend)
END_MESSAGE_MAP()


// CIPC_Mailslot_ClientDlg ��Ϣ�������

BOOL CIPC_Mailslot_ClientDlg::OnInitDialog()
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

void CIPC_Mailslot_ClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CIPC_Mailslot_ClientDlg::OnPaint()
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
HCURSOR CIPC_Mailslot_ClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CIPC_Mailslot_ClientDlg::OnBnClickedSend()
{
	// ���¿ؼ����ݵ�����
	this->UpdateData();
	// �����Ϣ�Ƿ�Ϊ��
	if( this->szData.IsEmpty())
		return ;

	// ���ʲ�
	HANDLE hMailslot = CreateFile ( MAILSLOT_NAME, \
		GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL ) ;
	if ( hMailslot == INVALID_HANDLE_VALUE )
	{
		this->MessageBox ( L"�޷���ָ���ʲ�" ) ;
		return ;
	}

	// д������
	DWORD dwWriteBytes = 0, len = this->szData.GetLength() * 2 + 2 ;
	LPBYTE	lpMsg = (LPBYTE)this->szData.GetBuffer ( len ) ;
	WriteFile ( hMailslot, lpMsg, len, &dwWriteBytes, NULL ) ;
	CloseHandle ( hMailslot ) ;
}
