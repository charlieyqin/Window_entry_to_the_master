// FileSystemDlg.cpp : implementation file
//

#include "stdafx.h"
#include "FileSystem.h"
#include "FileSystemDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFileSystemDlg dialog

CFileSystemDlg::CFileSystemDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFileSystemDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFileSystemDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFileSystemDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFileSystemDlg)
	DDX_Control(pDX, IDC_FILE_LIST, m_FileList);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CFileSystemDlg, CDialog)
	//{{AFX_MSG_MAP(CFileSystemDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(ID_STALL, OnStall)
	ON_COMMAND(ID_LOW_FORMAT, OnLowFormat)
	ON_COMMAND(ID_HIGH_FORMAT, OnHighFormat)
	ON_COMMAND(ID_CREATE_DIR, OnCreateDir)
	ON_COMMAND(ID_DELETE_DIR, OnDeleteDir)
	ON_BN_CLICKED(IDC_UPDATE, OnUpdate)
	ON_COMMAND(ID_LOG, OnLog)
	ON_COMMAND(ID_DELETE_FILE, OnDeleteFile)
	ON_COMMAND(ID_CREATE_FILE, OnCreateFile)
	ON_NOTIFY(NM_DBLCLK, IDC_FILE_LIST, OnDblclkFileList)
	ON_BN_CLICKED(IDC_AUTHOR, OnAuthor)
	ON_COMMAND(ID_SHOW_USER, OnShowUser)
	ON_COMMAND(ID_CREATE_USER, OnCreateUser)
	ON_BN_CLICKED(IDC_CREATE_DIR, OnCreateDir)
	ON_BN_CLICKED(IDC_DELETE_DIR, OnDeleteDir)
	ON_BN_CLICKED(IDC_DELETE_FILE, OnDeleteFile)
	ON_BN_CLICKED(IDC_CREATE_FILE, OnCreateFile)
	ON_BN_CLICKED(IDC_HIGH_FORMAT, OnHighFormat)
	ON_BN_CLICKED(IDC_LOW_FORMAT, OnLowFormat)
	ON_BN_CLICKED(IDC_LOG, OnLog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFileSystemDlg message handlers

BOOL CFileSystemDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
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

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	// ���ز˵�
	CMenu menu ;
	menu.LoadMenu ( IDR_OP_MENU ) ;
	SetMenu ( &menu ) ;

	// ��ʼ���ļ��б�ؼ�
	this->m_FileList.InsertColumn ( 0, " ��  ��  ��",	LVCFMT_CENTER, 100 ) ;
	this->m_FileList.InsertColumn ( 1, " �� ��  ",		LVCFMT_CENTER, 70 ) ;
	this->m_FileList.InsertColumn ( 2, " �� С  ",		LVCFMT_CENTER, 70 ) ;
	this->m_FileList.InsertColumn ( 3, " ���ʷ�ʽ  ",	LVCFMT_CENTER, 85 ) ;
	this->m_FileList.InsertColumn ( 4, " �����û�  ",	LVCFMT_CENTER, 85 ) ;
	this->m_FileList.SetExtendedStyle ( this->m_FileList.GetExtendedStyle()|LVS_EX_FULLROWSELECT );
	
	bInstall = bLogging = FALSE ;
	SYSTEM.lpCurUser = NULL ;

	HANDLE hFile =	CreateFile ( 
		SYSTEM_SPACE_NAME,					
		GENERIC_READ, 
		FILE_SHARE_READ,  
		NULL, 
		OPEN_EXISTING, 
		FILE_ATTRIBUTE_NORMAL ,
		NULL 
		);
	if ( hFile != INVALID_HANDLE_VALUE )
	{
		CloseHandle ( hFile ) ;
		bInstall = TRUE ;
		SYSTEM.SysCreateMap ( OPEN_EXISTING ) ;
	}
	else
		CloseHandle ( hFile ) ;

	strcpy ( szCurPath, "\\\\system\\" ) ;
	this->OnUpdate () ;
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CFileSystemDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CFileSystemDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CFileSystemDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CFileSystemDlg::OnStall() 
{
	if ( bInstall == FALSE )
	{
		if ( SYSTEM.SysInstall () )
		{
			this->MessageBox ( "�ļ�ϵͳ��װ�ɹ�!" ) ;
			bInstall = TRUE ;
		}
		else
		{
			this->MessageBox ( "�ļ�ϵͳ��װʧ��!" ) ;
		}
	}
	else
	{
		if ( SYSTEM.lpCurUser != NULL )
		{
			this->MessageBox ( "�Ѿ����û���½ϵͳ, �޷�ж��ϵͳ!" ) ;
			return ;
		}

		if ( SYSTEM.SysUnstall () )
		{
			bInstall = FALSE ;
			m_FileList.DeleteAllItems () ;
			this->MessageBox ( "�ļ�ϵͳж�سɹ�!" ) ;
		}
		else
		{
			this->MessageBox ( "�ļ�ϵͳж��ʧ��!" ) ;
		}
	}
}

void CFileSystemDlg::OnLowFormat() 
{
	if ( bInstall == FALSE )
	{
		this->MessageBox ( "û�а�װ�ļ�ϵͳ!" ) ;
		return ;
	}

	if ( SYSTEM.lpCurUser != NULL ) 
	{
		this->MessageBox (  "�����û���½�����ܸ�ʽ��!" ) ;
		return ;
	}

	if ( SYSTEM.SysLowFormat () )
		this->MessageBox ( "�ļ�ϵͳ�ͼ���ʽ���ɹ�!" ) ;
	else
		this->MessageBox ( "�ļ�ϵͳ�ͼ���ʽ��ʧ��!" ) ;

	strcpy ( szCurPath, "\\\\system\\" ) ;
	this->OnUpdate() ;
}

void CFileSystemDlg::OnHighFormat() 
{
	if ( bInstall == FALSE )
	{
		this->MessageBox ( "û�а�װ�ļ�ϵͳ!" ) ;
		return ;
	}

	if ( SYSTEM.lpCurUser != NULL ) 
	{
		this->MessageBox (  "�����û���½�����ܸ�ʽ��!" ) ;
		return ;
	}

	if ( SYSTEM.SysHighFormat () )
		this->MessageBox ( "�ļ�ϵͳ�߼���ʽ���ɹ�!" ) ;
	else
		this->MessageBox ( "�ļ�ϵͳ�߼���ʽ��ʧ��!" ) ;
	
	strcpy ( szCurPath, "\\\\system\\" ) ;
	this->OnUpdate() ;
}

void CFileSystemDlg::OnCreateDir() 
{
	if ( bLogging == FALSE )
	{
		this->MessageBox ( "�û���δ��½!" ) ;
		return ;
	}

	if ( AddDirDlg.DoModal () == IDOK )
	{	
		if ( SYSTEM.SysIsFileExist ( this->szCurPath, AddDirDlg.m_SubDirName.GetBuffer(9) ) )
		{
			this->MessageBox ( "�ļ����Ѿ���ʹ��!" ) ;
			return ;
		}

		SYSTEM.SysCreateSubDir ( this->szCurPath, AddDirDlg.m_SubDirName.GetBuffer(9) ) ;
		this->OnUpdate () ;
	}
}

void CFileSystemDlg::EnumDirectory ( LPSTR lpPath )
{
	if ( bLogging == FALSE )
	{
		return ;
	}

	DIRECTORY_ITEM DirItem ;
	UINT nCurAddr = SYSTEM.SysFirstEnumDir ( lpPath, &DirItem ) ;

	char byte[MAX_USER_PWD_LEN+1] = {0} ;
	wsprintf ( byte, "%s", DirItem.szFileName ) ;
	byte[8] = 0 ;
	m_FileList.InsertItem ( 0, byte ) ;
	
	wsprintf ( byte, "%s", DirItem.szUserName ) ;
	byte[12] = 0 ;
	m_FileList.SetItemText ( 0, 4, byte ) ;

	UINT nCurNum = 1 ;
	while ( nCurNum < MAX_DIR_ITEM_IN_PAGE )
	{
		nCurAddr = SYSTEM.SysNextEnumDir ( nCurAddr, &DirItem ) ;
		if ( nCurAddr == 0 )
			break ;

		memcpy ( byte, DirItem.szFileName, MAX_FILE_NAME_LEN ) ;
		byte[8] = 0 ;
		m_FileList.InsertItem ( nCurNum, byte ) ;
			
		memcpy ( byte, DirItem.szUserName, MAX_USER_NAME_LEN ) ;
		byte[12] = 0 ;
		m_FileList.SetItemText ( nCurNum, 4, byte ) ;

		if ( DirItem.szFileName[0] == '.' && DirItem.szFileName[1] == '.' )
		{
			nCurNum ++ ;
			continue ;
		}

		wsprintf ( byte, "%s", DirItem.szFileExt ) ;
		byte[3] = 0 ;
		m_FileList.SetItemText ( nCurNum, 1, byte ) ;

		if ( DirItem.bAttribute == 0x1 || DirItem.bAttribute == 0x2 )
		{
			wsprintf ( byte, "%u", DirItem.nFileSize ) ;
			m_FileList.SetItemText ( nCurNum, 2, byte ) ;
		}	

		if ( DirItem.bAttribute == 0x4 )
			wsprintf ( byte, "��Ŀ¼" ) ;
		else if ( DirItem.bAttribute == 0x2 )
			wsprintf ( byte, "��  д" ) ;
		else if ( DirItem.bAttribute == 0x1 )
			wsprintf ( byte, "ֻ  ��" ) ;
		else
			byte[0] = 0 ;
		m_FileList.SetItemText ( nCurNum, 3, byte ) ;

		nCurNum++ ;
	}
}

void CFileSystemDlg::OnUpdate() 
{
	// TODO: Add your control notification handler code here
	m_FileList.DeleteAllItems () ;
	this->EnumDirectory ( szCurPath ) ;
}

void CFileSystemDlg::OnLog() 
{
	if ( !bInstall )
	{
		this->MessageBox ( "δ��װϵͳ!" ) ;
		return ;
	}

	if ( bLogging == FALSE )
	{
		if ( LogDlg.DoModal () == IDOK )
		{
			if ( SYSTEM.SysCheckLogInfo ( LogDlg.m_UserName.GetBuffer(13), LogDlg.m_UserPwd.GetBuffer(13) ) )
			{
				this->MessageBox ( "��½�ɹ�!" ) ;
				bLogging = TRUE ;
				strcpy ( szCurPath, "\\\\system\\" ) ;
				this->OnUpdate () ;
			}
			else
				this->MessageBox ( "��½ʧ��!" ) ;
		}
	}
	else
	{
		bLogging = FALSE ;
		SYSTEM.lpCurUser = NULL ;
		m_FileList.DeleteAllItems () ;
		this->MessageBox ( "ע���ɹ�" ) ;
	}
}

void CFileSystemDlg::OnDeleteDir() 
{
	if ( !bInstall )
	{
		this->MessageBox ( "δ��װϵͳ!" ) ;
		return ;
	}

	if ( bLogging == FALSE )
	{
		this->MessageBox ( "�û���δ��½!" ) ;
		return ;
	}

	int nCurIndex = m_FileList.GetNextItem ( -1, LVNI_SELECTED ) ;
	if ( nCurIndex == -1 )
	{
		this->MessageBox ( "��ѡ��һ���ļ�Ŀ¼!" ) ;
		return ;
	}
	
	CString FileType = m_FileList.GetItemText ( nCurIndex, 3 ) ;
	if ( nCurIndex <= 1 || !strcmp ( FileType, "ֻ  ��" ) || !strcmp ( FileType, "��  д" ) )
	{
		this->MessageBox ( "��ѡ�Ĳ���Ŀ¼!" ) ;
		return ;
	}

	CString NameStr = m_FileList.GetItemText ( nCurIndex, 0 ) ;
	strcpy ( this->szCurName, NameStr.GetBuffer(9) ) ;

	if ( !SYSTEM.SysDeleteSubDir ( this->szCurPath, this->szCurName ) )
		this->MessageBox ( "�޷�ɾ�����ļ�" ) ;
	else
		this->OnUpdate () ;
}

void CFileSystemDlg::OnCreateFile() 
{
	CFileDlg dlg ;
	if ( dlg.DoModal () == IDOK )
	{
		if ( SYSTEM.SysIsFileExist ( this->szCurPath, dlg.m_Title.GetBuffer(9) ) )
		{
			this->MessageBox ( "�ļ����Ѿ���ʹ��!" ) ;
			return ;
		}
		if ( !SYSTEM.SysCreateFile ( szCurPath, dlg.m_Title.GetBuffer(9), \
						"txt", dlg.m_Text.GetBuffer(dlg.m_Text.GetLength() ) ) )
				this->MessageBox ( "�����ļ�ʧ��!" ) ;
		this->OnUpdate () ;
	}
}

void CFileSystemDlg::OnDeleteFile() 
{
	if ( !bInstall )
	{
		this->MessageBox ( "δ��װϵͳ!" ) ;
		return ;
	}

	if ( bLogging == FALSE )
	{
		this->MessageBox ( "�û���δ��½!" ) ;
		return ;
	}

	int nCurIndex = m_FileList.GetNextItem ( -1, LVNI_SELECTED ) ;
	if ( nCurIndex == -1 )
	{
		this->MessageBox ( "��ѡ��һ���ļ�!" ) ;
		return ;
	}

	CString FileType = m_FileList.GetItemText ( nCurIndex, 3 ) ;
	if ( nCurIndex <= 1 || !strcmp ( FileType, "��Ŀ¼" ) || FileType.IsEmpty() )
	{
		this->MessageBox ( "��ѡ�Ĳ����ļ�!" ) ;
		return ;
	}

	CString NameStr = m_FileList.GetItemText ( nCurIndex, 0 ) ;
	strcpy ( szCurName, NameStr.GetBuffer(9) ) ;
	szCurName[8] = 0 ;

	if ( !SYSTEM.SysDeleteFile ( this->szCurPath, this->szCurName ) )
		this->MessageBox ( "ɾ���ļ�ʧ��!" ) ;
	else
		this->OnUpdate() ;
}

void CFileSystemDlg::OnDblclkFileList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	int nCurIndex = m_FileList.GetNextItem ( -1, LVNI_SELECTED ) ;
	if ( nCurIndex <= 0 )
		return ;

	if ( nCurIndex == 1 )
	{
		// ����Ƿ��ڸ�Ŀ¼( szCurPath ?= "\\\\system\\"  )
		if ( strlen( this->szCurPath ) == 9 )
			return ;

		UINT nCurPos = strlen(szCurPath) - 1 ;
		szCurPath[nCurPos--] = 0 ;

		while ( szCurPath[nCurPos] != '\\' )
			szCurPath[nCurPos--] = 0 ;
	}
	else
	{		
		CString TempName = m_FileList.GetItemText ( nCurIndex, 0 ) ;
		
		if ( !SYSTEM.SysCheckUserPow ( this->szCurPath, TempName.GetBuffer(9) ) )
		{
			this->MessageBox ( "��ǰ�û�û�д򿪸��ļ���Ȩ��!" ) ;
			return ;
		}
		
		if ( strcmp( m_FileList.GetItemText(nCurIndex, 3), "��Ŀ¼" ) )
		{
			CFileDlg dlg ;
			dlg.m_Title	= TempName ;
			dlg.m_Text	= SYSTEM.SysReadFile ( this->szCurPath, TempName.GetBuffer(9) ) ;
			dlg.DoModal () ;
			return ;
		}
		else
		{
			char byte[15] = {0} ;
			wsprintf ( byte, "%s\\", TempName ) ;
			strcat ( szCurPath, byte ) ; 
		}
	}

	CString	TempStr ;
	TempStr.Format ( "��ǰ·��: %s", szCurPath ) ;
	this->SetDlgItemText ( IDC_CUR_PATH, TempStr ) ;
	this->OnUpdate () ;

	*pResult = 0;
}

void CFileSystemDlg::OnAuthor() 
{
	CAboutDlg dlg ;
	dlg.DoModal () ;
}

void CFileSystemDlg::OnShowUser() 
{
	if ( !bInstall )
	{
		this->MessageBox ( "δ��װϵͳ!" ) ;
		return ;
	}

	ShowUserDlg.SYSTEM = this->SYSTEM ;
	ShowUserDlg.DoModal() ;
}

void CFileSystemDlg::OnCreateUser() 
{
	if ( !bInstall )
	{
		this->MessageBox ( "δ��װϵͳ!" ) ;
		return ;
	}

	if ( AddUserDlg.DoModal() == IDOK )
	{
		if ( SYSTEM.SysIsUserExist ( AddUserDlg.m_UserName.GetBuffer(MAX_USER_PWD_LEN+1) ) )
		{
			this->MessageBox ( "���û����ѱ�ʹ��!", "����û�ʧ��" ) ;
			return ;
		}

		if ( SYSTEM.SysAddUserInfo ( AddUserDlg.m_UserName.GetBuffer(MAX_USER_PWD_LEN+1), \
									 AddUserDlg.m_UserPwd.GetBuffer(MAX_USER_PWD_LEN+1) ) )
		{
			this->MessageBox ( "����û��ɹ�!" ) ;
		}
		else
		{
			this->MessageBox ( "����û�ʧ��!" ) ;
		}
	}
}

void CFileSystemDlg::OnCancel() 
{
	SYSTEM.SysDeleteMap() ;	
	CDialog::OnCancel();
}
