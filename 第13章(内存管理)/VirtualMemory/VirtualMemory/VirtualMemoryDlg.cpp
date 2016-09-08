// VirtualMemoryDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "VirtualMemory.h"
#include "VirtualMemoryDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include "SelProcess.h"


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


// CVirtualMemoryDlg �Ի���




CVirtualMemoryDlg::CVirtualMemoryDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CVirtualMemoryDlg::IDD, pParent)
	, szProcess(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CVirtualMemoryDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_VM_LIST, VMList);
	DDX_Text(pDX, IDC_TAG_PROCESS, szProcess);
	DDX_Control(pDX, IDC_CHECK1, CommitCheck);
	DDX_Control(pDX, IDC_CHECK2, ReserveCheck);
	DDX_Control(pDX, IDC_CHECK3, FreeCheck);
}

BEGIN_MESSAGE_MAP(CVirtualMemoryDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_FLUSH, &CVirtualMemoryDlg::OnBnClickedFlush)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_SELECT, &CVirtualMemoryDlg::OnBnClickedSelect)
	ON_BN_CLICKED(IDC_CHECK1, &CVirtualMemoryDlg::OnBnClickedCheck1)
	ON_BN_CLICKED(IDC_CHECK2, &CVirtualMemoryDlg::OnBnClickedCheck2)
	ON_BN_CLICKED(IDC_CHECK3, &CVirtualMemoryDlg::OnBnClickedCheck3)
END_MESSAGE_MAP()


// CVirtualMemoryDlg ��Ϣ�������

BOOL CVirtualMemoryDlg::OnInitDialog()
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
	this->VMInfo.VM_GetSysInfo () ;
	this->VMInfo.VM_GetMemStatus () ;

	this->VMList.InsertColumn ( 0, L"ID", LVCFMT_LEFT, 30 ) ;
	this->VMList.InsertColumn ( 1, L"��ַ", LVCFMT_LEFT, 60 ) ;
	this->VMList.InsertColumn ( 2, L"��С", LVCFMT_CENTER, 60 ) ;
	this->VMList.InsertColumn ( 3, L"״̬", LVCFMT_CENTER, 65 ) ;
	this->VMList.InsertColumn ( 4, L"����", LVCFMT_CENTER, 65 ) ;
	this->VMList.InsertColumn ( 5, L"��ʼ����", LVCFMT_CENTER, 70 ) ;
	this->VMList.InsertColumn ( 6, L"���ʱ���", LVCFMT_CENTER, 70 ) ;
	this->VMList.SetExtendedStyle( this->VMList.GetExtendedStyle()|LVS_EX_FULLROWSELECT ) ;

	this->CommitCheck.SetCheck ( BST_CHECKED ) ;
	this->ReserveCheck.SetCheck ( BST_CHECKED ) ;
	this->FreeCheck.SetCheck ( BST_UNCHECKED ) ;

	this->SetTimer ( 1, 1000, NULL ) ;
	this->dwSelProcessId = GetCurrentProcessId () ;

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CVirtualMemoryDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CVirtualMemoryDlg::OnPaint()
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
HCURSOR CVirtualMemoryDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CVirtualMemoryDlg::OnBnClickedFlush()
{
	this->VMList.DeleteAllItems () ;
	
	if ( this->VMInfo.VM_GetMemInfoList ( this->dwSelProcessId ) == FALSE )
	{
		this->MessageBox ( L"��ȡ��Ϣʧ�ܣ�" ) ;
		return ;
	}

	CString		TempStr ;
	UINT nIndex = 0 ;
	list<MEMORY_BASIC_INFORMATION>::iterator p ;
	for ( p = this->VMInfo.MemList.begin(); p != this->VMInfo.MemList.end(); p++ ) 
	{
		if ( ( p->State == MEM_COMMIT && this->CommitCheck.GetCheck()==BST_UNCHECKED ) || \
			 ( p->State == MEM_RESERVE && this->ReserveCheck.GetCheck()==BST_UNCHECKED ) || \
			 ( p->State == MEM_FREE && this->FreeCheck.GetCheck()==BST_UNCHECKED ) )
			 continue ;

		TempStr.Format ( L"%d", nIndex+1 ) ;
		this->VMList.InsertItem ( nIndex, TempStr ) ;

		// [1]��ʼ��ַ
		TempStr.Format ( L"%08X", p->BaseAddress ) ;
		this->VMList.SetItemText ( nIndex, 1, TempStr ) ;

		// [2]��С
		TempStr.Format ( L"%08X", p->RegionSize ) ;
		this->VMList.SetItemText ( nIndex, 2, TempStr ) ;

		// [3]״̬
		switch ( p->State )
		{
		case MEM_COMMIT:	TempStr = L"�ύ" ;	break ;
		case MEM_RESERVE:	TempStr = L"����" ;	break ;
		case MEM_FREE:		TempStr = L"����" ;	break ;
		}
		this->VMList.SetItemText ( nIndex, 3, TempStr ) ;

		// [4]����
		switch ( p->Type )
		{
		case MEM_IMAGE:		TempStr = L"ӳ��";	break ;
		case MEM_PRIVATE:	TempStr = L"˽��" ;	break ;
		case MEM_MAPPED:	TempStr = L"ӳ��" ;	break ;
		}
		this->VMList.SetItemText ( nIndex, 4, TempStr ) ;

		// [5]��ʼ����
		switch ( p->AllocationProtect )
		{
		case PAGE_READONLY:				TempStr = L"-R--";	break;
		case PAGE_READWRITE:			TempStr = L"-RW-";	break;
		case PAGE_WRITECOPY:			TempStr = L"-RWC";	break;
		case PAGE_EXECUTE:				TempStr = L"E---";	break;
		case PAGE_EXECUTE_READ:			TempStr = L"ER--";	break;
		case PAGE_EXECUTE_READWRITE:	TempStr = L"ERW-";	break;
		case PAGE_EXECUTE_WRITECOPY:	TempStr = L"ERWC";	break;
		case PAGE_NOACCESS:				TempStr = L"----";	break;
		default:						TempStr = L"----";	break;
		}
		this->VMList.SetItemText ( nIndex, 5, TempStr ) ;


		// [6]���ʱ���
		switch ( p->Protect )
		{
		case PAGE_READONLY:				TempStr = L"-R--";	break;
		case PAGE_READWRITE:			TempStr = L"-RW-";	break;
		case PAGE_WRITECOPY:			TempStr = L"-RWC";	break;
		case PAGE_EXECUTE:				TempStr = L"E---";	break;
		case PAGE_EXECUTE_READ:			TempStr = L"ER--";	break;
		case PAGE_EXECUTE_READWRITE:	TempStr = L"ERW-";	break;
		case PAGE_EXECUTE_WRITECOPY:	TempStr = L"ERWC";	break;
		case PAGE_NOACCESS:				TempStr = L"----";	break;
		default:						TempStr = L"----";	break;
		}
		this->VMList.SetItemText ( nIndex, 6, TempStr ) ;

		nIndex ++ ;
	}
}

void CVirtualMemoryDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if ( nIDEvent == 1 )
	{
		this->VMInfo.VM_GetSysInfo () ;
		this->VMInfo.VM_GetMemStatus () ;

		CString TempStr ;
		TempStr.Format ( L"%08X", this->VMInfo.SysInfo.dwPageSize ) ;
		this->SetDlgItemText ( IDC_PAGE_SIZE, TempStr ) ;
		TempStr.Format ( L"%08X", this->VMInfo.SysInfo.lpMinimumApplicationAddress ) ;
		this->SetDlgItemText ( IDC_MIN_ADDR, TempStr ) ;
		TempStr.Format ( L"%08X", this->VMInfo.SysInfo.lpMaximumApplicationAddress ) ;
		this->SetDlgItemText ( IDC_MAX_ADDR, TempStr ) ;
		TempStr.Format ( L"%08X", this->VMInfo.MemStatus.dwTotalPhys ) ;
		this->SetDlgItemText ( IDC_TOTAL_PHYSICAL, TempStr ) ;
		TempStr.Format ( L"%08X", this->VMInfo.MemStatus.dwAvailPhys ) ;
		this->SetDlgItemText ( IDC_VALID_PHYSIC, TempStr ) ;
		TempStr.Format ( L"%08X", this->VMInfo.MemStatus.dwTotalPageFile ) ;
		this->SetDlgItemText ( IDC_TOTAL_PAGE, TempStr ) ;
		TempStr.Format ( L"%08X", this->VMInfo.MemStatus.dwAvailPageFile ) ;
		this->SetDlgItemText ( IDC_VALID_PAGE, TempStr ) ;
		TempStr.Format ( L"%08X", this->VMInfo.MemStatus.dwTotalVirtual ) ;
		this->SetDlgItemText ( IDC_TOTAL_VM, TempStr ) ;
		TempStr.Format ( L"%08X", this->VMInfo.MemStatus.dwAvailVirtual ) ;
		this->SetDlgItemText ( IDC_VALID_VM, TempStr ) ;
	}

	CDialog::OnTimer(nIDEvent);
}

void CVirtualMemoryDlg::OnBnClickedSelect()
{
	CSelProcess dlg ;
	if ( dlg.DoModal() == IDOK )
	{
		this->dwSelProcessId = dlg.GetSelProcessId () ;
		this->szProcess.Format ( L"[%04d]%s", dlg.GetSelProcessId(), dlg.GetSelProcessName () ) ;
		this->UpdateData ( FALSE ) ;
	}
}

void CVirtualMemoryDlg::OnBnClickedCheck1()
{
	this->OnBnClickedFlush () ;
}

void CVirtualMemoryDlg::OnBnClickedCheck2()
{
	this->OnBnClickedFlush () ;
}

void CVirtualMemoryDlg::OnBnClickedCheck3()
{
	this->OnBnClickedFlush () ;
}
