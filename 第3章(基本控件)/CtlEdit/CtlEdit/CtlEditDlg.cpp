// CtlEditDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CtlEdit.h"
#include "CtlEditDlg.h"

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


// CCtlEditDlg �Ի���




CCtlEditDlg::CCtlEditDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCtlEditDlg::IDD, pParent)
	, szMsg1(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCtlEditDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, szMsg1);
	DDX_Text(pDX, IDC_EDIT2, szMsg2);
	DDX_Text(pDX, IDC_EDIT3, szMsg3);
	DDX_Text(pDX, IDC_EDIT4, szMsg4);
	DDX_Text(pDX, IDC_EDIT5, szMsg5);
	DDX_Text(pDX, IDC_EDIT6, szMsg6);
	DDX_Text(pDX, IDC_EDIT7, szMsg7);
	DDX_Text(pDX, IDC_EDIT8, szMsg8);
	DDX_Text(pDX, IDC_EDIT9, szMsg9);
	DDX_Text(pDX, IDC_EDIT10, szMsg10);
	DDX_Text(pDX, IDC_EDIT11, szMsg11);
	DDX_Text(pDX, IDC_EDIT12, szMsg12);
}

BEGIN_MESSAGE_MAP(CCtlEditDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


// CCtlEditDlg ��Ϣ�������

BOOL CCtlEditDlg::OnInitDialog()
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

	this->szMsg1 = L"�����" ;
	this->szMsg2 = L"���ж���" ;
	this->szMsg3 = L"�Ҷ���" ;
	this->szMsg4 = L"���������" ;
	this->szMsg5 = L"���������" ;
	this->szMsg6 = L"UpperCase" ;
	this->szMsg7 = L"LowerCase" ;
	this->szMsg8 = L"123456" ;
	this->szMsg9 = L"�����ַ�[*����~32]" ;
	this->szMsg10 = L"������ʾ" ;
	this->szMsg11 = L"Password" ;
	this->szMsg12 = L"ֻ��" ;
	this->UpdateData ( FALSE ) ;

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CCtlEditDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CCtlEditDlg::OnPaint()
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
HCURSOR CCtlEditDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

