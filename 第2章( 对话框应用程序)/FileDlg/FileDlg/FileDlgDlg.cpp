// FileDlgDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "FileDlg.h"
#include "FileDlgDlg.h"

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


// CFileDlgDlg �Ի���




CFileDlgDlg::CFileDlgDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFileDlgDlg::IDD, pParent)
	, szSigOpenPath(_T(""))
	, szSigSavePath(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFileDlgDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_Path1, szSigOpenPath);
	DDX_Text(pDX, IDC_PATH2, szSigSavePath);
	DDX_Control(pDX, IDC_PATH_LIST, PathList);
}

BEGIN_MESSAGE_MAP(CFileDlgDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_Select1, &CFileDlgDlg::OnBnClickedSelect1)
	ON_BN_CLICKED(IDC_SELECT2, &CFileDlgDlg::OnBnClickedSelect2)
	ON_BN_CLICKED(IDC_SELECT3, &CFileDlgDlg::OnBnClickedSelect3)
END_MESSAGE_MAP()


// CFileDlgDlg ��Ϣ�������

BOOL CFileDlgDlg::OnInitDialog()
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

void CFileDlgDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CFileDlgDlg::OnPaint()
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
HCURSOR CFileDlgDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
} 
 

void CFileDlgDlg::OnBnClickedSelect1()
{
	// ���塰�򿪡��Ի���
	CFileDialog dlg ( TRUE ) ;
	if ( dlg.DoModal() == IDOK )
	{
		// ȡ���ļ�·��ȫ��
		// szSigOpenPath��CString���ͣ�����һ���༭�������
		this->szSigOpenPath = dlg.GetPathName() ;
		// ���½�����ʾ
		this->UpdateData( FALSE ) ;
	}	
}

void CFileDlgDlg::OnBnClickedSelect2()
{
	// ���塰���Ϊ���Ի���
	CFileDialog dlg ( FALSE ) ;
	if ( dlg.DoModal() == IDOK )
	{
		// ȡ���ļ�·��ȫ��
		// szSigSavePath��CString���ͣ�����һ���༭�������
		this->szSigSavePath = dlg.GetPathName() ;
		// ���½�����ʾ
		this->UpdateData( FALSE ) ;
	}	
}

void CFileDlgDlg::OnBnClickedSelect3()
{
	// ���ù�������ֻ��ѡ��*.exe����*.txt���͵��ļ�
	static WCHAR szFilter[] = L"��ִ���ļ�(*.exe)|*.exe|�ı��ļ�(*.txt)|*.txt||" ;
	// ����OFN_ALLOWMULTISELECT��ǣ�֧�ֶ�ѡ
	CFileDialog dlg ( TRUE, NULL, NULL, OFN_ALLOWMULTISELECT, szFilter ) ;
	if ( dlg.DoModal() == IDOK )
	{
		// ����б��
		this->PathList.ResetContent() ;
		// ȡ����ѡ��ĵ�һ���ļ���λ��Ϣ��
		POSITION pos = dlg.GetStartPosition() ;
		while ( pos )
			// ȡ��·��ȫ������ӵ��б��
			this->PathList.AddString ( dlg.GetNextPathName(pos) ) ;
	}
}
