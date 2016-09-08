// FontDlgDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "FontDlg.h"
#include "FontDlgDlg.h"

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


// CFontDlgDlg �Ի���




CFontDlgDlg::CFontDlgDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFontDlgDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFontDlgDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CFontDlgDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_SET_FONT, &CFontDlgDlg::OnBnClickedSetFont)
END_MESSAGE_MAP()


// CFontDlgDlg ��Ϣ�������

BOOL CFontDlgDlg::OnInitDialog()
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
	memset ( &this->LogFont, 0, sizeof(LOGFONT)) ;

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CFontDlgDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CFontDlgDlg::OnPaint()
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

		CFont font ;			// ��������
		CClientDC dc ( this ) ;	// ���嵱ǰ����DC
		// ���������õ����Դ�������
		font.CreateFontIndirect ( &LogFont ) ;
		// ��������ѡ��DC
		CFont* pFont = dc.SelectObject ( &font ) ;
		// �����Ի汳��ģʽΪ͸��
		dc.SetBkMode ( TRANSPARENT ) ;
		// ����������ɫ
		dc.SetTextColor ( this->color ) ;
		// �����ʾ����
		dc.TextOut ( 20, 25, L"��������" ) ;
		// ��������ѡ��DC����ԭ
		dc.SelectObject ( pFont ) ;
		// ɾ������
		font.DeleteObject () ;
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù����ʾ��
//
HCURSOR CFontDlgDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CFontDlgDlg::OnBnClickedSetFont()
{
	// ���塰���塱�Ի���
	CFontDialog dlg ;
	if ( dlg.DoModal() == IDOK )
	{
		// ȡ�õ�ǰ���õ���������
		dlg.GetCurrentFont ( &LogFont ) ;
		// ȡ�õ�ǰ���õ�������ɫ
		this->color = dlg.GetColor () ;
		// ֪ͨ�����ػ棬�Ա�ִ����OnPaint�������Զ�����ػ����
		this->Invalidate () ;
	}
}
