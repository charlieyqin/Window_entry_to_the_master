// SimMouseMsgDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SimMouseMsg.h"
#include "SimMouseMsgDlg.h"

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


// CSimMouseMsgDlg �Ի���




CSimMouseMsgDlg::CSimMouseMsgDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSimMouseMsgDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSimMouseMsgDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CSimMouseMsgDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_LEFT_DOWN, &CSimMouseMsgDlg::OnBnClickedLeftDown)
	ON_BN_CLICKED(IDC_RIGHT_DOWN, &CSimMouseMsgDlg::OnBnClickedRightDown)
	ON_BN_CLICKED(IDC_MOUSE_MOVE, &CSimMouseMsgDlg::OnBnClickedMouseMove)
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()


// CSimMouseMsgDlg ��Ϣ�������

BOOL CSimMouseMsgDlg::OnInitDialog()
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

	// ��ʼʱû��ģ����Ϣ������Ϊ0
	this->nType = 0 ;
	// ���û�ͼ����
	this->PaintRect.left = 15 ;
	this->PaintRect.top = 80 ;
	this->PaintRect.right = 310 ;
	this->PaintRect.bottom = 130 ;
	// ��������
	this->FramePen.CreatePen ( PS_SOLID, 3, RGB(0,0,0) ) ;
	// ������ˢ
	this->RedBrush.CreateSolidBrush ( RGB(255,0,0) ) ;
	this->GreenBrush.CreateSolidBrush ( RGB(0,255,0) ) ;
	this->BlueBrush.CreateSolidBrush ( RGB(0,0,255) ) ;

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CSimMouseMsgDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CSimMouseMsgDlg::OnPaint()
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
		CClientDC cdc(this) ;
		CPen* pOldPen = cdc.SelectObject ( &this->FramePen ) ;
		CBrush* pOldBrush = NULL ;
		switch ( this->nType )
		{
		case 1:	pOldBrush = cdc.SelectObject ( &this->RedBrush ) ;		break ;
		case 2:	pOldBrush = cdc.SelectObject ( &this->GreenBrush ) ;	break ;
		case 3:	pOldBrush = cdc.SelectObject ( &this->BlueBrush ) ;		break ;
		}
		cdc.Rectangle ( &this->PaintRect ) ;
		if ( pOldBrush )
			cdc.SelectObject ( pOldBrush ) ;
		cdc.SelectObject ( pOldPen ) ;

		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù����ʾ��
//
HCURSOR CSimMouseMsgDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// ģ��������������Ϣ
void CSimMouseMsgDlg::OnBnClickedLeftDown()
{
	// ��ȡ��ͼ�����ڵ�һ��
	CPoint point(50,100) ;
	// �ѿͻ���������ת��Ϊ��Ļ����
	this->ClientToScreen ( &point ) ;

	// ����ԭ�������λ��
	POINT OldPoint ;
	::GetCursorPos ( &OldPoint ) ;
	// ������굽��λ��
	::SetCursorPos ( point.x, point.y ) ;
	// ģ����굥����Ϣ
	mouse_event ( MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0 ) ;
	mouse_event ( MOUSEEVENTF_LEFTUP, 0, 0, 0, 0 ) ;
	// ������굽ԭ��λ��
	::SetCursorPos ( OldPoint.x, OldPoint.y ) ;
}

// ģ������Ҽ�������Ϣ
void CSimMouseMsgDlg::OnBnClickedRightDown()
{
	// ��ȡ��ͼ�����ڵ�һ��
	CPoint point(50,100) ;
	// �ѿͻ���������ת��Ϊ��Ļ����
	this->ClientToScreen ( &point ) ;

	// ����ԭ�������λ��
	POINT OldPoint ;
	::GetCursorPos ( &OldPoint ) ;
	// ������굽��λ��
	::SetCursorPos ( point.x, point.y ) ;
	// ģ����굥����Ϣ
	mouse_event ( MOUSEEVENTF_RIGHTDOWN, 0, 0, 0, 0 ) ;
	mouse_event ( MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0 ) ;
	// ������굽ԭ��λ��
	::SetCursorPos ( OldPoint.x, OldPoint.y ) ;
}

// ģ������ƶ���Ϣ
void CSimMouseMsgDlg::OnBnClickedMouseMove()
{
	// ��ȡ��ͼ�����ڵ�һ��
	CPoint point ( 50, 100 ) ;
	// ģ������ƶ���Ϣ������ʹ�õ����������
	this->PostMessage ( WM_MOUSEMOVE, 0, point.x|(point.y<<16) ) ;
}

void CSimMouseMsgDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// ֻ��Ӧ��ͼ�����ڵ������Ϣ
	if ( this->PaintRect.PtInRect(point) == TRUE )
	{
		this->nType = 1 ;
		// ֪ͨӦ�ó����ػ�
		this->InvalidateRect ( &this->PaintRect, FALSE ) ;
	}
	CDialog::OnLButtonDown(nFlags, point);
}

void CSimMouseMsgDlg::OnRButtonDown(UINT nFlags, CPoint point)
{
	// ֻ��Ӧ��ͼ�����ڵ������Ϣ
	if ( this->PaintRect.PtInRect(point) == TRUE )
	{
		this->nType = 2 ;
		// ֪ͨӦ�ó����ػ�
		this->InvalidateRect ( &this->PaintRect, FALSE ) ;
	}
	CDialog::OnRButtonDown(nFlags, point);
}

void CSimMouseMsgDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// ֻ��Ӧ��ͼ�����ڵ������Ϣ
	if ( this->PaintRect.PtInRect(point) == TRUE )
	{
		this->nType = 3 ;
		// ֪ͨӦ�ó����ػ�
		this->InvalidateRect ( &this->PaintRect, FALSE ) ;
	}
	CDialog::OnMouseMove(nFlags, point);
}
