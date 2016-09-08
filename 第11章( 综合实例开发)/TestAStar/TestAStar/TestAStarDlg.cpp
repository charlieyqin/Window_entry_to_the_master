// TestAStarDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TestAStar.h"
#include "TestAStarDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include "AStar.h"


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


// CTestAStarDlg �Ի���




CTestAStarDlg::CTestAStarDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTestAStarDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTestAStarDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_OUTPUT, OutputList);
}

BEGIN_MESSAGE_MAP(CTestAStarDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_GEN_MAP, &CTestAStarDlg::OnBnClickedGenMap)
	ON_BN_CLICKED(IDC_SEARCH_PATH, &CTestAStarDlg::OnBnClickedSearchPath)
	ON_EN_CHANGE(IDC_SIZE, &CTestAStarDlg::OnEnChangeSize)
	ON_EN_CHANGE(IDC_RATE, &CTestAStarDlg::OnEnChangeRate)
	ON_BN_CLICKED(IDC_BUTTON1, &CTestAStarDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CTestAStarDlg ��Ϣ�������

BOOL CTestAStarDlg::OnInitDialog()
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
	this->SetDlgItemInt ( IDC_SIZE, 50, 0 ) ;
	this->SetDlgItemInt ( IDC_RATE, 60, 0 ) ;
	AStar_SetMapParam ( 50, 60 ) ;

	this->OutputList.ResetContent() ;

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CTestAStarDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CTestAStarDlg::OnPaint()
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
HCURSOR CTestAStarDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CTestAStarDlg::OnBnClickedGenMap()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int size = this->GetDlgItemInt ( IDC_SIZE ) ;
	if ( size < 10 || size > 1000 )
	{
		this->OutputList.AddString ( L"�������� 10 <= size <= 1000" ) ;
		return ;
	}

	int rate = this->GetDlgItemInt ( IDC_RATE ) ;
	if ( rate < 0 || rate > 100 )
	{
		this->OutputList.AddString ( L"�������� 0 <= rate <= 100" ) ;
		return ;
	}

	AStar_SetMapParam ( size, rate ) ;
	if ( AStar_GenerateMap () )
		this->OutputList.AddString ( L"�½���ͼ�ɹ�!" ) ;
}

void CTestAStarDlg::OnBnClickedSearchPath()
{
	this->OutputList.AddString ( L"���ڼ��ص�ͼ�ļ�����" ) ;
	int num = AStar_InitialMap () ;
	if ( num == 0 )
	{
		this->OutputList.AddString ( L"��ʼ��ʧ�ܣ�(ȷ�ϵ�ͼmap.in����)" ) ;
		return ;
	}
	
	CString TempStr ;
	TempStr.Format ( L"��ͼ���سɹ�! ( Size = %d )", num ) ;
	this->OutputList.AddString ( TempStr ) ;

	this->OutputList.AddString ( L"����Ѱ��·������" ) ;
	int a = clock () ;
	bool ret = AStar_GetShortestPath () ;
	int b = clock () ;

	if ( ret == true )
	{
		TempStr.Format ( L"Ѱ·�ɹ���time=%dms", b-a ) ;
		this->OutputList.AddString ( TempStr ) ;
		this->OutputList.AddString ( L"����������ļ�����" ) ;
		AStar_Output () ;
		this->OutputList.AddString ( L"����ɹ�!" ) ;
	}
	else
		this->OutputList.AddString ( L"�õ�ͼû��·��!" ) ;
}

void CTestAStarDlg::OnEnChangeSize()
{
	this->UpdateData () ;
}

void CTestAStarDlg::OnEnChangeRate()
{
	this->UpdateData () ;
}

void CTestAStarDlg::OnBnClickedButton1()
{
	this->OutputList.ResetContent () ;
}
