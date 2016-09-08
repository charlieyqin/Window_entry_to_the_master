// BrushDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Brush.h"
#include "BrushDlg.h"

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


// CBrushDlg �Ի���




CBrushDlg::CBrushDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBrushDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	const UINT nWidth = 100, nHeight = 100, nDist = 30 ;

	// ����ǰ4��ͼ�εĻ�������
	CPoint StartPt ( 20, 30 ) ;
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

	// ������ɫ��ˢ
	this->MyEllipse[0].brush.CreateSolidBrush ( RGB(0,0,255) ) ;

	// ������Ӱ��ˢ
	this->MyEllipse[1].brush.CreateHatchBrush ( HS_BDIAGONAL, RGB(0,0,255) ) ;
	this->MyEllipse[2].brush.CreateHatchBrush ( HS_CROSS, RGB(0,0,255) ) ;
	this->MyEllipse[3].brush.CreateHatchBrush ( HS_DIAGCROSS, RGB(0,0,255) ) ;
	this->MyEllipse[4].brush.CreateHatchBrush ( HS_FDIAGONAL, RGB(0,0,255) ) ;
	this->MyEllipse[5].brush.CreateHatchBrush ( HS_HORIZONTAL, RGB(0,0,255) ) ;
	this->MyEllipse[6].brush.CreateHatchBrush ( HS_VERTICAL, RGB(0,0,255) ) ;

	// �������λ�ˢ
	CBitmap bmp ;
	bmp.LoadBitmapW ( IDB_BRUSH ) ;
	this->MyEllipse[7].brush.CreatePatternBrush ( &bmp ) ;
}

void CBrushDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CBrushDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


// CBrushDlg ��Ϣ�������

BOOL CBrushDlg::OnInitDialog()
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

void CBrushDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CBrushDlg::OnPaint()
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
		CBrush* pOldBrush = NULL ;
		for ( int i = 0; i < 8; i++ )
		{
			// �ѵ�ǰ�Ļ���ѡ��DC
			pOldBrush = cdc.SelectObject ( &this->MyEllipse[i].brush ) ;
			// ��ָ�����������Բ������Ϊ�����Σ����ʵ��Ϊ��Բ
			cdc.Ellipse ( this->MyEllipse[i].rect ) ;
			// ��ԭDC
			cdc.SelectObject ( pOldBrush ) ;
		}

		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù����ʾ��
//
HCURSOR CBrushDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

