// SimKeyMsgDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SimKeyMsg.h"
#include "SimKeyMsgDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define HOTKEY_POSTMESSAGE	1001
#define HOTKEY_KEYBDEVENT	1002


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


// CSimKeyMsgDlg �Ի���




CSimKeyMsgDlg::CSimKeyMsgDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSimKeyMsgDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSimKeyMsgDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CSimKeyMsgDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_UP, &CSimKeyMsgDlg::OnBnClickedUp)
	ON_BN_CLICKED(IDC_DOWN, &CSimKeyMsgDlg::OnBnClickedDown)
	ON_BN_CLICKED(IDC_LEFT, &CSimKeyMsgDlg::OnBnClickedLeft)
	ON_BN_CLICKED(IDC_RIGHT, &CSimKeyMsgDlg::OnBnClickedRight)
	ON_BN_CLICKED(IDC_WIN_R, &CSimKeyMsgDlg::OnBnClickedWinR)
	ON_BN_CLICKED(IDC_WIN_U, &CSimKeyMsgDlg::OnBnClickedWinU)
	ON_BN_CLICKED(IDC_CTRL_SHIFT, &CSimKeyMsgDlg::OnBnClickedCtrlShift)
	ON_BN_CLICKED(IDC_ALT_TAB, &CSimKeyMsgDlg::OnBnClickedAltTab)
END_MESSAGE_MAP()


// CSimKeyMsgDlg ��Ϣ�������

BOOL CSimKeyMsgDlg::OnInitDialog()
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

void CSimKeyMsgDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CSimKeyMsgDlg::OnPaint()
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
HCURSOR CSimKeyMsgDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

BOOL CSimKeyMsgDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���
	if ( pMsg->message == WM_KEYDOWN )
	{
		switch ( pMsg->wParam )
		{
		case VK_UP:		this->MessageBox ( L"�㰴���ˡ�����" ) ;	break ;
		case VK_DOWN:	this->MessageBox ( L"�㰴���ˡ�����" ) ;	break ;
		case VK_LEFT:	this->MessageBox ( L"�㰴���ˡ�����" ) ;	break ;
		case VK_RIGHT:	this->MessageBox ( L"�㰴���ˡ�����" ) ;	break ;
		}
	}

	return CDialog::PreTranslateMessage(pMsg);
}

void CSimKeyMsgDlg::OnBnClickedUp()
{
	this->PostMessage ( WM_KEYDOWN, VK_UP, 0 ) ;
}

void CSimKeyMsgDlg::OnBnClickedDown()
{
	this->PostMessage ( WM_KEYDOWN, VK_DOWN, 0 ) ;
}

void CSimKeyMsgDlg::OnBnClickedLeft()
{
	this->PostMessage ( WM_KEYDOWN, VK_LEFT, 0 ) ;
}

void CSimKeyMsgDlg::OnBnClickedRight()
{
	this->PostMessage ( WM_KEYDOWN, VK_RIGHT, 0 ) ;
}

void CSimKeyMsgDlg::OnBnClickedWinR()
{
	keybd_event ( VK_LWIN, 0, 0, 0 ) ;
	keybd_event ( 'R', 0, 0, 0 ) ;
	keybd_event ( 'R', 0, KEYEVENTF_KEYUP, 0 ) ;
	keybd_event ( VK_LWIN, 0, KEYEVENTF_KEYUP, 0 ) ;
}

void CSimKeyMsgDlg::OnBnClickedWinU()
{
	keybd_event ( VK_LWIN, 0, 0, 0 ) ;
	keybd_event ( 'U', 0, 0, 0 ) ;
	keybd_event ( 'U', 0, KEYEVENTF_KEYUP, 0 ) ;
	keybd_event ( VK_LWIN, 0, KEYEVENTF_KEYUP, 0 ) ;
}

void CSimKeyMsgDlg::OnBnClickedCtrlShift()
{
	keybd_event ( VK_CONTROL, 0, 0, 0 ) ;
	keybd_event ( VK_SHIFT, 0, 0, 0 ) ;
	keybd_event ( VK_SHIFT, 0, KEYEVENTF_KEYUP, 0 ) ;
	keybd_event ( VK_CONTROL, 0, KEYEVENTF_KEYUP, 0 ) ;
}

void CSimKeyMsgDlg::OnBnClickedAltTab()
{
	keybd_event ( VK_MENU, 0, 0, 0 ) ;
	keybd_event ( VK_TAB, 0, 0, 0 ) ;
	Sleep ( 1000 ) ;
	keybd_event ( VK_TAB, 0, KEYEVENTF_KEYUP, 0 ) ;
	keybd_event ( VK_MENU, 0, KEYEVENTF_KEYUP, 0 ) ;
}
