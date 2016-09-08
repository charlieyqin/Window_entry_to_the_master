// BlowfishCaluDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "BlowfishCalu.h"
#include "BlowfishCaluDlg.h"

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


// CBlowfishCaluDlg �Ի���




CBlowfishCaluDlg::CBlowfishCaluDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBlowfishCaluDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	memset ( this->szKey, 0, MAX_KEY_SIZE ) ;
	memset ( this->szMsg, 0, DEF_BUF_SIZE ) ;
	memset ( this->ECB_szEnMsg, 0, DEF_BUF_SIZE ) ;
	memset ( this->ECB_szDeMsg, 0, DEF_BUF_SIZE ) ;
	memset ( this->CBC_szEnMsg, 0, DEF_BUF_SIZE ) ;
	memset ( this->CBC_szEnMsg, 0, DEF_BUF_SIZE ) ;
}

void CBlowfishCaluDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CBlowfishCaluDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_EN_CHANGE(IDC_KEY, &CBlowfishCaluDlg::OnEnChangeKey)
	ON_BN_CLICKED(IDC_CODING, &CBlowfishCaluDlg::OnBnClickedCoding)
END_MESSAGE_MAP()


// CBlowfishCaluDlg ��Ϣ�������

BOOL CBlowfishCaluDlg::OnInitDialog()
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
	::SetDlgItemTextA ( this->m_hWnd, IDC_KEY, "Blowfish�㷨���ܽ�����ʾ���" ) ;

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CBlowfishCaluDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CBlowfishCaluDlg::OnPaint()
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
HCURSOR CBlowfishCaluDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CBlowfishCaluDlg::OnEnChangeKey()
{
}

void CBlowfishCaluDlg::OnBnClickedCoding()
{
	int nKeySize = ::GetDlgItemTextA ( this->m_hWnd, IDC_KEY, (char*)this->szKey, MAX_KEY_SIZE ) ;
	if ( nKeySize < MIN_KEY_SIZE )
	{
		this->MessageBox ( L"��Կ���Ȳ���С��4��" ) ;
		return ;
	}

	int nMsgSize = ::GetDlgItemTextA ( this->m_hWnd, IDC_MSG, (char*)this->szMsg, DEF_BUF_SIZE ) ;
	if ( nMsgSize == 0 )
	{
		this->MessageBox ( L"��������Ϣ�ַ�����" ) ;
		return ;
	}

	this->Blowfish.BF_SetKey ( this->szKey, nKeySize ) ;

	UINT nRealSize = DEF_BUF_SIZE ;
	this->Blowfish.BF_Encrypt ( this->szMsg, nMsgSize, this->ECB_szEnMsg, &nRealSize ) ;
	this->Blowfish.BF_Decrypt ( this->ECB_szEnMsg, nRealSize, this->ECB_szDeMsg, DEF_BUF_SIZE ) ;

	nRealSize = DEF_BUF_SIZE ;
	this->Blowfish.BF_SetMode ( 1 )  ;
	this->Blowfish.BF_Encrypt ( this->szMsg, nMsgSize, this->CBC_szEnMsg, &nRealSize ) ;
	this->Blowfish.BF_Decrypt ( this->CBC_szEnMsg, nRealSize, this->CBC_szDeMsg, DEF_BUF_SIZE ) ;

	::SetDlgItemTextA ( this->m_hWnd, IDC_ECB_EN_MSG, (char*)this->ECB_szEnMsg ) ;
	::SetDlgItemTextA ( this->m_hWnd, IDC_ECB_DE_MSG, (char*)this->ECB_szDeMsg ) ;
	::SetDlgItemTextA ( this->m_hWnd, IDC_CBC_EN_MSG, (char*)this->CBC_szEnMsg ) ;
	::SetDlgItemTextA ( this->m_hWnd, IDC_CBC_DE_MSG, (char*)this->CBC_szDeMsg ) ;
}
