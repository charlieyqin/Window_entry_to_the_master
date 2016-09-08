// ODBCSampleDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ODBCSample.h"
#include "ODBCSampleDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include "MyDlg.h"

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


// CODBCSampleDlg �Ի���




CODBCSampleDlg::CODBCSampleDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CODBCSampleDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CODBCSampleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BOOK_LIST, BookList);
}

BEGIN_MESSAGE_MAP(CODBCSampleDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_ADD, &CODBCSampleDlg::OnBnClickedAdd)
	ON_BN_CLICKED(IDC_MODIFY, &CODBCSampleDlg::OnBnClickedModify)
	ON_BN_CLICKED(IDC_DEL, &CODBCSampleDlg::OnBnClickedDel)
	ON_BN_CLICKED(IDC_FLUSH, &CODBCSampleDlg::OnBnClickedFlush)
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CODBCSampleDlg ��Ϣ�������

BOOL CODBCSampleDlg::OnInitDialog()
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
	this->BookList.InsertColumn ( 0, L" ID",LVCFMT_CENTER, 30 ) ;
	this->BookList.InsertColumn ( 1, L" ��   ��",LVCFMT_CENTER, 160 ) ;
	this->BookList.InsertColumn ( 2, L"����",	LVCFMT_CENTER, 100 ) ;
	this->BookList.InsertColumn ( 3, L"������",	LVCFMT_CENTER, 100 ) ;
	this->BookList.InsertColumn ( 4, L"�۸�",	LVCFMT_CENTER, 60 ) ;
	this->BookList.SetExtendedStyle ( this->BookList.GetExtendedStyle()|LVS_EX_FULLROWSELECT) ;

	Record.Open ( CRecordset::dynaset, L"SELECT * FROM BOOK" ) ;
	this->OnBnClickedFlush () ;

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CODBCSampleDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CODBCSampleDlg::OnPaint()
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
HCURSOR CODBCSampleDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CODBCSampleDlg::OnBnClickedAdd()
{
	// ����Ի�����󣬲�����Ϊ����ӡ�ģʽ
	CMyDlg BookInfoDlg ;
	BookInfoDlg.SetMode ( TRUE ) ;

	if ( BookInfoDlg.DoModal () == IDOK )
	{
		// ʹ��CRecordset::AddNew��������Ҫ��ʼ�����¼�¼
		Record.AddNew () ;
		// �����¼�¼��Ա����CBook�ฺ����������ֶ�֮��Ĺ���
		Record.m_BookName = BookInfoDlg.GetBookName () ;
		Record.m_Author = BookInfoDlg.GetAuthor () ;
		Record.m_Publish = BookInfoDlg.GetPublish () ;
		Record.m_Price = BookInfoDlg.GetPrice () ;
		// ֻ����ִ��CRecordset::Update������Ż�Ѽ�¼д�뵽���ݿ�
		Record.Update () ;

		// ˢ�½����б�ؼ���������ʾ
		this->OnBnClickedFlush() ;
	}
}

void CODBCSampleDlg::OnBnClickedModify()
{
	// ����Ƿ�ѡ��ĳһ��Ŀ
	int nCurSel = this->BookList.GetNextItem(-1,LVNI_SELECTED) ;
	if ( nCurSel == -1 )
	{
		this->MessageBox ( L"δѡ����Ŀ��" ) ;
		return ;
	}

	// ����Ի�����󣬲�����Ϊ���޸ġ�ģʽ
	CMyDlg BookInfoDlg ;
	BookInfoDlg.SetMode ( FALSE ) ;

	// ���õ�����λ��
	Record.SetAbsolutePosition ( nCurSel + 1 ) ;
	// ����Ҫ�޸ĵĵ�ǰ��¼���õ����޸��鼮��Ϣ�Ի���
	BookInfoDlg.SetBookName ( Record.m_BookName ) ;
	BookInfoDlg.SetAuthor ( Record.m_Author ) ;
	BookInfoDlg.SetPublish ( Record.m_Publish ) ;
	BookInfoDlg.SetPrice ( Record.m_Price ) ;

	if ( BookInfoDlg.DoModal () == IDOK )
	{
		// ʹ��CRecordset::Edit��������Ҫ��ʼ�޸ĵ�ǰ��¼
		Record.Edit () ;
		// �޸ĵ�ǰ��¼��Ա����CBook�ฺ����������ֶ�֮��Ĺ���
		Record.m_BookName = BookInfoDlg.GetBookName () ;
		Record.m_Author = BookInfoDlg.GetAuthor () ;
		Record.m_Publish = BookInfoDlg.GetPublish () ;
		Record.m_Price = BookInfoDlg.GetPrice () ;
		// ֻ����ִ��CRecordset::Update������Ż��޸����ݿ��¼
		Record.Update () ;

		// ˢ�½����б�ؼ���������ʾ
		this->OnBnClickedFlush () ;
	}
}

void CODBCSampleDlg::OnBnClickedDel()
{
	// ����Ƿ�ѡ��ĳһ��Ŀ
	int nCurSel = this->BookList.GetNextItem(-1,LVNI_SELECTED) ;
	if ( nCurSel == -1 )
	{
		this->MessageBox ( L"δѡ����Ŀ��" ) ;
		return ;
	}
	
	// ���õ���¼���ľ���λ��
	Record.SetAbsolutePosition ( nCurSel + 1 ) ;
	// ɾ����ǰ��¼
	Record.Delete () ;
	// ˢ�½����б�ؼ���������ʾ
	this->OnBnClickedFlush() ;
}

void CODBCSampleDlg::OnBnClickedFlush()
{
	// ɾ���б�ؼ������м�¼
	this->BookList.DeleteAllItems () ;

	UINT nIndex = 0 ;
	CString TempStr ;

	// �ƶ�ָ��Ե�һ����¼
	Record.MoveFirst () ;

	// ����Ƿ��Ѿ������¼��β��
	while ( !Record.IsEOF() )
	{
		// ���б�ؼ���Ӽ�¼
		TempStr.Format ( L"%d", nIndex+1 ) ;
		this->BookList.InsertItem ( nIndex, TempStr ) ;

		// �����б�ؼ���ǰ��¼����
		this->BookList.SetItemText ( nIndex, 1, Record.m_BookName ) ;
		this->BookList.SetItemText ( nIndex, 2, Record.m_Author ) ;
		this->BookList.SetItemText ( nIndex, 3, Record.m_Publish ) ;

		TempStr.Format ( L"%d", Record.m_Price ) ;
		this->BookList.SetItemText ( nIndex, 4, TempStr ) ;

		// �Ƶ���һ����¼
		Record.MoveNext () ;
		nIndex++ ;
	}
}


void CODBCSampleDlg::OnDestroy()
{
	CDialog::OnDestroy();

	// TODO: �ڴ˴������Ϣ����������
	this->Record.Close () ;
}
