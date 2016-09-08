// NagGenDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "NagGen.h"
#include "NagGenDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define MAX_BUF_SIZE		2048
#define MAX_TITLE_SIZE		64
#define MAX_CONTENT_SIZE	256

TCHAR a[] = TEXT("fjda") ;
TCHAR b[] = TEXT("fdsadagfdsa") ;

void StubCode ()
{	
	PTCHAR pTitle	= NULL ;
	PTCHAR pContent	= NULL ;

	DWORD begin, end ;
	__asm
	{
		push	edx
		call	$+5
		pop		edx
		add		edx, 7
		mov		begin, edx
BEGIN:
		pushad
		push	0
		push	pTitle
		push	pContent
		push	0
		call	dword ptr MessageBoxW
		popad
END:	
		call	$+5
		pop		edx
		add		edx, -5
		mov		end, edx
		pop		edx
	}
}

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


// CNagGenDlg �Ի���




CNagGenDlg::CNagGenDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CNagGenDlg::IDD, pParent)
	, m_PathName(_T(""))
	, m_NagTitle(_T(""))
	, m_NagContent(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CNagGenDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_PATH, m_PathName);
	DDX_Text(pDX, IDC_NAG_TITLE, m_NagTitle);
	DDV_MaxChars(pDX, m_NagTitle, 62);
	DDX_Text(pDX, IDC_NAG_CONTENT, m_NagContent);
	DDV_MaxChars(pDX, m_NagContent, 252);
}

BEGIN_MESSAGE_MAP(CNagGenDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_EN_CHANGE(IDC_PATH, &CNagGenDlg::OnEnChangePath)
	ON_EN_CHANGE(IDC_NAG_TITLE, &CNagGenDlg::OnEnChangeNagTitle)
	ON_EN_CHANGE(IDC_NAG_CONTENT, &CNagGenDlg::OnEnChangeNagContent)
	ON_BN_CLICKED(IDC_BROWSE, &CNagGenDlg::OnBnClickedBrowse)
	ON_BN_CLICKED(IDOK, &CNagGenDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CNagGenDlg ��Ϣ�������

BOOL CNagGenDlg::OnInitDialog()
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
	this->m_NagTitle = TEXT("NAG Sample !") ;
	this->m_NagContent = TEXT ( "This is a nag sample !(Insert a NAG MessageBox to the original PE(exe) file" ) ;
	this->UpdateData ( false ) ;

	//StubCode () ;

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CNagGenDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CNagGenDlg::OnPaint()
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
HCURSOR CNagGenDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CNagGenDlg::OnEnChangePath()
{
	this->UpdateData () ;
}

void CNagGenDlg::OnEnChangeNagTitle()
{
	this->UpdateData () ;
}

void CNagGenDlg::OnEnChangeNagContent()
{
	this->UpdateData () ;
}

void CNagGenDlg::OnBnClickedBrowse()
{	
	static TCHAR szFilter[] = TEXT ( "PE Files (*.exe)|*.exe||" ) ;
	CFileDialog dlg ( true, 0, 0, 4|2, szFilter ) ;
	if ( dlg.DoModal() == IDOK )
	{
		this->m_PathName = dlg.GetPathName() ;
		this->PEInfo.isReady = TRUE ;
		this->UpdateData ( false ) ;
	}
}

void CNagGenDlg::OnBnClickedOk()
{
	if ( this->PEInfo.isReady == FALSE )
	{
		this->MessageBox ( TEXT("Select a PE File!") ) ;
		return ;
	}

	if ( this->m_NagTitle.IsEmpty() == TRUE )
	{
		this->MessageBox ( TEXT("NAG Title should not be empty!") ) ;
		return ;
	}

	if ( this->m_NagContent.IsEmpty() == TRUE )
	{
		this->MessageBox ( TEXT("NAG Content should not be empty!") ) ;
		return ;
	}

	MAP_ITEM OldMap = {0}, NewMap = {0} ;

	TCHAR	pBuf[MAX_BUF_SIZE] = {0} ;
	BYTE	pData[MAX_BUF_SIZE] ={0} ;
	wsprintf ( pBuf, this->m_PathName.GetBuffer(this->m_PathName.GetLength()) ) ;
	if ( this->PEInfo.CreateMap(pBuf, &OldMap) == FALSE )
	{
		this->MessageBox ( TEXT("Please ensure this file is not been used!") ) ;
		return ;
	}
	
	// ȡ��PE�ļ�������Ϣ
	this->PEInfo.GetBaseInfo ( &OldMap ) ;
	// ��ʼ����������Ϣ
	this->PEInfo.InitNewSection () ;

	// ������������ݣ����浽pData������������������Ҫ�ĳ��ȶ�������Ϣ���е���
	DWORD dwNeedSize = this->GenerateData ( pData, OldMap.lpMapAddr );
	if ( this->PEInfo.NewSection.SizeOfRawData < dwNeedSize )
		this->PEInfo.NewSection.SizeOfRawData = dwNeedSize ;
	this->PEInfo.AdjustSectionSize () ;

	// �������ļ�(*_nag.exe)
	CString TempStr = this->m_PathName ;
	DWORD	dwNewFileSize = this->PEInfo.NewSection.PointerToRawData + this->PEInfo.NewSection.SizeOfRawData ;
	TempStr.SetAt ( TempStr.GetLength()-4, 0 ) ;
	wsprintf ( pBuf, TEXT("%s%s"), TempStr.GetBuffer(TempStr.GetLength()), TEXT("_nag.exe") ) ;
	if ( this->PEInfo.CreateNewMap ( pBuf, &NewMap, dwNewFileSize ) == FALSE )
	{
		this->MessageBox ( TEXT("Could't create new file!") ) ;
		DeleteFile ( pBuf ) ;
		return ;
	}

	// ���������Ϣ
	this->PEInfo.AddNewSection ( &OldMap, &NewMap, dwNewFileSize ) ;

	// ɾ��ԭPE�ļ���ӳ��
	this->PEInfo.DeleteMap ( &OldMap ) ;

	// ��pData�е�����д�뵽�����飨 contain IID, NewDllName, NewFunName, NewIat��
	LPVOID	lpNewSection = LPVOID(DWORD(NewMap.lpMapAddr)+this->PEInfo.NewSection.PointerToRawData) ;
	memcpy ( lpNewSection, pData, this->PEInfo.NewSection.SizeOfRawData ) ;

	// ȡ��PEͷ��Ϣ
	PIMAGE_DOS_HEADER	pDosHeader	= (PIMAGE_DOS_HEADER)(NewMap.lpMapAddr) ;
	PIMAGE_NT_HEADERS	pNtHeader	= (PIMAGE_NT_HEADERS)((LONG)(NewMap.lpMapAddr)+ (pDosHeader->e_lfanew)) ;
	PIMAGE_OPTIONAL_HEADER32 pOptionalHeader = &(pNtHeader->OptionalHeader) ;

	// д����IID��Ϣ
	// ���OriginalFirstThunk �ֶε�ֵΪ0�����ؾͲ����дIAT��Ҳ����˵����Ҫ�Լ���IATд���Ӧ�����ĵ�ַ
	// �����OriginalFirstThunk��ֵ����Ϊ��FirstThunk��ͬ��������ʼ����ʱ��������ͻ��дIAT
	PIMAGE_IMPORT_DESCRIPTOR pIID = (PIMAGE_IMPORT_DESCRIPTOR)((DWORD)lpNewSection + 0x14 * this->dwIIDNum) ;
	pIID->Name			= this->dwDllNameOff + this->PEInfo.NewSection.VirtualAddress ;
	pIID->FirstThunk	= this->dwIATOff + this->PEInfo.NewSection.VirtualAddress ;
	pIID->OriginalFirstThunk	= pIID->FirstThunk ;
	pIID->ForwarderChain	= 0xFFFFFFFF ;
	pIID->TimeDateStamp		= 0xFFFFFFFF ;
	*((DWORD*)(this->dwIATOff + (DWORD)lpNewSection)) = this->dwFunNameOff + this->PEInfo.NewSection.VirtualAddress ;
	
	
	// �޸�����Ŀ¼�������������Ϣ
	pOptionalHeader->DataDirectory[1].VirtualAddress	= this->PEInfo.NewSection.VirtualAddress ;
	pOptionalHeader->DataDirectory[1].Size			   += 0x14 ;

	// ����������
	pOptionalHeader->DataDirectory[11].VirtualAddress	= 0 ;
	pOptionalHeader->DataDirectory[11].Size				= 0 ;
	
	// �޸�OEP
	pOptionalHeader->AddressOfEntryPoint = this->dwNewEntryOff + this->PEInfo.NewSection.VirtualAddress ;
	
	this->PEInfo.FlushData ( LPVOID(this->PEInfo.NewSection.VirtualAddress), this->PEInfo.NewSection.SizeOfRawData ) ;
	this->PEInfo.DeleteMap ( &NewMap ) ;

	this->MessageBox ( TEXT("���Nag���ڳɹ�!") ) ;
}

DWORD CNagGenDlg::GenerateData(PBYTE pData, LPVOID lpImageBase)
{
	// ȡ��PE�ļ�������Ϣ
	PIMAGE_DOS_HEADER	pDosHeader	= (PIMAGE_DOS_HEADER)(lpImageBase) ;
	PIMAGE_NT_HEADERS	pNtHeader	= (PIMAGE_NT_HEADERS)((LONG)(lpImageBase)+ (pDosHeader->e_lfanew)) ;
	PIMAGE_OPTIONAL_HEADER32 pOptionalHeader = &(pNtHeader->OptionalHeader) ;
	PIMAGE_DATA_DIRECTORY pImportData	= (PIMAGE_DATA_DIRECTORY)(&( pOptionalHeader->DataDirectory[1]) ) ;
	PIMAGE_IMPORT_DESCRIPTOR	pIID = (PIMAGE_IMPORT_DESCRIPTOR) ImageRvaToVa ( pNtHeader, lpImageBase, pImportData->VirtualAddress, NULL ) ;

	// ��ԭIID������������
	memcpy ( pData, LPVOID(pIID), pOptionalHeader->DataDirectory[1].Size ) ;

	// ͳ��IID����
	this->dwIIDNum		= 0 ;
	while ( pIID[this->dwIIDNum].FirstThunk )
		this->dwIIDNum ++ ;

	char	szDllName[] = "USER32.dll" ;
	char	szFunName[] = "MessageBoxA" ;

	// ����ƫ����Ϣ
	this->dwDllNameOff		= pOptionalHeader->DataDirectory[1].Size + 0x14 ;
	this->dwFunNameOff		= this->dwDllNameOff + sizeof ( szDllName ) + 3 ;
	this->dwIATOff			= this->dwFunNameOff + sizeof ( szFunName ) + 4 ;
	this->dwNagTitleOff		= this->dwIATOff + 12 ;

	// д��DLL��
	memcpy ( &(pData[this->dwDllNameOff]), szDllName, sizeof(szDllName) ) ;
	// д�뺯����
	memcpy ( &(pData[this->dwFunNameOff+2]), szFunName, sizeof(szFunName) ) ; // 2, ���


	CHAR pTitle[128] = {0}, pContent[512] = {0} ;
	::GetDlgItemTextA ( this->GetSafeHwnd(), IDC_NAG_TITLE, pTitle, 128 ) ;
	::GetDlgItemTextA ( this->GetSafeHwnd(), IDC_NAG_CONTENT, pContent, 512 ) ;

	// ����ƫ����Ϣ��NagTitle + NagContent��
	this->dwNagContentOff	= this->dwNagTitleOff + strlen(pTitle) + 1 ;
	this->dwNewEntryOff		= this->dwNagContentOff + strlen(pContent) + 1 ;

	// ��NagTitle��NagContent��Ϣд�뻺����
	wsprintf ( PTCHAR(&pData[this->dwNagTitleOff]), TEXT("%s"), pTitle ) ;
	wsprintf ( PTCHAR(&pData[this->dwNagContentOff]), TEXT("%s"), pContent ) ;


	//////////////////////////////////////////////////////////////////////////////////////////
	// Stub Code ( 0x11111111Ϊ����ռλ������������
	// pushad
	// push 0
	// push 0x11111111
	// push 0x11111111
	// push 0
	// call dword ptr MessageBoxW
	// popad
	// jmp  0x11111111
	/////////////////////////////////////////////////////////////////////////////////////////
	BYTE pbCommand[] = { 0x60, 0x6A, 0x00, 0x68, 0x11, 0x11, 0x11, 0x11, \
			0x68, 0x11, 0x11, 0x11, 0x11, 0x6A, 0x00, 0xFF, 0x15, 0xBC, 0xF2, 0x42, 0x00, 0x61, \
			0xE9, 0x11, 0x11, 0x11, 0x11 } ;
	
	// ͳ��Stub Code���ȣ�Ȼ��д��pData������
	DWORD	dwStubLength = sizeof(pbCommand);
	memcpy ( &(pData[this->dwNewEntryOff]), pbCommand, dwStubLength ) ;

	// ���� JMP ָ��Ĳ�����
	DWORD dwOldEntryRVA = pOptionalHeader->AddressOfEntryPoint ;
	DWORD dwNewEntryRVA = this->PEInfo.NewSection.VirtualAddress + this->dwNewEntryOff + 22 ;
	DWORD dwJmpDist		= dwOldEntryRVA - dwNewEntryRVA - 5 ;

	// ����TitleVA
	*((DWORD*)(&(pData[this->dwNewEntryOff+4])))	= pOptionalHeader->ImageBase + this->PEInfo.NewSection.VirtualAddress + this->dwNagTitleOff ;
	// ����ContentVA
	*((DWORD*)(&(pData[this->dwNewEntryOff+9])))	= pOptionalHeader->ImageBase + this->PEInfo.NewSection.VirtualAddress + this->dwNagContentOff ;
	// ���� CALL [0x********]
	*((DWORD*)(&(pData[this->dwNewEntryOff+17])))	= pOptionalHeader->ImageBase + this->PEInfo.NewSection.VirtualAddress + this->dwIATOff ;
	// ���� JMP �Ĳ����� ==> E9 ** ** ** **
	*((DWORD*)(&(pData[this->dwNewEntryOff+23])))	= dwJmpDist ;

	// �����ܳ���
	return this->dwNewEntryOff + dwStubLength + 0x10 ;
}
