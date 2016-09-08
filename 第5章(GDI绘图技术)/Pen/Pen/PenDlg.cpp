// PenDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Pen.h"
#include "PenDlg.h"

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


// CPenDlg �Ի���




CPenDlg::CPenDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPenDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	// ����ͼ�εĿ�ȡ��߶ȡ����
	const UINT nWidth = 100, nHeight = 100, nDist=20 ;

	// ����ǰ4��ͼ�εĻ�������
	CPoint StartPt ( 20, 20 ) ;
	for ( int i = 0; i < 4; i++ )
	{
		this->MyEllipse[i].rect.left = StartPt.x ;
		this->MyEllipse[i].rect.top = StartPt.y ;
		this->MyEllipse[i].rect.right = this->MyEllipse[i].rect.left + nWidth ;
		this->MyEllipse[i].rect.bottom = this->MyEllipse[i].rect.top + nHeight ;
		StartPt.x += nWidth + nDist ;
	}

	// ���ú�4��ͼ�εĻ�������
	for ( int i = 4; i < 8; i++ )
	{
		this->MyEllipse[i].rect.left = this->MyEllipse[i-4].rect.left ;
		this->MyEllipse[i].rect.top = this->MyEllipse[i-4].rect.top + nHeight + nDist ;
		this->MyEllipse[i].rect.right = this->MyEllipse[i].rect.left + nWidth ;
		this->MyEllipse[i].rect.bottom = this->MyEllipse[i].rect.top + nHeight ;
	}

	// ������ͨ����
	this->MyEllipse[0].pen.CreatePen ( PS_SOLID, 5, RGB(0,0,255) ) ;
	this->MyEllipse[1].pen.CreatePen ( PS_DASH, 1, RGB(0,0,255) ) ;
	this->MyEllipse[2].pen.CreatePen ( PS_DOT, 1, RGB(0,0,255) ) ;
	this->MyEllipse[3].pen.CreatePen ( PS_DASHDOT, 1, RGB(0,0,255) ) ;
	this->MyEllipse[4].pen.CreatePen ( PS_DASHDOTDOT, 1, RGB(0,0,255) ) ;
	this->MyEllipse[5].pen.CreatePen ( PS_NULL, 1, RGB(0,0,255) ) ;
	this->MyEllipse[6].pen.CreatePen ( PS_INSIDEFRAME, 5, RGB(0,0,255) ) ;

	// �������ϻ���
	LOGBRUSH	LogBrush ;
	LogBrush.lbStyle = BS_HATCHED ;
	LogBrush.lbColor = RGB ( 0, 0, 255 ) ;
	LogBrush.lbHatch = HS_DIAGCROSS ;
	this->MyEllipse[7].pen.CreatePen ( PS_GEOMETRIC, 10, &LogBrush ) ;
}

void CPenDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CPenDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


// CPenDlg ��Ϣ�������

BOOL CPenDlg::OnInitDialog()
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

void CPenDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CPenDlg::OnPaint()
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
		// ����ͻ�����DC
		CClientDC cdc ( this ) ;
		CPen* pOldPen = NULL ;
		for ( int i = 0; i < 8; i++ )
		{
			// �ѵ�ǰ�Ļ���ѡ��DC
			pOldPen = cdc.SelectObject ( &this->MyEllipse[i].pen ) ;
			// ��ָ�����������Բ������Ϊ�����Σ����ʵ��Ϊ��Բ
			cdc.Ellipse ( this->MyEllipse[i].rect ) ;
			// ��ԭDC
			cdc.SelectObject ( pOldPen ) ;
		}
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù����ʾ��
//
HCURSOR CPenDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

