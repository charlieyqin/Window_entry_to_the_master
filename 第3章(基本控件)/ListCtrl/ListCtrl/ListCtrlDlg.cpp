// ListCtrlDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ListCtrl.h"
#include "ListCtrlDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include "AddInfoDlg.h"


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


// CListCtrlDlg �Ի���




CListCtrlDlg::CListCtrlDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CListCtrlDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CListCtrlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST, list);
}

BEGIN_MESSAGE_MAP(CListCtrlDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_ADD, &CListCtrlDlg::OnBnClickedAdd)
	ON_BN_CLICKED(IDC_DEL, &CListCtrlDlg::OnBnClickedDel)
END_MESSAGE_MAP()


// CListCtrlDlg ��Ϣ�������

BOOL CListCtrlDlg::OnInitDialog()
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

	this->InitListCtrl () ;

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CListCtrlDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CListCtrlDlg::OnPaint()
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
HCURSOR CListCtrlDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CListCtrlDlg::OnBnClickedAdd()
{
	CAddInfoDlg dlg ;
	if ( dlg.DoModal () != IDCANCEL )
	{
		// ȡ���б�ؼ�����Ŀ����
		int nItemNum = this->list.GetItemCount () ;
		// �����Ա��Ϣ���б�ؼ�
		this->list.InsertItem ( nItemNum, dlg.NEW_GetName() ) ;
		this->list.SetItemText ( nItemNum, 1, dlg.NEW_GetId() ) ;
		this->list.SetItemText ( nItemNum, 2, dlg.NEW_GetGender() ) ;
		this->list.SetItemText ( nItemNum, 3, dlg.NEW_GetAddr () ) ;
	}
}

void CListCtrlDlg::OnBnClickedDel()
{
	// ȡ�õ�ǰ��ѡ�����Ŀ����
	int nCurSel = this->list.GetNextItem ( -1, LVNI_SELECTED ) ;
	if ( nCurSel != -1 )
		this->list.DeleteItem ( nCurSel ) ;
}

VOID CListCtrlDlg::InitListCtrl(void)
{
	this->list.InsertColumn ( 0, L"  ����",	LVCFMT_CENTER, 80 ) ;
	this->list.InsertColumn ( 1, L"���֤",	LVCFMT_CENTER, 200 ) ;
	this->list.InsertColumn ( 2, L"�Ա�",	LVCFMT_CENTER, 60 ) ;
	this->list.InsertColumn ( 3, L"����",	LVCFMT_CENTER, 80 ) ;
	this->list.SetExtendedStyle ( this->list.GetExtendedStyle()|LVS_EX_FULLROWSELECT) ;

	this->list.InsertItem ( 0, L"������" ) ;
	this->list.SetItemText ( 0, 1, L"1234356789123456789" ) ;
	this->list.SetItemText ( 0, 2, L"��" ) ;
	this->list.SetItemText ( 0, 3, L"�䵱" ) ;

	this->list.InsertItem ( 1, L"���ʦ̫" ) ;
	this->list.SetItemText ( 1, 1, L"123456789987654321" ) ;
	this->list.SetItemText ( 1, 2, L"Ů" ) ;
	this->list.SetItemText ( 1, 3, L"��ü" ) ;

	this->list.InsertItem ( 2, L"������" ) ;
	this->list.SetItemText ( 2, 1, L"431354345657657686" ) ;
	this->list.SetItemText ( 2, 2, L"��" ) ;
	this->list.SetItemText ( 2, 3, L"����" ) ;

	this->list.InsertItem ( 3, L"�Ƿ�" ) ;
	this->list.SetItemText ( 3, 1, L"123123132132321321" ) ;
	this->list.SetItemText ( 3, 2, L"��" ) ;
	this->list.SetItemText ( 3, 3, L"ؤ��" ) ;

	return VOID();
}
