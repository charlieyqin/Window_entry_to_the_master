// IDEACaluDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "IDEACalu.h"
#include "IDEACaluDlg.h"

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


// CIDEACaluDlg �Ի���




CIDEACaluDlg::CIDEACaluDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CIDEACaluDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	memset ( this->bMsg, 0, DEF_BUF_SIZE ) ;
	memset ( this->bEnMsg, 0, DEF_BUF_SIZE ) ;
	memset ( this->bDeMsg, 0, DEF_BUF_SIZE ) ;
}

void CIDEACaluDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CIDEACaluDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_EN_DE, &CIDEACaluDlg::OnBnClickedEnDe)
	ON_BN_CLICKED(IDC_SET_KEY, &CIDEACaluDlg::OnBnClickedSetKey)
END_MESSAGE_MAP()


// CIDEACaluDlg ��Ϣ�������

BOOL CIDEACaluDlg::OnInitDialog()
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
	::SetDlgItemTextA ( this->m_hWnd, IDC_KEY, "TEST_IDEA_SAMPLE" ) ;
	this->OnBnClickedSetKey (); 
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CIDEACaluDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CIDEACaluDlg::OnPaint()
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
HCURSOR CIDEACaluDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CIDEACaluDlg::OnBnClickedEnDe()
{
	int nTextLen = ::GetDlgItemTextA ( this->m_hWnd, IDC_TEXT, (char*)this->bMsg, DEF_BUF_SIZE ) ;
	if ( nTextLen == 0 )
	{
		this->MessageBox ( L"�������ַ���!" ) ;
		return ;
	}

	this->nEnDataSize = DEF_BUF_SIZE ;
	memset ( (char*)this->bEnMsg, 0, DEF_BUF_SIZE ) ;
	this->idea.EncryptData ( this->bMsg, nTextLen, this->bEnMsg, &this->nEnDataSize ) ;
	::SetDlgItemTextA ( this->m_hWnd, IDC_EN_TEXT, (char*)this->bEnMsg ) ;

	UINT nBufSize = DEF_BUF_SIZE ;
	memset ( (char*)this->bDeMsg, 0, DEF_BUF_SIZE ) ;
	this->idea.DecryptData ( this->bEnMsg, this->nEnDataSize, this->bDeMsg, &nBufSize ) ;
	::SetDlgItemTextA ( this->m_hWnd, IDC_DE_TEXT, (char*)this->bDeMsg ) ;
}

void CIDEACaluDlg::OnBnClickedSetKey()
{
	BYTE bKey[DEF_BUF_SIZE] ;
	int nSize = ::GetDlgItemTextA ( this->m_hWnd, IDC_KEY, (char*)bKey, DEF_BUF_SIZE ) ;
	this->idea.SetKey ( bKey, nSize ) ;
}
