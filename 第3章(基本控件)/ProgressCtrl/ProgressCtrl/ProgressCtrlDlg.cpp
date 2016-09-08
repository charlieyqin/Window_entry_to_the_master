// ProgressCtrlDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ProgressCtrl.h"
#include "ProgressCtrlDlg.h"

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


// CProgressCtrlDlg �Ի���




CProgressCtrlDlg::CProgressCtrlDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CProgressCtrlDlg::IDD, pParent)
	, nStart(0)
	, nEnd(0)
	, nStep(0)
	, szInfo(_T(""))
	, szInfo2(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CProgressCtrlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_BEGIN, nStart);
	DDV_MinMaxUInt(pDX, nStart, 0, 10000);
	DDX_Text(pDX, IDC_END, nEnd);
	DDV_MinMaxUInt(pDX, nEnd, 0, 100000000);
	DDX_Control(pDX, IDC_PROGRESS, ProgressCtrl);
	DDX_Text(pDX, IDC_INFO, szInfo);
	DDX_Control(pDX, IDC_PROGRESS2, ProgressCtrl2);
	DDX_Text(pDX, IDC_INFO2, szInfo2);
}

BEGIN_MESSAGE_MAP(CProgressCtrlDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_EN_CHANGE(IDC_BEGIN, &CProgressCtrlDlg::OnEnChangeBegin)
	ON_EN_CHANGE(IDC_END, &CProgressCtrlDlg::OnEnChangeEnd)
	ON_BN_CLICKED(IDC_SHOW, &CProgressCtrlDlg::OnBnClickedShow)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CProgressCtrlDlg ��Ϣ�������

BOOL CProgressCtrlDlg::OnInitDialog()
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
	this->bStatus = FALSE ;
	this->nStart = 0 ;
	this->nEnd = 100 ;
	this->szInfo = L"��ǰ����" ;
	this->UpdateData ( FALSE ) ;

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CProgressCtrlDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CProgressCtrlDlg::OnPaint()
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
HCURSOR CProgressCtrlDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CProgressCtrlDlg::OnEnChangeBegin()
{
	// ֻ����û�й���ʱ���ܽ�������
	if ( this->bStatus == FALSE )
		this->UpdateData () ;
}

void CProgressCtrlDlg::OnEnChangeEnd()
{
	// ֻ����û�й���ʱ���ܽ�������
	if ( this->bStatus == FALSE )
		this->UpdateData () ;
}

void CProgressCtrlDlg::OnBnClickedShow()
{
	if ( bStatus == TRUE )
	{
		this->MessageBox ( L"�������У�", L"Error" ) ;
		return ;
	}

	// ��������Ƿ�Ϸ�
	if ( this->nEnd <= this->nStart )
	{
		this->MessageBox ( L"���벻�Ϸ���", L"Error" ) ;
		return ;
	}
	
	this->bStatus = TRUE ;

	// ���������������ķ�Χ
	this->ProgressCtrl.SetRange32 ( this->nStart, this->nEnd ) ;
	this->ProgressCtrl2.SetRange32 ( this->nStart, this->nEnd ) ;

	// ���ý���Ϊ��ʼֵ
	this->ProgressCtrl.SetPos ( this->nStart ) ;
	this->ProgressCtrl2.SetPos ( this->nStart ) ;

	// ���ò������̶�����Ϊ100����������Ϊ0��
	this->nStep = ( this->nEnd - this->nStart ) / 100 ;
	if ( this->nStep == 0 )
		this->nStep = 1 ;
	this->ProgressCtrl2.SetStep ( this->nStep ) ;

	// ���ü�ʱ��IDΪ1��ÿ100ms����һ��
	this->SetTimer ( 1, 100, NULL ) ;
}

void CProgressCtrlDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	// �ж��Ƿ�ָ���ļ�ʱ��
	if ( nIDEvent == 1 )
	{
		// ȡ�õ�ǰ����
		int nCurPos1 = this->ProgressCtrl.GetPos () ;
		int nCurPos2 = this->ProgressCtrl2.GetPos () ;

		// ���������������ִ�н������͹رռ�ʱ��
		if ( nCurPos1 >= this->nEnd && nCurPos2 >= this->nEnd )
		{
			this->KillTimer ( 1 ) ;
			this->bStatus = FALSE ;
		}

		// ��λ��ʽ��ÿ�ν�������1
		if ( nCurPos1 < this->nEnd )
			this->ProgressCtrl.SetPos ( nCurPos1 + 1 ) ;

		// �𲽷�ʽ��ÿ�ν�������ָ���Ĳ���
		if ( nCurPos2 < this->nEnd )
			this->ProgressCtrl2.StepIt () ;

		// ��һ���������ĵ�ǰ��Ϣ
		this->szInfo.Format ( L"[��λ��ʽ]��ǰ���ȣ�CurPos=%d,Step=1��", nCurPos1 ) ;
		// �ڶ����������ĵ�ǰ��Ϣ
		this->szInfo2.Format ( L"[�𲽷�ʽ]��ǰ���ȣ�CurPos=%d,Step=%d��", nCurPos2, this->nStep ) ;
		// ������ʾ��Ϣ
		this->UpdateData ( FALSE ) ;
	}

	CDialog::OnTimer(nIDEvent);
}
