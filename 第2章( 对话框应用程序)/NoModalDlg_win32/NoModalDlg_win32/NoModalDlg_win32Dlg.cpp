// NoModalDlg_win32Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "NoModalDlg_win32.h"
#include "NoModalDlg_win32Dlg.h"

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


// CNoModalDlg_win32Dlg �Ի���




CNoModalDlg_win32Dlg::CNoModalDlg_win32Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CNoModalDlg_win32Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CNoModalDlg_win32Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CNoModalDlg_win32Dlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_CREATE_DIALOG, &CNoModalDlg_win32Dlg::OnBnClickedCreateDialog)
END_MESSAGE_MAP()


// CNoModalDlg_win32Dlg ��Ϣ�������

BOOL CNoModalDlg_win32Dlg::OnInitDialog()
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

void CNoModalDlg_win32Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CNoModalDlg_win32Dlg::OnPaint()
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
HCURSOR CNoModalDlg_win32Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

INT_PTR CALLBACK DialogProc( HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	switch ( uMsg )
	{
	// ����Ի����ʼ����Ϣ
	case WM_INITDIALOG:
		// ��ʱ��lParam����CreateDialogParam�����һ������dwInitParam�����õ�ֵ
		return TRUE ;
	// ����WM_COMMAND��Ϣ
	case WM_COMMAND:
		{
			switch ( LOWORD(wParam) )
			{
			// ��Ӧ�Ի���Ľ�����Ϣ
			case IDCANCEL:
				::EndDialog ( hwndDlg, 0 ) ;
				return TRUE ;
			}
		}
		break ;
	}
	// ����FALSE����ʾ����Ϣ�������ݸ�ϵͳĬ�ϵ���Ϣ�������
	// ����TRUE���ͱ�ʾ����Ҫ����������Ϣ
	return FALSE ;
}


void CNoModalDlg_win32Dlg::OnBnClickedCreateDialog()
{
	//  ȡ�õ�ǰģ��ʵ�����
	HINSTANCE hInstance = (HINSTANCE)GetModuleHandle ( NULL ) ;
	// ������ģ̬�Ի���
	HANDLE hDlg = CreateDialog ( hInstance, MAKEINTRESOURCE(IDD_NOMODAL_DIALOG), NULL, DialogProc ) ;
	// ��ʾ�Ի���
	::ShowWindow ( (HWND)hDlg, SW_SHOW ) ;
}
