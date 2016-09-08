// ButtonDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Button.h"
#include "ButtonDlg.h"

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


// CButtonDlg �Ի���




CButtonDlg::CButtonDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CButtonDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CButtonDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ADDR1, addr1);
	DDX_Control(pDX, IDC_ADDR2, addr2);
	DDX_Control(pDX, IDC_ADDR3, addr3);
	DDX_Control(pDX, IDC_ADDR4, addr4);
	DDX_Control(pDX, IDC_GAME1, game1);
	DDX_Control(pDX, IDC_GAME2, game2);
	DDX_Control(pDX, IDC_GAME3, game3);
	DDX_Control(pDX, IDC_GAME4, game4);
	DDX_Control(pDX, IDC_GAME5, game5);
	DDX_Control(pDX, IDC_GAME6, game6);
}

BEGIN_MESSAGE_MAP(CButtonDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_SURE, &CButtonDlg::OnBnClickedSure)
END_MESSAGE_MAP()


// CButtonDlg ��Ϣ�������

BOOL CButtonDlg::OnInitDialog()
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

	this->addr1.SetCheck ( BST_CHECKED ) ;

	this->game1.SetCheck (  BST_CHECKED ) ;
	this->game2.SetCheck (  BST_CHECKED ) ;
	this->game3.SetCheck (  BST_CHECKED ) ;
	this->game4.SetCheck (  BST_CHECKED ) ;
	this->game5.SetCheck (  BST_CHECKED ) ;
	this->game6.SetCheck (  BST_CHECKED ) ;

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CButtonDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CButtonDlg::OnPaint()
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
HCURSOR CButtonDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CButtonDlg::OnBnClickedSure()
{
	CString szMsg ;

	szMsg += L"�������ڵأ�" ;
	if ( this->addr1.GetCheck () == BST_CHECKED )
		szMsg += L"����\n" ;
	else if ( this->addr2.GetCheck () == BST_CHECKED )
		szMsg += L"�Ϻ�\n" ;
	else if ( this->addr3.GetCheck () == BST_CHECKED )
		szMsg += L"����\n" ;
	else if ( this->addr4.GetCheck () == BST_CHECKED )
		szMsg += L"����\n" ;

	szMsg += L"������Ȥ���ã�" ;
	if ( this->game1.GetCheck() == BST_CHECKED )
		szMsg += L"�����˶� " ;
	if ( this->game2.GetCheck() == BST_CHECKED )
		szMsg += L"Ӱ������ " ;
	if ( this->game3.GetCheck() == BST_CHECKED )
		szMsg += L"�ڿͼ��� " ;
	if ( this->game4.GetCheck() == BST_CHECKED )
		szMsg += L"���ι۹� " ;
	if ( this->game5.GetCheck() == BST_CHECKED )
		szMsg += L"�������� " ;
	if ( this->game6.GetCheck() == BST_CHECKED )
		szMsg += L"������Ϸ " ;

	this->MessageBox ( szMsg, L"����ѡ��" ) ;
}
