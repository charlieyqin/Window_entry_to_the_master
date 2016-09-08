// ColorDlgDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ColorDlg.h"
#include "ColorDlgDlg.h"

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


// CColorDlgDlg �Ի���




CColorDlgDlg::CColorDlgDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CColorDlgDlg::IDD, pParent)
	, r(0)
	, g(0)
	, b(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CColorDlgDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_R, r);
	DDX_Text(pDX, IDC_G, g);
	DDX_Text(pDX, IDC_B, b);
}

BEGIN_MESSAGE_MAP(CColorDlgDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_SET_COLOR, &CColorDlgDlg::OnBnClickedSetColor)
	ON_EN_CHANGE(IDC_R, &CColorDlgDlg::OnEnChangeR)
	ON_EN_CHANGE(IDC_G, &CColorDlgDlg::OnEnChangeG)
	ON_EN_CHANGE(IDC_B, &CColorDlgDlg::OnEnChangeB)
END_MESSAGE_MAP()


// CColorDlgDlg ��Ϣ�������

BOOL CColorDlgDlg::OnInitDialog()
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
	this->r = this->g = this->b = 255 ;
	this->UpdateData ( FALSE ) ;

	this->ColorShowRect.left = 147 ;
	this->ColorShowRect.top = 30 ;
	this->ColorShowRect.right = 245 ;
	this->ColorShowRect.bottom = 114 ;

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CColorDlgDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CColorDlgDlg::OnPaint()
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

		CClientDC dc (this) ;	// ���崰��DC
		CBrush* pOldBrush ;		// ���ڱ����ϵĻ�ˢ
		CBrush brush ;			// �����µĻ�ˢ
		// ����ָ������ɫ������ˢ
		brush.CreateSolidBrush ( RGB(this->r,this->g,this->b) ) ;
		// ���»�ˢѡ��DC
		pOldBrush = dc.SelectObject ( &brush ) ;
		// ����ָ����������ƾ�������
		dc.Rectangle ( &this->ColorShowRect ) ;
		// ��ԭ�����ϻ�ˢѡ��DC
		dc.SelectObject ( pOldBrush ) ;
		// ɾ���»�ˢ
		brush.DeleteObject () ;
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù����ʾ��
//
HCURSOR CColorDlgDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CColorDlgDlg::OnBnClickedSetColor()
{
	// ���塰��ɫ���Ի���
	CColorDialog dlg ;
	if ( dlg.DoModal () == IDOK )
	{
		// ȡ��ѡȡ����ɫ
		COLORREF color = dlg.GetColor () ;
		// ȡ�ú�ɫֵ
		this->r = GetRValue ( color ) ;
		// ȡ����ɫֵ
		this->g = GetGValue ( color ) ;
		// ȡ����ɫֵ
		this->b = GetBValue ( color ) ;
		// ���½�����ʾ����ɫֵ
		this->UpdateData ( FALSE ) ;
		// ���½�����Ƶ�ɫ��
		this->Invalidate () ;
	}
}

void CColorDlgDlg::OnEnChangeR()
{
	this->UpdateData () ;
	this->Invalidate () ;
}

void CColorDlgDlg::OnEnChangeG()
{
	this->UpdateData () ;
	this->Invalidate () ;
}

void CColorDlgDlg::OnEnChangeB()
{
	this->UpdateData () ;
	this->Invalidate () ;
}
