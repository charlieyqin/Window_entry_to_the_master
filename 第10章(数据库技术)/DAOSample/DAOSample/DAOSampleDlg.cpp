// DAOSampleDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DAOSample.h"
#include "DAOSampleDlg.h"

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


// CDAOSampleDlg �Ի���




CDAOSampleDlg::CDAOSampleDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDAOSampleDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDAOSampleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BOOK_LIST, BookList);
}

BEGIN_MESSAGE_MAP(CDAOSampleDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_ADD, &CDAOSampleDlg::OnBnClickedAdd)
	ON_BN_CLICKED(IDC_MODIFY, &CDAOSampleDlg::OnBnClickedModify)
	ON_BN_CLICKED(IDC_DEL, &CDAOSampleDlg::OnBnClickedDel)
	ON_BN_CLICKED(IDC_FLUSH, &CDAOSampleDlg::OnBnClickedFlush)
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CDAOSampleDlg ��Ϣ�������

BOOL CDAOSampleDlg::OnInitDialog()
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
	
	// �������ݿ�
	this->db.Open ( L"book.mdb", FALSE, FALSE, NULL ) ;
	this->OnBnClickedFlush () ;

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CDAOSampleDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CDAOSampleDlg::OnPaint()
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
HCURSOR CDAOSampleDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CDAOSampleDlg::OnBnClickedAdd()
{
	// ������ݿ��Ƿ�������
	if ( this->db.IsOpen () == FALSE )
	{
		this->MessageBox ( L"δ�������ݿ⣡" ) ;
		return ;
	}

	// �����¼�����󣬴򿪼�¼��
	CDaoRecordset Record ( &this->db ) ;
	Record.Open ( dbOpenDynaset, L"SELECT * FROM BOOK" ) ;

	// ����Ի�����󣬲�����Ϊ����ӡ�ģʽ
	CMyDlg AddBookDlg ;
	AddBookDlg.SetMode ( TRUE ) ;

	if ( AddBookDlg.DoModal() == IDOK )
	{
		// ʹ��CDaoRecordset::AddNew��������Ҫ��ʼ����¼�¼
		Record.AddNew () ;
		// �����¼�¼
		Record.SetFieldValue ( 1, AddBookDlg.GetBookName().GetBuffer() ) ;
		Record.SetFieldValue ( 2, AddBookDlg.GetAuthor().GetBuffer() ) ;
		Record.SetFieldValue ( 3, AddBookDlg.GetPublish ().GetBuffer() ) ;
		CString szTempStr ;
		szTempStr.Format ( L"%d", AddBookDlg.GetPrice() ) ;
		Record.SetFieldValue ( 4, szTempStr.GetBuffer() ) ;
		// ֻ����ִ��CDaoRecordset::Update������Ż�д�뵽���ݿ�
		Record.Update () ;
		// �رռ�¼��
		Record.Close () ;
		// ˢ�½����б�ؼ�������ʾ
		this->OnBnClickedFlush () ;
	}
}

void CDAOSampleDlg::OnBnClickedModify()
{
	// ������ݿ��Ƿ�������
	if ( this->db.IsOpen () == FALSE )
	{
		this->MessageBox ( L"δ�������ݿ⣡" ) ;
		return ;
	}

	// ����Ƿ�ѡ����Ŀ
	int nCurSel = this->BookList.GetNextItem ( -1,LVNI_SELECTED) ;
	if ( nCurSel == -1 )
	{
		this->MessageBox ( L"û��ѡ����Ŀ��" ) ;
		return ;
	}

	// �����¼�����󣬲��ƶ�ָ�뵽ָ��λ��
	CDaoRecordset Record ( &this->db ) ;
	Record.Open ( dbOpenDynaset, L"SELECT * FROM BOOK" ) ;
	Record.Move ( nCurSel ) ;

	// ����Ի�����󣬲�����Ϊ���޸ġ�ģʽ
	CMyDlg ModBookDlg ;
	ModBookDlg.SetMode ( FALSE ) ;

	// �ѵ�ǰ��¼��Ϣ���õ��Ի���
	COleVariant OleVariant ;
	Record.GetFieldValue ( 1, OleVariant ) ;
	ModBookDlg.SetBookName ( OleVariant.bstrVal ) ;
	Record.GetFieldValue ( 2, OleVariant ) ;
	ModBookDlg.SetAuthor ( OleVariant.bstrVal ) ;
	Record.GetFieldValue ( 3, OleVariant ) ;
	ModBookDlg.SetPublish ( OleVariant.bstrVal ) ;
	Record.GetFieldValue ( 4, OleVariant ) ;
	ModBookDlg.SetPrice ( OleVariant.uintVal ) ;

	if ( ModBookDlg.DoModal () == IDOK )
	{
		// ʹ��CDaoRecordset::Edit��������Ҫ��ʼ�޸ĵ�ǰ��¼
		Record.Edit () ;
		// �޸ĵ�ǰ��¼��Ա
		Record.SetFieldValue ( 1, ModBookDlg.GetBookName().GetBuffer() ) ;
		Record.SetFieldValue ( 2, ModBookDlg.GetAuthor().GetBuffer() ) ;
		Record.SetFieldValue ( 3, ModBookDlg.GetPublish ().GetBuffer() ) ;
		CString szTempStr ;
		szTempStr.Format ( L"%d", ModBookDlg.GetPrice() ) ;
		Record.SetFieldValue ( 4, szTempStr.GetBuffer() ) ;
		// ֻ����ִ��CDaoRecordset::Update������Ż��޸����ݿ��¼
		Record.Update () ;
		// ���ڼ�¼��
		Record.Close () ;
		// ˢ�½����б�ؼ�������ʾ
		this->OnBnClickedFlush () ;
	}
}

void CDAOSampleDlg::OnBnClickedDel()
{
	// ������ݿ��Ƿ�������
	if ( this->db.IsOpen () == FALSE )
	{
		this->MessageBox ( L"δ�������ݿ⣡" ) ;
		return ;
	}

	// ����Ƿ���ѡ����Ŀ
	int nCurSel = this->BookList.GetNextItem ( -1,LVNI_SELECTED) ;
	if ( nCurSel == -1 )
	{
		this->MessageBox ( L"û��ѡ����Ŀ��" ) ;
		return ;
	}

	// �����¼�����󣬲��ƶ�ָ�뵽ָ��λ��
	CDaoRecordset Record ( &this->db ) ;
	Record.Open ( dbOpenDynaset, L"SELECT * FROM BOOK" ) ;
	Record.Move ( nCurSel ) ;
	// ɾ����ǰ��¼
	Record.Delete () ;
	// �رռ�¼��
	Record.Close () ;
	// ˢ�½����б�ؼ�������ʾ
	this->OnBnClickedFlush () ;
}

void CDAOSampleDlg::OnBnClickedFlush()
{
	// ������ݿ��Ƿ�������
	if ( this->db.IsOpen () == FALSE )
	{
		this->MessageBox ( L"δ�������ݿ⣡" ) ;
		return ;
	}

	// ɾ���б�ؼ����м�¼
	this->BookList.DeleteAllItems () ;

	// �����¼�����󣬲��򿪼�¼��
	CDaoRecordset	Record ( &this->db ) ;
	Record.Open ( dbOpenDynaset, L"SELECT * FROM BOOK" ) ;

	UINT		nIndex = 0 ;
	CString		TempStr ;
	COleVariant	OleVariant ;

	// �ƶ�����һ����¼
	Record.MoveFirst () ;
	while( !Record.IsEOF() )
	{
		// ���б�ؼ���Ӽ�¼
		TempStr.Format ( L"%d", nIndex+1 ) ;
		this->BookList.InsertItem ( nIndex, TempStr ) ;

		for ( int i = 1; i <= 3; i++ )
		{
			Record.GetFieldValue ( i, OleVariant ) ;
			this->BookList.SetItemText ( nIndex, i, OleVariant.bstrVal ) ;
		}

		Record.GetFieldValue ( 4, OleVariant ) ;
		TempStr.Format ( L"%d", OleVariant.uintVal ) ;
		this->BookList.SetItemText ( nIndex, 4, TempStr ) ;

		// �Ƶ���һ����¼
		Record.MoveNext () ;
		nIndex++ ;
	}

	// �رռ�¼��
	Record.Close () ;
}

void CDAOSampleDlg::OnDestroy()
{
	CDialog::OnDestroy();

	// TODO: �ڴ˴������Ϣ����������
	this->db.Close () ;
}
